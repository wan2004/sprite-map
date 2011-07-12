#include "spritescene.h"
#include "sprite.h"
#include <QPixmap>
#include <QGraphicsScene>
#include "mapbase.h"
#include "mapinfo.h"
#include "mapmanager.h"
SpriteScene::SpriteScene(QGraphicsView *parent)
    : QGraphicsView(parent)
{
    this->_scene = new QGraphicsScene(0,0,800,600);

    this->setScene(this->_scene);
    this->setSceneRect(0,0,795,595);
    this->setWindowFlags(Qt::FramelessWindowHint);

    MapInfo* mapinfo = new MapInfo();
    QString map1data("ansi1.mdt");
    mapinfo->readMap(map1data);

    MapManager* manager1 = new MapManager(this->_scene);
    manager1->initMap(mapinfo);
    //this->_scene->createItemGroup(this->_scene->items())->setPos(100,100);
}

SpriteScene::~SpriteScene()
{

}
