#ifndef HROBOTPRESSURESENSOROPTO_H
#define HROBOTPRESSURESENSOROPTO_H
#include <QObject>
#include <QMutex>
#include "HConnector.h"
#include <QUdpSocket>
#include "HRobotPressureSensorPrivateBase.h"

typedef struct ResponseStruct {
    unsigned int sequenceNumber;
    unsigned int sampleCounter;
    unsigned int status;
    double fx;
    double fy;
    double fz;
    double tx;
    double ty;
    double tz;
} Response;

class HRobotPressureSensorSRI:public HRobotPressureSensorPrivateBase
{
    Q_OBJECT
public:
    HRobotPressureSensorSRI();
    ~HRobotPressureSensorSRI();
    bool GetPressureSensorInfo(double &x, double& y, double& z);
//    void Check();
    void SetNeedToCalibration(bool bCalibration);

private:
    void SendCommand();
    bool ParseData(QByteArray byteArray);
    double LowPassFilter_RC_1order(double Vi, double Vo_p, double sampleFrq, double CutFrq);
private:
    QUdpSocket *m_UdpSocket;
    QByteArray m_SensorData ;
    bool m_bNeedCalibration;
    Response m_Response;
    Response m_ResponseCalibration;
    QAbstractSocket::SocketState m_SocketState ;
    HPressureInfo m_PressureInfo;
    int m_nNoDataCount ;
    int m_nDataError ;
    int m_iSriAngle;
    QMutex m_Mutex;

signals:
    void SigWrite(QByteArray);
    void SigSendCommand(qint16 command, qint32 data) ;
    void SigReconnect();
    void SigInit();
public slots:
    void SlotStateChanged(QAbstractSocket::SocketState);
    void SlotReadData();
    void SlotConnected();
};

#endif // HROBOTPRESSURESENSOROPTO_H
