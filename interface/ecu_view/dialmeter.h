#ifndef DIALMETER_H
#define DIALMETER_H

#include <QString>

#include <qwt_dial.h>
#include <qpainter.h>
#include <qwt_dial.h>
#include <qwt_dial_needle.h>
#include <qwt_round_scale_draw.h>

class dialMeter: public QwtDial
{
public:
    dialMeter(QWidget *parent = NULL);
    void setLabel(const QString &);

protected:
    virtual void drawScaleContents( QPainter *painter,const QPointF &center, double radius ) const;

private:
    QString d_label;
};

#endif // DIALMETER_H
