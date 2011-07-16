#include "mapinfo.h"
#include <QFile>
#include <QDebug>
#include <stdio.h>
#include <QPixmap>
#include <QStringList>
#include <QTextStream>
#define SEPR "----------"
#define SEPR_ITEM "@@@@@@@@@@"
#define MDT_NAME "name:"
#define MDT_TYPE "type:"
#define MDT_WIDTH "width:"
#define MDT_HEIGHT "height:"
#define MDT_BACKGROUND "background:"


MapInfo::MapInfo(QString &basefile,QObject *parent) :
    QObject(parent)
{
    QImage image;
    image.load(basefile);
    this->base = new QPixmap();
    this->base->convertFromImage(image);
}
MapInfo::~MapInfo()
{
    int i;
    for(i=0;i < this->_data.length();i++){
        delete _data.at(i);
    }
    this->_data.clear();
    delete base;
}

bool MapInfo::readMap(QString &path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly )) {

        QByteArray line;

        while (QString(line.mid(0,10)).compare(SEPR_ITEM))//解析地图其他信息 分隔符 @@@@@@@@@@
        {
            line = file.readLine();
            analysisString(line);

            if(file.atEnd())return false;
        }
        qDebug()<< "name is " << this->name;
        qDebug()<< "width is " << this->width;
        qDebug()<< "height is " << this->height;
        qDebug()<< "type is " << this->type;
        line = file.readLine();
        while (QString(line.mid(0,10)).compare(SEPR))//解析地图上面的物品和其他信息 分隔符 -----------
        {
            analysisHandleLine(line);
            line = file.readLine();
            if(file.atEnd())return false;
        }

        while (!file.atEnd()) //解析地图背景信息
        {
            line = file.readLine();
            QString tmp(line);
            MapBase* mbase= new MapBase(this->base);

            int toke1 = tmp.indexOf(",");
            int toke2 = tmp.indexOf(" ");
            //int toke3 = tmp.indexOf(",",toke2);
            unsigned int col1 =  QVariant(tmp.mid(0 ,toke1)).toInt();
            unsigned int row1 =  QVariant(tmp.mid(toke1 + 1,toke2 - toke1 -1 )).toInt();

            mbase->vindex = row1;
            mbase->hindex = col1;

            this->_data.append(mbase);
            qDebug() << "row1 is " << row1;
            qDebug() << "col1 is " << col1;
        }
        qDebug()<< "mbase lenght is " << this->_data.length();
        file.close();
        return true;
    }else{
        qDebug()<< "file not found" ;
        return false;
    }

}

bool MapInfo::writeMap(QString &path)
{
    QFile file(path);
    if(file.open(QFile::WriteOnly)){
        QString dataformat;
        int i;

        file.write((MDT_NAME+this->name+"\r\n").toLocal8Bit());
        file.write((MDT_TYPE+QVariant(this->type).toString()+"\r\n").toLocal8Bit());
        file.write((MDT_WIDTH+QVariant(this->width).toString()+"\r\n").toLocal8Bit());
        file.write((MDT_HEIGHT+QVariant(this->height).toString()+"\r\n").toLocal8Bit());
        file.write((MDT_BACKGROUND+this->background.name()+"\r\n").toLocal8Bit());
        file.write((tr(SEPR_ITEM)+"\r\n").toLocal8Bit());
        dataformat = ("%1,%2|%3,%4|%5,%6|%7|%8|%9|%10|%11|\r\n");
        QList<MapItem*> list1 = getMapItemInfo();
        for(i=0;i<list1.length();i++)
        {
            MapItem* base = list1.at(i);

            QString data = dataformat.arg(
                    QVariant(base->hindex).toString(),QVariant(base->vindex).toString(),
                    QVariant(base->iColnum).toString(),QVariant(base->iRownum).toString(),
                    QVariant(base->mapX).toString(),QVariant(base->mapY).toString(),
                    QVariant(base->crossType).toString(),
                    QVariant(base->checkType).toString(),
                    QVariant(base->breakType).toString()
                    ).arg(QVariant(base->special).toString())
                    .arg(QVariant(base->mapZ).toString());
            file.write(data.toUtf8());
        }
        file.write((tr(SEPR)+"\r\n").toUtf8());

        QList<MapBase*> list = getMapBaseInfo();

        dataformat = ("%1,%2\r\n");
        for(i=0;i<list.length();i++)
        {
            MapBase* base = list.at(i);

            QString data = dataformat.arg(QVariant(base->hindex).toString(),QVariant(base->vindex).toString());
            file.write(data.toUtf8());
        }
        if(!file.flush())
            return false;

        file.close();
        return true;
    }else{
        return false;
    }

}

