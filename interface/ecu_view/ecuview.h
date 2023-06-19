#ifndef ECUVIEW_H
#define ECUVIEW_H

#include <QMainWindow>
#include <QMessageBox>

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

private:
    Ui::ecuView *ui;
};
#endif // ECUVIEW_H
