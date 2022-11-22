#include <QDebug>
#include "minion.h"
#include "qobjectdefs.h"
#include "teddy.h"
#include "bullet.h"
#include "enemy.h"
#include "dislife.h"
#include "win.h"
#include "lose.h"
#include <QTimer>
#include <QTimerEvent>
#include <QImage>

minion::minion(int boardData[15][15], Bullet * b[4], enemy *e[2], Teddy *t[2], door *d[1], dislife *h[4], win *w[1], lose *l[1], QGraphicsTextItem *text,QGraphicsTextItem *text2 )
{
    // Sets minion Image
    QPixmap minionimage(":/new/prefix1/minion.png");
    minionimage = minionimage.scaledToWidth(50);
    minionimage = minionimage.scaledToHeight(50);
    setPixmap(minionimage);

    // specifies and defines the pointers created in the main
    this->e=e;
    this->b = b ;
    this->t=t;
    this->d=d;
    this->h=h;
    this->w=w;
    this->l=l ;
    this->text=text;
    this->text2=text2;
    this->timer2=new QTimer();

    // Set Position
    row = 7;
    column = 7;
    setPos(50 + column * 50, 50 + row * 50);

    // Set data Array
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            data[i][j] = boardData[i][j];
}

// returns player to his orignal image
void minion::minionreturn ()
{
    QPixmap minionimage(":/new/prefix1/minion.png");
    minionimage = minionimage.scaledToWidth(50);
    minionimage = minionimage.scaledToHeight(50);
    setPixmap(minionimage);
    very_cool = false;
    text->setPlainText("Status:Normal") ;
    timer0.stop();
    timer2->stop();
    text2->setPlainText("Not Powered Yet") ;
}

//returns all items back to their positions when player loses a life
void minion::reset()
{
    b[0]->setPos(50 + 1 * 50, 50 + 1 * 50);
    scene()->addItem(b[0]);
    b[1]->setPos(50 + 13 * 50, 50 + 1 * 50);
    scene()->addItem(b[1]);
    b[2]->setPos(50 + 1 * 50, 50 + 13 * 50);
    scene()->addItem(b[2]);
    b[3]->setPos(50 + 13 * 50, 50 + 13 * 50);
    scene()->addItem(b[3]);

    setPos(50 + 7 * 50, 50 + 7 * 50);
    row = 7;
    column = 7;

    e[0]->setPos(50 + 13 * 50, 50 + 2 * 50);
    scene()->addItem(e[0]);
    e[1]->setPos(50 + 13 * 50, 50 + 10 * 50);
    scene()->addItem(e[1]);
}

// returns all postions when player loses the whole game
void minion::reset_all()
{
    qDebug("mklmfkeml");
    b[0]->setPos(50 + 1 * 50, 50 + 1 * 50);
    scene()->addItem(b[0]);
    b[1]->setPos(50 + 13 * 50, 50 + 1 * 50);
    scene()->addItem(b[1]);
    b[2]->setPos(50 + 1 * 50, 50 + 13 * 50);
    scene()->addItem(b[2]);
    b[3]->setPos(50 + 13 * 50, 50 + 13 * 50);
    scene()->addItem(b[3]);

    e[0]->setPos(50 + 13 * 50, 50 + 2 * 50);
    scene()->addItem(e[0]);
    e[1]->setPos(50 + 13 * 50, 50 + 10 * 50);
    scene()->addItem(e[1]);
    setPos(50 + 7 * 50, 50 + 7 * 50);

    t[0]->setPos(50 + 4 * 50, 50 + 5 * 50);
    scene()->addItem(t[0]);
    qDebug("tedsfsft minion3");
    t[1]->setPos(50 + 10 * 50, 50 + 11 * 50);
    scene()->addItem(t[1]);
    qDebug("tedsfsft minion4");

    t[0]->setPos(50 + 4 * 50, 50 + 5 * 50);
    scene()->addItem(t[0]);

    t[1]->setPos(50 + 10 * 50, 50 + 11 * 50);
    scene()->addItem(t[1]);
}

// handles the decrease in health of the enemy as well as the shortest distance of the enemy to player to kill
void minion:: killenemy()
{
    float d1=10000 ;
    float d2= 10000 ;

   if (!e[0]->dead)
   {
    d1= getdistance(e[0]) ;
   }

   if (!e[1]->dead)
   {
    d2= getdistance(e[1]) ;
   }

    bool di = d2<d1 ;

    if (e[di]->health ==1)
    {
        e[di]->dead = true;
        count++;
        scene()->removeItem(e[di]);
        return;
    }
    else
    {
        e[di]->health --;
        return ;
    }
}

