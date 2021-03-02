#include "mainwindow.h"
#include <QApplication>
//#include "HLogManager.h"

int main(int argc, char *argv[])
{
//#ifdef QT_DEBUG
//    HLogManager::Initialize(HLOG_LEVEL_TRACE, true);
//#else
//    HLogManager::Initialize(HLOG_LEVEL_INFO, false);
//#endif

    //HLogManager::GetCommonLog()->Info(HCODE_LOCATION, "Application start-----");


    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
