#-------------------------------------------------
#
# Project created by QtCreator 2020-12-17T16:06:33
#
#-------------------------------------------------

QT       += core gui

QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = URtest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    HRobotArmUR.cpp \
    HTcpCommunicateClient.cpp \
    ./TCP/HConnector.cpp \
    HArmRealtime.cpp \
    HConnector.cpp \
    HRobotPressureSensorPrivateBase.cpp \
    HRobotPressureSensorSRI.cpp

HEADERS  += mainwindow.h \
    HRobotArmUR.h \
    HTcpCommunicateClient.h \
    ./TCP/HConnector.h \
    HArmRealtime.h \
    HTestDefine.h \
    driver_global.h \
    HConnector.h \
    HRobotPressureSensorPrivateBase.h \
    HRobotPressureSensorSRI.h

FORMS    += mainwindow.ui
