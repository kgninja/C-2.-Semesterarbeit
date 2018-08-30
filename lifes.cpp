#include <QtGui>
#include <QRect>
#include <QPainter>
#include <QSize>
#include "lifes.h"
#include <iostream>
using namespace std;


lifes::lifes(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(false);
    Boikstarpunkte = 3;
    spielende = false;
}

lifes::~lifes()
{
}
void lifes::resizeEvent(QPaintEvent *event){
}
void lifes::paintEvent(QPaintEvent * )
{
    QPainter painter;
    painter.begin( this );
    for(int i = 0; i < Boikstarpunkte; i++) {
    QPixmap boikstar(":/img/boikstar.jpg");
    int abstand = i * 25;
    painter.drawPixmap(abstand, 0, 15, 20, boikstar);
    painter.setBrush(Qt::NoBrush);
}
    painter.end();
}


void lifes::punkteUpdate(void)
{
    if(Boikstarpunkte >= 1){
    Boikstarpunkte = Boikstarpunkte - 1;
    update();
}
    else {
        spielende = true;
    }
}


