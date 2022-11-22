#include "lose.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>

lose::lose()
{
    //sets losing pic image
    QPixmap limage(":/new/prefix1/lose.png");
    limage = limage.scaledToWidth(500);
    limage =limage.scaledToHeight(500);
    setPixmap(limage);
}
