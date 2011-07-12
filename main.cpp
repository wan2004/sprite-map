#include <QtGui/QApplication>
#include "spritescene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpriteScene w;
    w.resize(800,600);
    w.show();

    return a.exec();
}
