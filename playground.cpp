#include <QtGui>
#include <QRect>
#include <QPainter>
#include <QSize>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>
#include "playground.h"
using namespace std;


playground::playground(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(118, 238, 198)));
    setAutoFillBackground(true);
    setMouseTracking(false);
    this->geschwindigkeit = 0;
    this->geschwindigkeitLinks = true;
    this->KGspieler= new KGSpieler;
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    letztesX=100;
    letztesY=100;
    erhoehen=0;
    QSize size = this->size();
    this->Breite = size.width();
    this->Hoehe = size.height();
    KGspieler->x = this->Breite - 50;
    KGspieler->y = this->Hoehe - 50;
    KGspieler->size=50;
    punkte = 0;
    getroffen = false;

}

playground::~playground()
{
}
void playground::paintEvent(QPaintEvent * )
{
    QPainter painter;

    vector<struct kleineBoikstars *>::iterator pos,start;
    start = KGGegner.begin();

    painter.begin( this );

    painter.setBrush(Qt::BDiagPattern);
    painter.drawRect(this->KGspieler->x, this->KGspieler->y, this->KGspieler->size, 50);
    painter.setBrush(Qt::NoBrush);

    for (pos=start; pos!= KGGegner.end(); pos++)
    {
        if((*pos)->y > Hoehe) {
            KGGegner.erase(pos);
            punkte=punkte+5;
        } else {
            int x = (*pos)->x;
            int y = (*pos)->y;
            int breite = (*pos)->breite;
            int hoehe = (*pos)->hoehe;
            if(x > KGspieler->x && x <= (KGspieler->x + KGspieler->size) && (y > KGspieler->y && y <= (KGspieler->y + KGspieler->size))) {
                punkte = punkte - 50;
                getroffen = true;
                KGGegner.erase(pos);
            }
        }
        QPixmap boikstar(":/img/boikstar.jpg");
        painter.drawPixmap((*pos)->x, (*pos)->y, (*pos)->breite, (*pos)->hoehe, boikstar);
        //painter.setBrush(Qt::white);
        //painter.drawEllipse((*pos)->x,(*pos)->y,(*pos)->radius,(*pos)->radius);

    }
    painter.end();
}

void playground::resizeEvent(QPaintEvent *event){

    QSize size = this->size();
    this->Breite = size.width();
    this->Hoehe = size.height();
    KGspieler->x = ((int) this->Breite / 2 )- ((int)this->KGspieler->size / 2);
    KGspieler->y = this->Hoehe - 70;

    update();
}

void playground::bewegungLinks(){

    if(!this->geschwindigkeitLinks) {
        this->geschwindigkeit = 0;
        this->geschwindigkeitLinks = true;
    }

    int x = this->KGspieler->x -5 - (this->geschwindigkeit / 2);

    if(this->geschwindigkeit >= 25) {
        this->geschwindigkeit = 25;
    }

    this->geschwindigkeit = this->geschwindigkeit + 5;

    if(x < 0){
        x = this->Breite;
    }

    this->KGspieler->x = x;
    update();
}

void playground::bewegungRechts(){

    if(this->geschwindigkeitLinks) {
        this->geschwindigkeit = 0;
        this->geschwindigkeitLinks = false;
    }

    int x = this->KGspieler->x +5 + (this->geschwindigkeit / 2);

    if(geschwindigkeit > 25) {
        geschwindigkeit = 25;
    }

    this->geschwindigkeit = this->geschwindigkeit + 5;

    if((x + this->KGspieler->size) > Breite){
        x = 0 - this->KGspieler->size;
    }

    this->KGspieler->x = x;
    update();
}


void playground::KGspielstandspeicherung() {
    vector<struct kleineBoikstars *>::iterator pos,start;
    start = KGGegner.begin();

    ofstream file;
    file.open("speicherstand.kg");

    for (pos=start; pos!= KGGegner.end(); pos++) {
        int objX = (*pos)->x;
        int objY = (*pos)->y;
        file << "Boikstars | " << objX << " | " << objY << endl;
    }

    file << "Punkte" << " | " << punkte << endl;
    int playerX = KGspieler->x;
    int playerY = KGspieler->y;
    file << "KGSpieler | " << playerX << " | " << playerY << endl;
    file.close();
}

void playground::KGladendesSpielstands(){
    KGGegner.clear();
    std::ifstream in("speicherstand.kg", std::ifstream::in);

    if(!in) {
      cout << "Spielstand kann nicht wieder erzeugt werden.";
      return;
    }

    char str[255];

    while(in) {
        in.getline(str, 255);
        stringstream ss(str);
        string toks[3];
        string sep = " | ";
        ss >> toks[0] >> sep >> toks[1] >> sep >> toks[2];

        if(toks[0] == "KGSpieler"){
            KGspieler->x=stoi(toks[1]);
            KGspieler->y=stoi(toks[2]);
        }

        else if(toks[0]== "Punkte"){

            punkte = stoi(toks[1]);

}
        else{
        struct kleineBoikstars *object;
                object=new kleineBoikstars;

                object->breite=15;
                object->hoehe=20;
                if(toks[1] == "" || toks[2] == "") {
                    continue;
                }
                object->x = stoi(toks[1]);
                object->y = stoi(toks[2]);

                KGGegner.push_back(object);
        }
}

    in.close();
    update();
}

void playground::neuesObjekt()
{

    if(KGGegner.size() > 10) {

        return;
    }

    int x =  0 + ( std::rand() % ( Breite - 0 + 1 ) );
    struct kleineBoikstars *object;
    object=new kleineBoikstars;

    object->breite=15;
    object->hoehe=20;
    object->x = x;
    object->y = 0 - object->hoehe;

    KGGegner.push_back(object);
    update();
}

void playground::ObjektBewegung(void)
{

    vector<struct kleineBoikstars *>::iterator pos,start;
    start = KGGegner.begin();

        for (pos=start; pos!= KGGegner.end(); pos++){

            (*pos)->y=(*pos)->y + 5;
            update();
        }
}

