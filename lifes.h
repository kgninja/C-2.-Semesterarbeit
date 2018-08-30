#include <vector>
#include <QWidget>
#include <QTimer>
#include <QPainter>
using namespace std;

class lifes : public QWidget
{

public:
    lifes(QWidget *parent = 0);
    ~lifes();
    int Boikstarpunkte;
    void punkteUpdate();
    bool spielende;

private:

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QPaintEvent *);
};
