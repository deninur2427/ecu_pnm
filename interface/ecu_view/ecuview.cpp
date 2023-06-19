#include "ecuview.h"
#include "ui_ecuview.h"

ecuView::ecuView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ecuView)
{
    ui->setupUi(this);

    ecuPort = new QSerialPort(this);
    tmrData = new QTimer(this);
    tmrData->stop();

    // update serial port
    serialPortPopulate();
}

ecuView::~ecuView()
{
    delete ui;
}


void ecuView::on_actionQuit_triggered()
{
    QApplication::quit();
}


void ecuView::on_actionAboutQt_triggered()
{
    QApplication::aboutQt();
}


void ecuView::on_actionAbout_triggered()
{
    QMessageBox msgAbout;

    msgAbout.setText("ECU Prototype Interface and Data Mapping.\nEarly Prototype Development");
    msgAbout.setWindowTitle("ECU Interface");
    msgAbout.setIcon(QMessageBox::Information);
    msgAbout.exec();
}

void ecuView::serialPortPopulate(){
    ui->cmbSerialPort->clear();

    foreach (QSerialPortInfo portInfo,QSerialPortInfo::availablePorts()){
        ui->cmbSerialPort->addItem(portInfo.portName());
    }
}

void ecuView::serialDataRead(){
    QByteArray rawData = ecuPort->readAll();

    ui->txtSerialData->insertPlainText(rawData);
    if(ui->txtSerialData->toPlainText().isEmpty()) return;
}

void ecuView::serialDataRequest(){
    ui->txtSerialData->clear();
    QByteArray dataReq = "tps\n";
    ecuPort->write(dataReq);
}


void ecuView::on_btnPortRefresh_clicked()
{
    serialPortPopulate();
}

