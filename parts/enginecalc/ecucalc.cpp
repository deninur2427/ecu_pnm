#include "ecucalc.h"
#include "ui_ecucalc.h"

int inj_data_off_deg[7]={10,12,14,16,18,20,25};
int inj_data_dur_deg[7]={25,30,40,50,60,70,80};
int data_tps[7]={0,250,500,750,1000,1250};

int ign_data_off_deg[7]={10,12,15,18,19,20,21};
int data_rpm[7]={0,1000,2000,3000,4000,5000,6000};

ecu::ecu(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ecu)
{
    ui->setupUi(this);

    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(app_about()));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(app_quit()));
    connect(ui->actionHelp,SIGNAL(triggered()),this,SLOT(app_help()));
    connect(ui->actionCalc,SIGNAL(triggered()),this,SLOT(ecu_calc()));

    ui->txtRPM->setText("1000");
    ui->txtTPS->setText("200");
}

ecu::~ecu()
{
    delete ui;
}

void ecu::app_about(){
    QApplication::aboutQt();
    return;
}

void ecu::app_quit(){
    QApplication::quit();
}

void ecu::app_help(){
    QString pesan="";

    pesan+= "Platform chibiOS dengan timer GPT frekuensi 10khz \r\n";
    pesan+= "maka setiap tick berdurasi 1/10000 second \r\n \r\n";
    pesan+= "Totaltooth 24-1 dengan TMA 9 dan TMB 21\r\n";

    QMessageBox::information(this,"Bantuan",pesan);
    return;
}

void ecu::ecu_take(){
    ign_dur_deg=30;

    flow_rate=40;

    rpm=ui->txtRPM->text().toInt();
    tps=ui->txtTPS->text().toInt();
}

void ecu::ecu_view(){
    ui->txtFlow->setText(QString::number(flow_rate)+ " mm3/s");
    ui->txtInjVol->setText(QString::number(inj_vol)+ " mm3");
    ui->txtDurasiInjT->setText(QString::number(inj_dur_tick)+ " tick");
    ui->txtDurasiInjD->setText(QString::number(inj_dur_deg)+ " deg");
    ui->txtOffInjD->setText(QString::number(inj_off_deg)+ " deg");
    ui->txtOnInjD->setText(QString::number(inj_on_deg)+ " deg");
    ui->txtOnInjT->setText(QString::number(inj_on_tick)+ " tick");

    ui->txtDurasiIgnDeg->setText(QString::number(ign_dur_deg)+ " deg");
    ui->txtDurasiIgnT->setText(QString::number(ign_dur_tick)+ " tick");
    ui->txtOffIgnDeg->setText(QString::number(ign_off_deg)+ " deg");
    ui->txtOnIgnDeg->setText(QString::number(ign_on_deg)+ " deg");
    ui->txtOnIgnT->setText(QString::number(ign_on_tick)+ " tick");
}

void ecu::ecu_calc(){
    int i;

    ecu_take();

    rps=rpm/60;
    rot_tick=10000/rps;
    deg_rot_tick=rot_tick/360;

    // Injection
    for(i=0;i<5;i++){
       if((tps>=data_tps[i])&&(tps<data_tps[i+1])){
           inj_dur_deg=inj_data_dur_deg[i]+ ((inj_data_dur_deg[i+1]-inj_data_dur_deg[i])*(tps-data_tps[i])/(data_tps[i+1]-data_tps[i]));
           inj_off_deg=inj_data_off_deg[i]+ ((inj_data_off_deg[i+1]-inj_data_off_deg[i])*(tps-data_tps[i])/(data_tps[i+1]-data_tps[i]));
       }
    };

    if(tps<data_tps[0]){
       inj_dur_deg=inj_data_dur_deg[0];
       inj_off_deg=inj_data_off_deg[0];
    }

    if(tps>=data_tps[5]){
       inj_dur_deg=inj_data_dur_deg[5];
       inj_off_deg=inj_data_off_deg[5];
    }

    inj_on_deg=180-inj_dur_deg-inj_off_deg;

    inj_dur_tick=inj_dur_deg*deg_rot_tick;
    inj_on_tick =inj_on_deg*deg_rot_tick;

    inj_vol= (float) flow_rate*inj_dur_tick/10000;


    // Ignition
    for(i=0;i<5;i++){
       if((rpm>=data_rpm[i])&&(rpm<data_rpm[i+1])){
           ign_off_deg=ign_data_off_deg[i]+ ((ign_data_off_deg[i+1]-ign_data_off_deg[i])*(rpm-data_rpm[i])/(data_rpm[i+1]-data_rpm[i]));
       }
    };

    if(rpm<data_rpm[0]){
       ign_off_deg=ign_data_off_deg[0];
    }

    if(rpm>=data_rpm[5]){
       ign_off_deg=ign_data_off_deg[5];
    }

    ign_on_deg=180-ign_dur_deg-ign_off_deg;

    ign_dur_tick=ign_dur_deg*deg_rot_tick;
    ign_on_tick=ign_on_deg*deg_rot_tick;

    ecu_view();
    return;
}

