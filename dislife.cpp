#include "dislife.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>

dislife::dislife()
{
    //sets heart image
    QPixmap heartsimage(":/new/prefix1/heart.png");
    heartsimage = heartsimage.scaledToWidth(30);
    heartsimage = heartsimage.scaledToHeight(30);
    setPixmap(heartsimage);
}
