#include "win.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>

win::win()
{
    //sets winning image
    QPixmap wimage(":/new/prefix1/win.png");
    wimage = wimage.scaledToWidth(500);
    wimage =wimage.scaledToHeight(500);
    setPixmap(wimage);
}
