#include <QtGui/QApplication>
#include <QTextCodec>
#include "spritescene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    SpriteScene w;
    w.resize(800,600);
    w.show();

    return a.exec();
}
