#include <vector>
#include <QWidget>
#include <QTimer>
#include <QPainter>
using namespace std;

class playground : public QWidget
{
public:
    playground(QWidget *parent = 0);
    ~playground();

    struct KGSpieler *KGspieler;
    enum drawType { square, circle };
    void neuesObjekt(void);
    void start(void) { timer->start(1); erhoehen=1; }
    void stop(void) { timer->stop(); erhoehen=0; }
    void ObjektBewegung(void);
    void bewegungRechts(void);
    void bewegungLinks(void);
    void KGspielstandspeicherung();
    void KGladendesSpielstands();
    bool getroffen;
    int punkte;

private:
    QTimer *timer;
    QTimer *neuesObjektTimer;
    int Breite;
    int Hoehe;
    int erhoehen;
    int letztesX;
    int letztesY;  
    int geschwindigkeit;
    bool geschwindigkeitLinks;

    vector<struct kleineBoikstars *> KGGegner;

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent (QPaintEvent *);

};

struct kleineBoikstars
{
    int x, y;
    int breite;
    int hoehe;
    int phase;
    int verschiebung_;
};

struct KGSpieler {

    int x, y, size;

};


