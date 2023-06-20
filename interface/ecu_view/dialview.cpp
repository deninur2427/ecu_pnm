#include "dialview.h"

extern int valTPS;

dialView::dialView(QWidget *parent ):
    QFrame( parent )
{
    QGridLayout *layout = new QGridLayout( this );
    layout->setSpacing( 5 );
    layout->setMargin( 0 );

    QwtDial *dial_tps = createDial( 1 );
    layout->addWidget( dial_tps, 0, 0 );

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
        d_tps->setLabel("Throttle");
        d_tps->setFixedHeight(sizedial);
        d_tps->setFixedWidth(sizedial);

        dial = d_tps;
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
}
