#include "HRobotPressureSensorSRI.h"
#include <QtEndian>
#include <Windows.h>
//#include "HTcpCommunicateClient.h"
#include "qdebug.h"
#include <winsock.h>
//#include "../Alarm/HAlarmMgr.h"
#include <QNetworkProxy>
#include <QNetworkDatagram>
#include "TypeDef.h"
#define DATA_LEN    62
#define PI 3.1415926
#define SAMPLE_FREQUENCY 500 
#define CUT_FREQUENCY 10
union packet
{
    float f;
    quint8 buf[4];
};


HRobotPressureSensorSRI::HRobotPressureSensorSRI()
    :HRobotPressureSensorPrivateBase(), m_Mutex(QMutex::NonRecursive)
{
    qRegisterMetaType<QAbstractSocket::SocketState>("SocketState");
    m_nNoDataCount = 0 ;
    m_nDataError = 0 ;
    m_bNeedCalibration = true;
    m_iSriAngle = 45;
    memset(&m_ResponseCalibration,0,sizeof(Response));
    memset(&m_Response,0,sizeof(Response));

    m_SocketState = QAbstractSocket::UnconnectedState;

    QString IP = "193.169.10.5";
    int Port =4008 ;



#if 0
    m_pConnect = new HConnector(false,QHostAddress(IP),Port);
    connect(m_pConnect,SIGNAL(SigReadyRead(QByteArray)),this,SLOT(SlotReadData(QByteArray)));
    connect(m_pConnect,SIGNAL(SigConnected()),this,SLOT(SlotConnected()));
    connect(m_pConnect,SIGNAL(SigStateChanged(QAbstractSocket::SocketState)),this,SLOT(SlotStateChanged(QAbstractSocket::SocketState)));

    connect(this,SIGNAL(SigInit()),m_pConnect,SLOT(SlotInit()));

    connect(this,SIGNAL(SigWrite(QByteArray)),m_pConnect,SLOT(SlotWrite(QByteArray)));
#endif

    m_UdpSocket = new QUdpSocket(this);
    m_UdpSocket->bind(Port) ;
    m_UdpSocket->setProxy(QNetworkProxy::NoProxy);
    connect(m_UdpSocket,SIGNAL(connected()),this,SLOT(SlotConnected()));
    connect(m_UdpSocket,SIGNAL(readyRead()),this,SLOT(SlotReadData()));
    connect(m_UdpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(SlotStateChanged(QAbstractSocket::SocketState)));

    m_UdpSocket->connectToHost(QHostAddress(IP),Port);
#if 0
    QThread* pSocketThread = new QThread;
    m_UdpSocket->moveToThread(pSocketThread);
    pSocketThread->start();
#endif
    //emit SigInit();
}

HRobotPressureSensorSRI::~HRobotPressureSensorSRI()
{
    if (NULL != m_UdpSocket)
    {
        m_UdpSocket->write(QByteArray("AT+GSD=STOP\r\n"));
        m_UdpSocket->deleteLater();
    }
}

void HRobotPressureSensorSRI::SendCommand()//设置输出格式
{
    QByteArray message("AT+SGDM=(A01,A02,A03,A04,A05,A06);E;1;(WMA:1,1,1,1)\r\n");
    emit SigWrite(message);
    Sleep(300);
    //QByteArray smpr("AT+SMPR=2000\r\n");
    //emit SigWrite(smpr);
    //Sleep(300);
    QByteArray str = "AT+GSD\r\n";
    emit SigWrite(str);
}

void HRobotPressureSensorSRI::SlotConnected()
{
    m_SocketState = QAbstractSocket::ConnectedState;
	
    QByteArray str = "AT+GSD\r\n";
    m_UdpSocket->write(str) ;
}

void HRobotPressureSensorSRI::SlotReadData()
{
    m_Mutex.lock();
    m_nNoDataCount = 0 ;
    m_SensorData.clear();
    m_SensorData.append(m_UdpSocket->receiveDatagram().data()) ;
    m_Mutex.unlock();
}

void HRobotPressureSensorSRI::SlotStateChanged(QAbstractSocket::SocketState state)
{
    m_Mutex.lock();
    m_SocketState = state ;
    m_Mutex.unlock();
}

