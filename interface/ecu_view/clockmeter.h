#ifndef CLOCKMETER_H
#define CLOCKMETER_H

#include <QString>

#include <qpainter.h>
#include <qwt_dial.h>
#include <qwt_dial_needle.h>
#include <qwt_round_scale_draw.h>

class clockMeter: public QwtDial
{
protected:
    virtual void drawScaleContents( QPainter *painter,const QPointF &center, double radius ) const;

private:
    QString d_label;

public:
    clockMeter(QWidget *parent=NULL);
    void setLabel(const QString &);
};

#endif /* CLOCKMETER_H */

