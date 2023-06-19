#include "ecuview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ecuView w;
    w.show();
    return a.exec();
}