void HRobotPressureSensorSRI::SetNeedToCalibration(bool bCalibration)
{
    if (m_bNeedCalibration != bCalibration)
    {
        m_bNeedCalibration = bCalibration ;
    }
}

#define EPSILON 0.0001
//非INF数据  3.40282e+38
#define ERR_DATA_LIMIT 3.0e+38

bool HRobotPressureSensorSRI::GetPressureSensorInfo(double &x, double& y, double& z)
{

    static bool bFirst = false;
    m_Mutex.lock();
    if (!bFirst)
    {
        //第一次运行清空之前的数据
        bFirst = true ;
        m_SensorData.clear();
        m_Mutex.unlock();
        return false;
    }
    if (m_SensorData.isEmpty())
    {
        m_nNoDataCount ++ ;
        m_Mutex.unlock();
        return false ;
    }
    m_nNoDataCount = 0 ;
    QByteArray byteArray = m_SensorData.toHex().toUpper();
    m_SensorData.clear();
    m_Mutex.unlock();

   if (ParseData(byteArray))
   {
            double fx = (m_Response.fx) ;
            double fy = (m_Response.fy) ;
            double fz = (m_Response.fz) ;
            //double tx = (m_Response.tx-m_ResponseCalibration.tx) ;
            //double ty = (m_Response.ty-m_ResponseCalibration.ty) ;
            //double tz = (m_Response.tz-m_ResponseCalibration.tz) ;

            double fxo, fyo, fzo;
            double sampleFrq = SAMPLE_FREQUENCY;//采样频率500HZ
            double CutFrq = CUT_FREQUENCY; //截止频率10HZ

            static double fxo_pre = 0;
            static double fyo_pre = 0;
            static double fzo_pre = 0;

            fxo = LowPassFilter_RC_1order(fx, fxo_pre, sampleFrq, CutFrq);
            fyo = LowPassFilter_RC_1order(fy, fyo_pre, sampleFrq, CutFrq);
            fzo = LowPassFilter_RC_1order(fz, fzo_pre, sampleFrq, CutFrq);

            fxo_pre = fxo;
            fyo_pre = fyo;
            fzo_pre = fzo;

            x = fxo;
            y = fyo;
            z = fzo;

            return true;
    }
   else
   {
       return false;
   }


}


/**
* @brief  implement 1 order RC low pass filter
*         raw data filtered by a simple RC low pass filter with cut off frequency = CutFrq
* @param  Vi        : Vi(k)
* @param  Vo        : Vo(k)
* @param  Vo_p      : Vo(k-1)
* 参考https://blog.csdn.net/qq_27158179/article/details/82661297
*/
double HRobotPressureSensorSRI::LowPassFilter_RC_1order(double Vi, double Vo_p, double sampleFrq, double CutFrq)
{
    double Vo;
    double RC, Cof1, Cof2;

    RC = (double)1.0 / 2.0 / PI / CutFrq;
    Cof1 = 1 / (1 + RC*sampleFrq);
    Cof2 = RC*sampleFrq / (1 + RC*sampleFrq);
    Vo = Cof1 * (Vi)+Cof2 * (Vo_p);

    return Vo;
}

