#include "playbox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    playbox w;
    w.setGeometry(100, 100, 800, 600);
    w.show();

    return a.exec();
}
