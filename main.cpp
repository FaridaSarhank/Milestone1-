#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QDebug>
#include "door.h"
#include "minion.h"
#include "enemy.h"
#include "teddy.h"
#include "bullet.h"
#include "dislife.h"
#include "win.h"
#include "lose.h"
#include "QTimer"
#include <QPlainTextEdit>
#include <QTextEdit>

int main(int argc, char *argv[] )
{
    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene scene;

    //sets text on screen
    QFont *f = new QFont;
    f->setPointSize(20);
    f->setBold(true);
    QGraphicsTextItem *text = scene.addText("Status:Normal");
    text->setPos(600,00);
    text->setFont(*f);
    text->setDefaultTextColor(QColor(QColorConstants::Svg::lightpink));
    QGraphicsTextItem *text2 = scene.addText("Not Powered Yet");
    text2->setPos(100, 00);
    text2->setFont(*f);
    text2->setDefaultTextColor(QColor(QColorConstants::Svg::lightpink));

    //sets street image as the background for the scene
    QPixmap streetimage(":/new/prefix1/street.png");
    streetimage = streetimage.scaledToWidth(50);
    streetimage = streetimage.scaledToHeight(50);
    view.setFixedSize(1000,900);
    view.setWindowTitle("GTA Game");
    QBrush brush(Qt::darkBlue);
    view.setBackgroundBrush(streetimage);

    //reads from the board file and creates a 15 by 15 array on it
    QFile file(":/new/prefix1/board.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    int boardData[15][15];

    QString temp;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j <15; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }

    //creates images to be displayed on the pix map
    QPixmap borderupimage(":/new/prefix1/wall.png");
    borderupimage = borderupimage.scaledToWidth(70);
    borderupimage = borderupimage.scaledToHeight(50);

    QPixmap borderimage(":/new/prefix1/borders - down.png");
    borderimage = borderimage.scaledToWidth(30);
    borderimage = borderimage.scaledToHeight(30);

    QPixmap girlsimage(":/new/prefix1/girls.png");
    girlsimage = girlsimage.scaledToWidth(50);
    girlsimage = girlsimage.scaledToHeight(50);

    QPixmap gruimage(":/new/prefix1/gru.png");
    gruimage = gruimage.scaledToWidth(50);
    gruimage = gruimage.scaledToHeight(50);

    QPixmap treeimage(":/new/prefix1/tree2.png");
    treeimage =  treeimage.scaledToWidth(50);
    treeimage =  treeimage.scaledToHeight(50);

    QPixmap fireimage(":/new/prefix1/firehydrant.png");
    fireimage = fireimage.scaledToWidth(50);
    fireimage = fireimage.scaledToHeight(50);

    QPixmap carimage(":/new/prefix1/car.png");
    carimage = carimage.scaledToWidth(50);
    carimage = carimage.scaledToHeight(50);

    QPixmap houseimage(":/new/prefix1/house.png");
    houseimage = houseimage.scaledToWidth(50);
    houseimage = houseimage.scaledToHeight(50);

    QPixmap pinkimage(":/new/prefix1/pinky.png");
    pinkimage = pinkimage.scaledToWidth(50);
    pinkimage = pinkimage.scaledToHeight(50);

    QPixmap Gimage(":/new/prefix1/G.png");
    Gimage = Gimage.scaledToWidth(50);
    Gimage = Gimage.scaledToHeight(50);

    QGraphicsPixmapItem boarditems[15][15];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15 ; j++)
        {
            //Set Image on array in certain specified places on the board
            if (boardData[i][j] == 1)
                boarditems[i][j].setPixmap(borderupimage);
            else if (boardData[i][j] == 70)
                boarditems[i][j].setPixmap(girlsimage);
            else if (boardData[i][j] == 2)
                boarditems[i][j].setPixmap(Gimage);
            else if (boardData[i][j] == 71)
                boarditems[i][j].setPixmap(gruimage);
            else if (boardData[i][j] == 72)
                boarditems[i][j].setPixmap(fireimage);
            else if (boardData[i][j] == 73)
                 boarditems[i][j].setPixmap(carimage);
            else if (boardData[i][j]==-2)
                boarditems[i][j].setPixmap(houseimage);
            else if (boardData[i][j] == -3)
                boarditems[i][j].setPixmap(pinkimage);

             // Set Position
             boarditems[i][j].setPos(50+ j * 50, 50 + i * 50);

             // Add to the Scene
             scene.addItem(&boarditems[i][j]);
        }

    //sets the position of each image
    Bullet banana1;
    banana1.setPos(50 + 1 * 50, 50 + 1 * 50);
    scene.addItem(&banana1);

    Bullet banana2 ;
    banana2.setPos(50 + 13 * 50, 50 + 1 * 50);
    scene.addItem(&banana2);

    Bullet banana3;
    banana3.setPos(50 + 1 * 50, 50 + 13 * 50);
    scene.addItem(&banana3);

    Bullet banana4;
    banana4.setPos(50 + 13 * 50, 50 + 13 * 50);
    scene.addItem(&banana4);
    Bullet*b  [4] ={&banana1,&banana2,&banana3,&banana4};

    Teddy teddy1;
    teddy1.setPos(50 + 4 * 50, 50 + 5 * 50);
    scene.addItem(&teddy1);

    Teddy teddy2;
    teddy2.setPos(50 + 10 * 50, 50 + 11 * 50);
    scene.addItem(&teddy2);
    Teddy*t[2]={&teddy1, &teddy2};

    QTimer timer;

    lose l1;
    lose *l[1] = {&l1};
    enemy e1(boardData,13,2,l);
    scene.addItem(&e1);

    //a timer that calls the enemy move function so that it is always moving
    enemy e2(boardData,13,10,l);
    scene.addItem(&e2);
    timer.start(100) ;
    timer.connect(&timer, SIGNAL(timeout()), &e1 , SLOT(move()));
    timer.connect(&timer, SIGNAL(timeout()), &e2 , SLOT(move()));

    dislife heart1;
    dislife heart2;
    dislife heart3;
    dislife *h [3]={&heart1,&heart2,&heart3};

    heart1.setPos(50 + -1 * 50, 50 + -1 * 50);
    scene.addItem(&heart1);

    heart2.setPos(50 + -1 * 50, 50 + -2 * 50);
    scene.addItem(&heart2);

    heart3.setPos(50 + -1 * 50, 50 + -3 * 50);
    scene.addItem(&heart3);

    //classes called and objects made to make the passing of player easier
    enemy *e [2] = {&e1,&e2};

    door d1;
    door *d[1]={&d1};

    win w1;
    win *w[1]={&w1};


    minion player(boardData,b,e,t,d,h,w,l,text,text2);
    scene.addItem(&player);
    player.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    player.setFocus();
    view.setScene(&scene);
    view.show();
    return a.exec();
}


