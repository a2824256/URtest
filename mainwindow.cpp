#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_RobotUR = new HRobotArmUR;
    m_RobotUR->moveToThread(&m_URthread);
    m_URthread.start();
    connect(this,SIGNAL(SigXMovestate(int)),m_RobotUR,SLOT(SlotXMovestate(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_xpos_pressed()
{
    emit SigXMovestate(1);
}
void MainWindow::on_btn_xneg_pressed()
{
    emit SigXMovestate(2);
}
void MainWindow::on_btn_xpos_released()
{
    emit SigXMovestate(0);
}
void MainWindow::on_btn_xneg_released()
{
    emit SigXMovestate(0);
}



