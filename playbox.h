#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "playground.h"
#include "lifes.h"

class playbox : public QWidget
{
    Q_OBJECT

public:
    playbox(QWidget *parent = 0);

private:
    playground *myPlayground;
    lifes *Lifes;
    QPushButton *startstopButton;
    QLabel *Points;
    bool isStarted;
    QTimer *erzeugeObjektTimer;
    QTimer *bewegeObjektTimer;
    void punkte();
    void Startzustandaenderung();

private slots:
    void stopppen(void);
    void starten(void);
    void startstop(void);
    void bewegung(void);
    void objekt(void);
    void speichern(void);
    void laden(void);


protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void resizeEvent (QPaintEvent *);


};
