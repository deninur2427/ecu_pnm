#ifndef DIALVIEW_H
#define DIALVIEW_H

#include <QTimer>
#include <QFrame>
#include <QLayout>

#include "dialmeter.h"

#define sizedial 250

class QwtDial;
class dialMeter;

class dialView: public QFrame
{
    Q_OBJECT

public:
    dialView(QWidget *parent = NULL);

private:
    QwtDial *createDial( int pos );

    dialMeter* d_tps;
    dialMeter* d_rpm;

    QTimer* tmrUpdateValue;

private slots:
    void updateValue();
};


#endif // DIALVIEW_H
