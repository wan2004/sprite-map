#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QObject>
#include <QGraphicsScene>
class Sprite;
class MapInfo;
class MapBase;
class MapManager : public QObject
{
    Q_OBJECT
public:
    explicit MapManager(QGraphicsScene* scene,QObject *parent = 0);
    bool initMap(MapInfo* mapinfo);
    Sprite* addSprite(Sprite* sprite,bool block=true,unsigned int level=1);
    Sprite* removeSprite(Sprite* sprite);
    bool isInitialized();
private:
    QGraphicsScene* drawScene;
    MapInfo* curMapInfo;
    bool initialized;
signals:

public slots:

};

#endif // MAPMANAGER_H
