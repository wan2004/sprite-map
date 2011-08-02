#include "mapitem.h"
#include <QPainter>
MapItem::MapItem(QPixmap* base,QString tName,unsigned int hindex ,unsigned int vindex ,
                 unsigned int hnum,unsigned int vnum ,QGraphicsItem* parent )
                     : MapBase(base,hindex,vindex,hnum,vnum,parent)
{
    crossType = 0;
    checkType = 0;
    breakType = 0;
    special = 0;
    mapX = 0;
    mapY = 0;
    mapZ = 0;
    typeName = tName;

}

//用mapX mapY 更新坐标系属性 x , y
void MapItem::updateLocation()
{
    int posXoffset,posYoffset;
    posXoffset = this->mapX * this->sizeH ;
    posYoffset = this->mapY * this->sizeV ;
    this->setPos(posXoffset ,posYoffset);
}
