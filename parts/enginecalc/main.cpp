#include "ecucalc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ecu w;
    w.show();

    return a.exec();
}
