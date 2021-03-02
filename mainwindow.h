#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <HRobotArmUR.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    HRobotArmUR  *m_RobotUR;
    QThread   m_URthread;

private slots:
    void on_btn_xpos_pressed();
    void on_btn_xneg_pressed();
    void on_btn_xpos_released();
    void on_btn_xneg_released();

signals:
    void SigXMovestate(int state);
};

#endif // MAINWINDOW_H
