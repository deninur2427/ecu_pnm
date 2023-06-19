#include "ecuview.h"
#include "ui_ecuview.h"

ecuView::ecuView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ecuView)
{
    ui->setupUi(this);
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

