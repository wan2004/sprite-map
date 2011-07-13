#include "mapmanager.h"
#include "mapinfo.h"
#include "mapbase.h"
#include "sprite.h"
#include <QList>
#include <QDebug>
MapManager::MapManager(QGraphicsScene* scene,QObject *parent) :
    QObject(parent)
{
    this->drawScene = scene;
    curMapInfo = 0;
    initialized = false;
}

bool MapManager::initMap(MapInfo *mapinfo)
{
    qDebug()<< "init start";
    curMapInfo = mapinfo;
    int i;
    QList<MapBase*> list = mapinfo->getMapBaseInfo(); //得到背景信息并加入场景

    for(i = 0;i < list.length();i++){
        MapBase* base = list.at(i);
        int posXoffset,posYoffset;
        if(mapinfo->width){
            posXoffset = ( i % mapinfo->width ) * DEF_MAPBASE_WIDTH;
            posYoffset = ( i / mapinfo->width ) * DEF_MAPBASE_HEIGHT;
        }else {
            posXoffset = 0;
            posYoffset = 0;
        }
        base->setPos(posXoffset ,posYoffset);
        if(!this->drawScene->items().contains(base)){
            this->drawScene->addItem(base);
        }
    }
    QList<MapItem*> listitem = mapinfo->getMapItemInfo(); //得到物件信息并加入场景

    for(i = 0;i < listitem.length();i++){
        MapItem* item = listitem.at(i);
        int posXoffset,posYoffset;
        posXoffset = item->mapX * item->sizeH ;
        posYoffset = item->mapY * item->sizeV ;
        item->setPos(posXoffset ,posYoffset);
        if(!this->drawScene->items().contains(item)){
            this->drawScene->addItem(item);
            item->setZValue(item->mapZ);
        }
    }

    this->drawScene->setBackgroundBrush(QBrush(curMapInfo->background));
    this->initialized = true;
    return this->initialized;
}

Sprite* MapManager::addSprite(Sprite *sprite,QString type,unsigned int level)
{
    if(!spriteMap.contains(type)){
        QList<Sprite* >* list = new QList<Sprite*>();
        list->append(sprite);
        spriteMap.insert(type,list);
    }else{
        QList<Sprite* >* list = spriteMap.value(type);
        list->append(sprite);
    }
    return sprite;
}

Sprite* MapManager::removeSprite(Sprite *sprite,QString type)
{
    if(spriteMap.contains(type)){
        QList<Sprite* >* list = spriteMap.value(type);
        list->removeAll(sprite);
    }
    return sprite;
}

bool MapManager::isInitialized()
{
    return this->initialized;
}
