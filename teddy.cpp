#include "teddy.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>

Teddy::Teddy()
{
    // sets teddy image
    QPixmap teddyimage(":/new/prefix1/teddybear.png");
    teddyimage = teddyimage.scaledToWidth(50);
    teddyimage = teddyimage.scaledToHeight(50);
    setPixmap(teddyimage);
}


