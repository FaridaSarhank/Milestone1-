#ifndef ENEMY_H
#define ENEMY_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QDebug>
#include <QPainter>
#include "lose.h"

class enemy : public QObject,  public QGraphicsPixmapItem
{
  Q_OBJECT
private :

    int data[15][15];

public:
    int health=2 ;
    bool dead = false;
    QPixmap vectorimage ;
    enemy(int boardData[15][15],int r , int c,lose *l[1]);
    int row, column;
    lose **l ;

public slots :
   void move() ; // handels enemy moving fuctionaility (through rand)
};

#endif // ENEMY_H
