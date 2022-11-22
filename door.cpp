#include "door.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>

door::door()
{
    //sets door image
    QPixmap doorimage(":/new/prefix1/pinkdoor.png");
    doorimage = doorimage.scaledToWidth(100);
    doorimage = doorimage.scaledToHeight(100);
    setPixmap(doorimage);
}


