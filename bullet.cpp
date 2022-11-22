#include "bullet.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>

Bullet::Bullet()
{
    //sets bullet image
    QPixmap bulletimage(":/new/prefix1/Banana.png");
    bulletimage = bulletimage.scaledToWidth(30);
    bulletimage = bulletimage.scaledToHeight(30);
    setPixmap(bulletimage);
}