QList<MapBase*> MapInfo::getMapBaseInfo()
{
    return this->_data;
}
QList<MapItem*> MapInfo::getMapItemInfo()
{
    return this->_item;
}
/*
 * Warning 不是同一个list时,上个list内指针内存泄露
 */
void MapInfo::setMapBaseInfo(QList<MapBase*> list)
{
    this->_data = list;
}

// 从0行0列开始
bool MapInfo::setMapBase(unsigned int row,unsigned int col,MapBase* base)
{
    delete this->_data.at(row+col * this->width);
    this->_data.replace(row+col * this->width,base);
    return true;
}

void MapInfo::analysisString(const QByteArray byte)//解析地图上面的物件和其他信息
{
    QString str(byte);
    if(str.contains(MDT_NAME)){
        this->name = str.mid(strlen(MDT_NAME),str.indexOf("\r\n") - strlen(MDT_NAME));
    }else if(str.contains(MDT_TYPE)){
        QString tmp = str.mid(strlen(MDT_TYPE),str.indexOf("\r\n") - strlen(MDT_TYPE));  // 根据 MDT_TYPE 得到对应 贴图文件
        this->type = QVariant(tmp).toInt();
        if(base == 0)base = new QPixmap("base"+tmp+".png");
    }else if(str.contains(MDT_WIDTH)){
        this->width = QVariant(str.mid(strlen(MDT_WIDTH),str.indexOf("\r\n") - strlen(MDT_WIDTH))).toInt();
    }else if(str.contains(MDT_HEIGHT)){
        this->height = QVariant(str.mid(strlen(MDT_HEIGHT),str.indexOf("\r\n") - strlen(MDT_HEIGHT))).toInt();
    }else if(str.contains(MDT_BACKGROUND)){
        this->background = QColor(str.mid(11,str.indexOf("\r\n") - 11));
    }
}


/*
*  根据 | 隔开解析各个属性
*  背景|区块大小|所在点|穿透|调查|可破坏|特殊操作|类别名称|
*/
void MapInfo::analysisHandleLine(const QByteArray byte)
{
    QString line(byte);
    QList<QString> strList;
    int pos1,pos2;

    pos1 = 0;
    pos2 = line.indexOf("|",pos1);
    while (pos2!= -1)
    {
        strList.append(line.mid(pos1,pos2- pos1));
        pos1 = pos2 + 1;
        pos2 = line.indexOf("|",pos1);
    }
    if(!this->base)qDebug()<<" base is null";
    MapItem* item = new MapItem(this->base);
    int tmp = 0;
    QString hi;

    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->hindex = QVariant(hi.mid(0,hi.indexOf(",") )).toUInt();
        item->vindex = QVariant(hi.mid(hi.indexOf(",")+1)).toUInt();
        tmp++;
    }
    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->setIColnum (QVariant(hi.mid(0,hi.indexOf(","))).toUInt());
        item->setIRownum (QVariant(hi.mid(hi.indexOf(",")+1)).toUInt());
        tmp++;
    }
    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->mapX = QVariant(hi.mid(0,hi.indexOf(",") )).toUInt();
        item->mapY = QVariant(hi.mid(hi.indexOf(",")+1)).toUInt();
        tmp++;
    }
    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->crossType = QVariant(hi).toInt();
        tmp++;
    }
    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->checkType = QVariant(hi).toInt();
        tmp++;
    }
    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->breakType = QVariant(hi).toInt();
        tmp++;
    }
    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->special = QVariant(hi).toInt();
        tmp++;
    }
    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->mapZ = QVariant(hi).toInt();
        tmp++;
    }
    if(tmp < strList.length()){
        hi = strList.at(tmp);
        item->typeName = hi;
        tmp++;
    }

    this->_item.append(item);
}
