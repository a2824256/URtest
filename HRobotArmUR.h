#ifndef __H_HRobotArmUR_H__
#define __H_HRobotArmUR_H__

#include <QObject>
#include "./TCP/HConnector.h"
#include <QTimer>
#include <QMutex>
#include "TypeDef.h"
#include "HArmRealtime.h"
#include "HRobotPressureSensorSRI.h"
typedef struct
{
    float       x;
    float       y;
    float       z;
    float       Rx;
    float       Ry;
    float       Rz;
    float       ProbeType;
    float       Coup;
    float       StopBit;
    float       reserve1;
    float       reserve2;
    float       reserve3;
    float       reserve4;
    float       reserve5;
    float       reserve6;
    float       reserve7;
    float       reserve8;
    float       reserve9;
    float       reserve10;
    float       reserve11;
}H_ROBOT_MOVE_DATA;

class HTcpCommunicateClient;
class HRobotArmUR:public QObject
{
	Q_OBJECT
public:
    HRobotArmUR();
    virtual ~HRobotArmUR();
    HTcpCommunicateClient* TCPSocketInit(int portNum);
    void SendData(QByteArray array);
 private:
    HConnector* m_pConnect ;
    int Xmove_state;
    HArmRealtime *m_pArmRealtime;
    QThread      *m_pRealtimeThread;  //获取机械臂实时数据
    double m_currentX;
    double m_currentY;
    double m_currentZ;
    HRobotPressureSensorSRI* m_pSensorSRI;
    double fx;
    double fy;
    double fz;
    double fx_zero;
    double fy_zero;
    double fz_zero;
signals:
    void SigInitSocket();
    void SigWrite(QByteArray);

public slots:
    void SlotReadyRead(QByteArray);
    void SlotXMovestate(int);
    void SltRecvData(double x, double y, double z, \
        double rx, double ry, double rz);

};

#endif // __H_HRobotArmDazu_H__
