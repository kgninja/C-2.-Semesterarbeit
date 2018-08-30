#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QEvent>
#include <QKeyEvent>
#include <iostream>
#include <fstream>
#include <QString>
#include <QtGui>
#include "playbox.h"
using namespace std;


playbox::playbox(QWidget *parent)
    : QWidget(parent)
{
    this->isStarted = true;
    QPushButton *loadButton = new QPushButton(tr("Laden"));
    loadButton->setFocusPolicy(Qt::NoFocus);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(laden()));

    QPushButton *safeButton = new QPushButton(tr("Speichern"));
    safeButton->setFocusPolicy(Qt::NoFocus);
    connect(safeButton, SIGNAL(clicked()), this, SLOT(speichern()));

    startstopButton = new QPushButton(tr("Start"));
    startstopButton->setFocusPolicy(Qt::NoFocus);
    connect(startstopButton, SIGNAL(clicked()), this, SLOT(startstop()));

    QLabel *lifeLabel = new QLabel(this);
    lifeLabel->setText("Leben:");
    myPlayground = new playground;
    Lifes = new lifes;
    Points = new QLabel(this);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(Points, 0, 1);
    gridLayout->addWidget(safeButton, 0, 2);
    gridLayout->addWidget(loadButton, 0, 3);
    gridLayout->addWidget(startstopButton, 0, 4);
    gridLayout->addWidget(lifeLabel, 0, 5);
    gridLayout->addWidget(Lifes, 0, 6);
    gridLayout->addWidget(myPlayground, 1, 0, 6, 8);
    setLayout(gridLayout);
    erzeugeObjektTimer= new QTimer(this);
    connect(erzeugeObjektTimer, SIGNAL(timeout()), this, SLOT(objekt()));
        erzeugeObjektTimer->start(500);

    bewegeObjektTimer= new QTimer(this);
    connect(bewegeObjektTimer, SIGNAL(timeout()), this, SLOT(bewegung()));
        bewegeObjektTimer->start(20);

}


void playbox::resizeEvent(QPaintEvent *event){

}

void playbox::keyPressEvent(QKeyEvent *event)
{

}

void playbox::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        this->Startzustandaenderung();
    }

    if(event->key() == Qt::Key_Left) {
        if(isStarted){
            this->myPlayground->bewegungLinks();
        }
    }
    if(event->key() == Qt::Key_Right)
    {
        if(isStarted){
            this->myPlayground->bewegungRechts();

        }
    }
}


void playbox::Startzustandaenderung(void) {
    this->isStarted = !this->isStarted;
    if(this->isStarted) {
        this->startstopButton->setText("Start");
        this->erzeugeObjektTimer->start(150);
        this->bewegeObjektTimer->start(20);
    } else {
        this->startstopButton->setText("Pause");
        this->erzeugeObjektTimer->stop();
        this->bewegeObjektTimer->stop();
    }
}
void playbox::speichern(){
    if(isStarted) {
        Startzustandaenderung();
    }
    myPlayground->KGspielstandspeicherung();
}

void playbox::laden(){

   if(isStarted) {
       Startzustandaenderung();
   }
   myPlayground->KGladendesSpielstands();
   this->punkte();
}

void playbox::starten(void)
{
    myPlayground->start();
}

void playbox::stopppen(void)
{
    myPlayground->stop();
}

void playbox::startstop(void) {
    Startzustandaenderung();
}


void playbox::objekt(void){

    myPlayground->neuesObjekt();
 }

void playbox::bewegung(void){

if(myPlayground->getroffen){
    Lifes->punkteUpdate();

    myPlayground->getroffen=false;
}

    myPlayground->ObjektBewegung();
    punkte();

    if(Lifes->spielende) {
        qApp->quit();
    }
}

void playbox::punkte(){
    Points->setText("Boikstarpunkte: " + QString::number(myPlayground->punkte));
}


