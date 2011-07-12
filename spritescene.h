#ifndef SPRITESCENE_H
#define SPRITESCENE_H

#include <QtGui/QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include "sprite.h"
#define IMAGE_FILE1 "swod.png"
#define IMAGE_FILE2 "base.png"
class QPixmap;
class SpriteScene : public QGraphicsView
{
    Q_OBJECT

public:
    SpriteScene(QGraphicsView *parent = 0);
    ~SpriteScene();
private:
    QGraphicsScene* _scene;
    QList<Sprite*> itemList;
    QPixmap* base;
};

#endif // SPRITESCENE_H
