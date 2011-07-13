#include "mapbase.h"
#include <QPainter>
#include <QPixmap>
MapBase::MapBase(QPixmap* base,unsigned int hindex ,unsigned int vindex ,
                 unsigned int hnum ,unsigned int vnum ,QGraphicsItem* parent)
    :Sprite(parent)
{
    this->iColnum = hnum;
    this->iRownum = vnum;
    this->sizeV = DEF_MAPBASE_WIDTH;
    this->sizeH = DEF_MAPBASE_HEIGHT;
    this->vindex = vindex;
    this->hindex = hindex;
    this->setPixmap(base);
    this->width = iColnum * sizeH;
    this->height = iRownum * sizeV;
}

void MapBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(QPointF(0,0),*this->getPixmap(),QRectF(hindex * sizeH,vindex * sizeV,iColnum * sizeH,iRownum * sizeV));

}
void MapBase::setIColnum(uint col)
{
    this->iColnum =col;
    this->width = iColnum * sizeH;
}

void MapBase::setIRownum(uint row)
{
    this->iRownum =row;
    this->height = iRownum * sizeV;
}
