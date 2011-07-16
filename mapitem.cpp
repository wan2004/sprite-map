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

