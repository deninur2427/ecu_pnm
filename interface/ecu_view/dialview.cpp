#include "dialview.h"

extern int valTPS;
extern int valRPM;
extern int valCrank;

dialView::dialView(QWidget *parent ):
    QFrame( parent )
{
    QGridLayout *layout = new QGridLayout( this );
    layout->setSpacing( 5 );
    layout->setMargin( 0 );

    QwtDial *dial_tps = createDial(1);
    layout->addWidget( dial_tps, 0, 0 );

    QwtDial *dial_rpm = createDial(2);
    layout->addWidget( dial_rpm, 0, 1 );

    QwtDial *dial_rot = createDial(3);
    layout->addWidget( dial_rot, 0, 2 );

    for (int i = 0; i < layout->columnCount(); i++ ) layout->setColumnStretch( i, 1 );
    for (int i = 0; i < layout->rowCount(); i++ ) layout->setRowStretch( i, 1 );

    tmrUpdateValue = new QTimer(this);
    connect(tmrUpdateValue,SIGNAL(timeout()),this,SLOT(updateValue()));
    tmrUpdateValue->start(100);
}

QwtDial* dialView::createDial(int pos){
    QwtDial *dial = NULL;

    switch( pos ){

    case 1: {
        d_tps = new dialMeter(this);
        d_tps->setScaleStepSize( 10.0 );
        d_tps->setScale( 0.0, 100.0 );
        d_tps->scaleDraw()->setPenWidthF(2);
        d_tps->setLabel("TPS");
        d_tps->setFixedHeight(sizedial);
        d_tps->setFixedWidth(sizedial);
        d_tps->clearFocus();
        d_tps->setAttribute(Qt::WA_TransparentForMouseEvents);

        dial = d_tps;
        break;
    }
    case 2: {
        d_rpm = new dialMeter(this);
        d_rpm->setScaleStepSize( 500.0 );
        d_rpm->setScale( 0.0, 4000.0 );
        d_rpm->scaleDraw()->setPenWidthF(2);
        d_rpm->setLabel("RPM");
        d_rpm->setFixedHeight(sizedial);
        d_rpm->setFixedWidth(sizedial);
        d_rpm->clearFocus();
        d_rpm->setAttribute(Qt::WA_TransparentForMouseEvents);

        dial = d_rpm;
        break;
    }
    case 3: {
        d_rot = new clockMeter(this);
        d_rot->setScaleStepSize( 1.0 );
        d_rot->setScale( 0.0, 24.0 );
        d_rot->scaleDraw()->setPenWidthF(2);
        d_rot->setLabel("Rotation");
        d_rot->setFixedHeight(sizedial);
        d_rot->setFixedWidth(sizedial);
        d_rot->clearFocus();
        d_rot->setAttribute(Qt::WA_TransparentForMouseEvents);

        //d_rot->setOrigin(285); // 270+15 following degree of cranktooth
        d_rot->setOrigin(90);

        dial = d_rot;
        break;
    }

    }

    if (dial)
    {
        dial->setReadOnly( true );
        dial->setLineWidth( 4 );
        dial->setFrameShadow( QwtDial::Sunken );
    }

    return dial;
}

void dialView::updateValue(){
    d_tps->setValue(valTPS);
    d_rpm->setValue(valRPM);
    d_rot->setValue(valCrank);
}