bool HRobotPressureSensorSRI::ParseData(QByteArray byteArray)
{
    QString strData;
    if (byteArray.length() < DATA_LEN)
    {
        return false;
    }
    while (byteArray.size() >= DATA_LEN)
    {
        if (byteArray.startsWith("AA55001B"))
        {
            strData = byteArray.left(DATA_LEN);
            byteArray.remove(0, DATA_LEN);
        }
        else
        {
            byteArray.remove(0, 1); // 删除头部字符
        }
    }
    bool ok;
    if(strData.length() == DATA_LEN)
    {
        packet m_x,m_y,m_z;
        packet m_Tx, m_Ty, m_Tz;

        m_x.buf[0] = (quint8)(strData.mid(12,2).toUShort(&ok,16));
        m_x.buf[1] = (quint8)(strData.mid(14,2).toUShort(&ok,16));
        m_x.buf[2] = (quint8)(strData.mid(16,2).toUShort(&ok,16));
        m_x.buf[3] = (quint8)(strData.mid(18,2).toUShort(&ok,16));

        m_y.buf[0] = (quint8)(strData.mid(20,2).toUShort(&ok,16));
        m_y.buf[1] = (quint8)(strData.mid(22,2).toUShort(&ok,16));
        m_y.buf[2] = (quint8)(strData.mid(24,2).toUShort(&ok,16));
        m_y.buf[3] = (quint8)(strData.mid(26,2).toUShort(&ok,16));

        m_z.buf[0] = (quint8)(strData.mid(28,2).toUShort(&ok,16));
        m_z.buf[1] = (quint8)(strData.mid(30,2).toUShort(&ok,16));
        m_z.buf[2] = (quint8)(strData.mid(32,2).toUShort(&ok,16));
        m_z.buf[3] = (quint8)(strData.mid(34,2).toUShort(&ok,16));

        m_Tx.buf[0] = (quint8)(strData.mid(36, 2).toUShort(&ok, 16));
        m_Tx.buf[1] = (quint8)(strData.mid(38, 2).toUShort(&ok, 16));
        m_Tx.buf[2] = (quint8)(strData.mid(40, 2).toUShort(&ok, 16));
        m_Tx.buf[3] = (quint8)(strData.mid(42, 2).toUShort(&ok, 16));

        m_Ty.buf[0] = (quint8)(strData.mid(44, 2).toUShort(&ok, 16));
        m_Ty.buf[1] = (quint8)(strData.mid(46, 2).toUShort(&ok, 16));
        m_Ty.buf[2] = (quint8)(strData.mid(48, 2).toUShort(&ok, 16));
        m_Ty.buf[3] = (quint8)(strData.mid(50, 2).toUShort(&ok, 16));

        m_Tz.buf[0] = (quint8)(strData.mid(52, 2).toUShort(&ok, 16));
        m_Tz.buf[1] = (quint8)(strData.mid(54, 2).toUShort(&ok, 16));
        m_Tz.buf[2] = (quint8)(strData.mid(56, 2).toUShort(&ok, 16));
        m_Tz.buf[3] = (quint8)(strData.mid(58, 2).toUShort(&ok, 16));
        //m_Response.fx = m_x.f;
        //m_Response.fy = m_y.f;

        m_Response.fx = m_x.f * cos(m_iSriAngle * PI / 180) + m_y.f * sin(m_iSriAngle * PI / 180);
        m_Response.fy = -m_x.f * sin(m_iSriAngle * PI / 180) + m_y.f * cos(m_iSriAngle * PI / 180);

        m_Response.fz = m_z.f;
        m_Response.tx = m_Tx.f;
        m_Response.ty = m_Ty.f;
        m_Response.tz = m_Tz.f;

        static int nCount = 0 ;
        if (nCount >= 1000)
        {
            nCount = 0 ;
        }
        nCount++ ;

//         if ( (fabs(m_Response.fx - 0xFFFFFFFF80000000) < EPSILON) ||
//              (fabs(m_Response.fy - 0xFFFFFFFF80000000) < EPSILON) ||
//              (fabs(m_Response.fz - 0xFFFFFFFF80000000) < EPSILON))

        if ( (m_Response.fx > ERR_DATA_LIMIT) ||
            (m_Response.fy > ERR_DATA_LIMIT) ||
            (m_Response.fz > ERR_DATA_LIMIT))
        {
            m_nDataError++ ;
            return false ;
        }
        else
        {
            m_nDataError = 0 ;
        }

        strData.clear();
    }
    return true ;
}

//void HRobotPressureSensorSRI::Check()
//{
//    H_ALARM_OPERATE operate = H_ALARM_NULL;

//    m_Mutex.lock();
//    operate = (m_nNoDataCount >= 500) ? H_ALARM_ADD : H_ALARM_DELETE;
//    m_Mutex.unlock();
//    HAlarmMgr::GetInstance()->OperateAlarm(H_ALARM_LEVEL_HIGH,H_ALARM_SIX_DIMENSIONAL_FORCE_SENSOR_ERROR,operate);

//    m_Mutex.lock();
//    operate =  (m_nDataError >= 500) ? H_ALARM_ADD : H_ALARM_DELETE;
//    m_Mutex.unlock();
//    HAlarmMgr::GetInstance()->OperateAlarm(H_ALARM_LEVEL_HIGH,H_ALARM_SIX_DIMENSIONAL_FORCE_SENSOR_DATA_ERROR,operate);
//}
