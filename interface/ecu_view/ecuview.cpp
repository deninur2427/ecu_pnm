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

    ecuPort->setBaudRate(QSerialPort::Baud38400);
    ecuPort->setDataBits(QSerialPort::Data8);
    ecuPort->setStopBits(QSerialPort::OneStop);
    ecuPort->setFlowControl(QSerialPort::NoFlowControl);
    ecuPort->setParity(QSerialPort::NoParity);

    // update serial port
    serialPortPopulate();

    connect(ecuPort,SIGNAL(readyRead()),this,SLOT(serialDataRead()));
    connect(tmrData,SIGNAL(timeout()),this,SLOT(serialDataRequest()));
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
    QByteArray dataReq = "tps\r";
    ecuPort->write(dataReq);
}


void ecuView::on_btnPortRefresh_clicked()
{
    serialPortPopulate();
}


void ecuView::on_btnSerialPort_clicked()
{
    QString strBtnName = ui->btnSerialPort->text();
    ecuPort->setPortName(ui->cmbSerialPort->currentText());

    if(strBtnName=="Open"){
        if(ecuPort->open(QIODevice::ReadWrite)){
            ui->statusbar->showMessage("Serial Opened");
            ui->btnSerialPort->setText("Close");
            tmrData->start(100);
            ui->cmbSerialPort->setEnabled(false);
        }
        else{
            ui->statusbar->showMessage("Serial Opening Failed");
        }
    }
    else if(strBtnName=="Close"){
        if(ecuPort->isOpen()) ecuPort->close();
        ui->btnSerialPort->setText("Open");
        ui->statusbar->showMessage("Serial Closed");
        tmrData->stop();
        ui->cmbSerialPort->setEnabled(true);
    }
}

