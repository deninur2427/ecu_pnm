#ifndef ECUCALC_H
#define ECUCALC_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
    class ecu;
}

class ecu: public QMainWindow
{
    Q_OBJECT

public:
   explicit ecu(QWidget *parent=0);
   ~ecu();

private:
   Ui::ecu *ui;

   // Injection
   float inj_vol;
   int inj_off_deg;
   int inj_dur_deg;
   int inj_dur_tick;
   int inj_on_deg;
   int inj_on_tick;
   int flow_rate;

   // Ignition
   int ign_off_deg;
   int ign_dur_deg;
   int ign_dur_tick;
   int ign_on_deg;
   int ign_on_tick;

   //Input
   int rpm;
   int tps;

   //Degree to Tick Timer Calibration
   int rps;
   int rot_tick;
   int deg_rot_tick;

private slots:
    void app_about();
    void app_quit();
    void app_help();

    void ecu_calc();
    void ecu_take();
    void ecu_view();
};

#endif
