#include "enemy.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "minion.h"
#include "lose.h"

enemy::enemy(int boardData[15][15], int r, int c,lose *l[1])
{
    //sets enemy image
    QPixmap vectorimage(":/new/prefix1/vector.png");
    vectorimage = vectorimage.scaledToWidth(50);
    vectorimage = vectorimage.scaledToHeight(50);
    setPixmap(vectorimage);

    row = r;
    column = c;
    this->l=l ;

    // Set data Array
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            data[i][j] = boardData[i][j];
}

// Movement code for enemy works with a rand that generates a number and based on that the enemy moves up , down , right , left
void enemy::move()
{
    int d =rand()%4 ;


    if (d == 0 && data[row - 1][column] < 0)
    {
        row--;
    }
    else if (d== 1 && data[row + 1][column] < 0)
    {
        row++;
    }
    else if (d == 2 && data[row][column + 1] < 0)
    {
        column++;
    }
    else if (d == 3 && data[row][column - 1] < 0)
    {
        column--;
    }
    setPos(50 + column * 50, 50 + row * 50);

// handles the colliosion of when the enemy collides into player and accordingly decreases lives and resets both the variable and function are passed through dynamic casting
   QList<QGraphicsItem*> items2 = collidingItems();
    for (int i = 0; i < items2.size(); i++)
    {
        if (typeid(*items2[i]) == typeid(minion))
        {
            minion * m = dynamic_cast<minion*>(items2[i]);
            if(m->very_cool)
            {
                continue;
            }
             else
            {
              m->lives -- ;
              m-> hearts();
              m->reset();
             }
            if (m->lives<= 0)
            {
                scene()->addItem(l[0]);
                l[0]->setPos(50 + -2 * 50, 50 + -2 * 50);
            }
        }
    }
}
