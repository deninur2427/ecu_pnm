#ifndef ECUVIEW_H
#define ECUVIEW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

#include "dialview.h"

#define USE_REVERSE_INJ 1

#define CDATA           12

QT_BEGIN_NAMESPACE
namespace Ui { class ecuView; }
QT_END_NAMESPACE

class ecuView : public QMainWindow
{
    Q_OBJECT

public:
    ecuView(QWidget *parent = nullptr);
    ~ecuView();

private slots:
    void on_actionQuit_triggered();
    void on_actionAboutQt_triggered();
    void on_actionAbout_triggered();
    void on_btnPortRefresh_clicked();
    void on_btnSerialPort_clicked();

    void serialPortPopulate();
    void serialDataRead();
    void serialDataRequest();

    void on_btnMonitoring_clicked();

private:
    Ui::ecuView *ui;
    QSerialPort *ecuPort;
    QTimer* tmrMonitor;

};
#endif // ECUVIEW_H
