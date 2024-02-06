#include "ecuview.h"
#include "ui_ecuview.h"

int valTPS = 0;
int limTPS[2]={5,3050};

int valRPM = 0;
int valCrank = 0;

int limInj[2]={7,200};

int defInj[CDATA][CDATA]={
#if USE_REVERSE_INJ
    {	48,	50,	57,	97,	97,	97,	97,	97,	88,	88,	88,	88},
    {	47,	49,	54,	97,	97,	97,	97,	97,	88,	88,	88,	88},
    {	45,	48,	52,	55,	57,	59,	64,	64,	74,	81,	82,	84},
    {	44,	47,	51,	53,	56,	59,	62,	62,	74,	79,	82,	84},
    {	42,	45,	50,	52,	55,	57,	62,	62,	69,	75,	77,	80},
    {	40,	42,	47,	48,	50,	52,	57,	57,	62,	70,	72,	74},
    {	38,	40,	44,	46,	48,	51,	54,	56,	63,	67,	70,	74},
    {	36,	38,	43,	45,	48,	50,	52,	54,	61,	65,	68,	70},
    {	29,	32,	36,	38,	40,	43,	45,	47,	54,	58,	60,	62},
    {	28,	30,	34,	37,	39,	41,	43,	45,	52,	56,	59,	61},
    {	26,	29,	33,	35,	37,	40,	42,	44,	51,	55,	57,	59},
    {	44,	26,	13,	 4,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0}
#else
    {	44,	26,	13,	 4,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0},
    {	26,	29,	33,	35,	37,	40,	42,	44,	51,	55,	57,	59},
    {	28,	30,	34,	37,	39,	41,	43,	45,	52,	56,	59,	61},
    {	29,	32,	36,	38,	40,	43,	45,	47,	54,	58,	60,	62},
    {	36,	38,	43,	45,	48,	50,	52,	54,	61,	65,	68,	70},
    {	38,	40,	44,	46,	48,	51,	54,	56,	63,	67,	70,	74},
    {	40,	42,	47,	48,	50,	52,	57,	57,	62,	70,	72,	74},
    {	42,	45,	50,	52,	55,	57,	62,	62,	69,	75,	77,	80},
    {	44,	47,	51,	53,	56,	59,	62,	62,	74,	79,	82,	84},
    {	45,	48,	52,	55,	57,	59,	64,	64,	74,	81,	82,	84},
    {	47,	49,	54,	97,	97,	97,	97,	97,	88,	88,	88,	88},
    {	48,	50,	57,	97,	97,	97,	97,	97,	88,	88,	88,	88}
#endif
};

int defIgn[CDATA][CDATA]={
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30},
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}
};

ecuView::ecuView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ecuView)
{
    ui->setupUi(this);

    ui->tblInj->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblInj->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tblIgn->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblIgn->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tabMain->addTab(new dialView, "Monitoring");

    ecuPort = new QSerialPort(this);
    tmrMonitor = new QTimer(this);
    tmrMonitor->stop();

    ecuPort->setBaudRate(QSerialPort::Baud9600);
    ecuPort->setDataBits(QSerialPort::Data8);
    ecuPort->setStopBits(QSerialPort::OneStop);
    ecuPort->setFlowControl(QSerialPort::NoFlowControl);
    ecuPort->setParity(QSerialPort::NoParity);
    ecuDataMode = SERIAL_MODE_INFO;
    ecuReqFlag = SERIAL_IDLE;

    // update serial port
    serialPortPopulate();

    connect(ecuPort,SIGNAL(readyRead()),this,SLOT(serialDataRead()));
    connect(tmrMonitor,SIGNAL(timeout()),this,SLOT(serialDataRequest()));
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

    serialDataParsing(ui->txtSerialData->toPlainText(),ecuDataMode);
    ecuReqFlag = SERIAL_IDLE;
}

void ecuView::serialDataRequest(){
    ui->txtSerialData->clear();

    QByteArray dataReq = "basic\r";
    ecuDataMode = SERIAL_MODE_INFO;

    if(ecuReqFlag==SERIAL_IDLE){
        ecuPort->write(dataReq);
        ecuReqFlag = SERIAL_WAIT;
    }
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
        ui->cmbSerialPort->setEnabled(true);
    }
}

void ecuView::on_btnMonitoring_clicked()
{
    QString strBtnName = ui->btnMonitoring->text();

    if(strBtnName=="Start Monitoring"){
        if(ecuPort->isOpen()) {
            tmrMonitor->start(100);
            ui->btnMonitoring->setText("Stop Monitoring");
            ui->statusbar->showMessage("Engine Monitor Dial Started");
        }
        else{
            ui->statusbar->showMessage("Open Serial Port First");
        }
    }
    else{
        tmrMonitor->stop();
        ui->btnMonitoring->setText("Start Monitoring");
        ui->statusbar->showMessage("Engine Monitor Dial Stopped");
    }
}

void ecuView::serialDataParsing(QString strData, int modeData){
    QStringList dataVals = strData.split(",");

    switch (modeData) {

    case SERIAL_MODE_INFO: {
        if(dataVals.count()<3) break;

        int adcTPS = dataVals[0].toInt();
        valTPS = (adcTPS - limTPS[0]) * 100 / (limTPS[1] - limTPS[0]);
        valRPM = dataVals[1].toInt();
        valCrank = dataVals[2].toInt();
    }

    default:
        break;
    }
}