// removes the hearts on screen as lives are lost
void minion ::hearts()
{
    if (lives==2)
    {
    scene()->removeItem(h[0]);
    }
    if (lives==1)
    {
    scene()->removeItem(h[1]);
    }
    if (lives==0)
    {
        scene()->removeItem(h[2]);
    }
}

// gets the distance between two points through the manhattan method
float  minion:: getdistance(enemy*e)
{
    int x = e->row ;
    int y = e->column ;
    return abs((this->row-x)+(this->column-y)) ;
}

// timer starts a counter so we're able to output a string on the screen
void minion :: updateCountdown()
{
   text2-> setPlainText(QString::number(timer0.remainingTime()/1000));
}

// Movement code for player as well as controls all player occurances when a key is pressed
void minion::keyPressEvent(QKeyEvent* event)
{

    if (event->key() == Qt::Key_Up && data[row - 1][column] < 0)
    {
        row--;
    }
    else if (event->key() == Qt::Key_Down && data[row + 1][column] < 0)
    {
        row++;
    }
    else if (event->key() == Qt::Key_Right && data[row][column + 1] < 0)
    {
        column++;
    }
    else if (event->key() == Qt::Key_Left && data[row][column - 1] < 0)
    {
        column--;
    }
    setPos(50 + column * 50, 50 + row * 50);

//handles the collison when the player collidies with a power pellet and tranfsorms , as well sets the text for when player is in invinciable mode
    QList<QGraphicsItem*> items = collidingItems();
    for (int i = 0; i < items.size(); i++)
    {
        if (typeid(*items[i]) == typeid(Teddy))
        {
            timer0.start(10000);
            very_cool= true;
            scene()->removeItem(items[i]);
            QPixmap strongimage(":/new/prefix1/strongminion.png");
            strongimage =strongimage.scaledToWidth(70);
            strongimage = strongimage.scaledToHeight(70);
            setPixmap(strongimage);
            text->setPlainText("Status:Invinsible") ;
            timer2->start();
            connect(timer2, SIGNAL(timeout()), this, SLOT(updateCountdown()));
            timer0.connect(&timer0, SIGNAL(timeout()), this , SLOT(minionreturn()));

        }
    }

//handles the collison when the player collidies with a bullet
    QList<QGraphicsItem*> items1 = collidingItems();
    for (int i = 0; i < items1.size(); i++)
    {
        if (typeid(*items1[i]) == typeid(Bullet))
        {
            timer1.start(1000);
            scene()->removeItem(items[i]);

            QPixmap gunminion(":/new/prefix1/largegun.png");
            gunminion =gunminion.scaledToWidth(50);
            gunminion = gunminion.scaledToHeight(50);
            setPixmap(gunminion);
            timer1.connect(&timer1, SIGNAL(timeout()), this , SLOT(minionreturn())) ;
            killenemy();
        }

    }

//handles the collison when the player collidies with an enemy and loses a life , which calls the heart function to decrease a life on screen
    QList<QGraphicsItem*> items2 = collidingItems();
    for (int i = 0; i < items2.size(); i++)
    {
       if (typeid(*items2[i]) == typeid(enemy))
       {
            if(very_cool)
            {
                continue;
            }
            else if (lives!=0)
            {
               lives -- ;
               hearts() ;
               reset();
            }

        if (lives<=0)
        {
            scene()->addItem(l[0]);
            l[0]->setPos(50 + -2 * 50, 50 + -2 * 50);
        }
       }
    }

    if (count==2)
    {
        scene()->addItem(d[0]);
        d[0]->setPos(50 + 6 * 50, 50 + 7 * 50);
    }

//handles the collison when the player collidies door then removes player and outputs the winning image
    QList<QGraphicsItem*> items4 = collidingItems();
    for (int i = 0; i < items4.size(); i++)
    {
        if (typeid(*items4[i]) == typeid(door))
        {
            scene()->addItem(w[0]);
            w[0]->setPos(50 + -2 * 50, 50 + -2 * 50);
            scene()->removeItem(this);
        }
    }
}
