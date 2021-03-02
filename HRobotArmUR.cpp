#include "HRobotArmUR.h"
#include "HTcpCommunicateClient.h"
#include <string.h>
#include <QDebug>
#include "Windows.h"
#include <sstream>
#include "Eigen/Dense"
#include "QNetworkInterface"
//#include "HLogManager.h"

HRobotArmUR::HRobotArmUR()
{
    m_currentX = 0;
    m_currentY = 0;
    m_currentZ = 0;
    Xmove_state = 0;
    m_pConnect = new HConnector(true,QHostAddress("193.169.10.120"),30000);
    connect(m_pConnect,SIGNAL(SigReadyRead(QByteArray)),this,SLOT(SlotReadyRead(QByteArray)));
    connect(this,SIGNAL(SigInitSocket()),m_pConnect,SLOT(SlotInit()));
    QThread* pSocketThread = new QThread;
    m_pConnect->moveToThread(pSocketThread);
    pSocketThread->start(QThread::HighPriority);
    emit SigInitSocket();
    connect(this,SIGNAL(SigWrite(QByteArray)),m_pConnect,SLOT(SlotWrite(QByteArray)));

    m_pRealtimeThread = new QThread;
    QString Ip = "193.169.10.50";
    int port = 30003;  
    //m_pSensorSRI = new HRobotPressureSensorSRI();
    //fx_zero = 0;
    //fy_zero = 0;
    //fz_zero = 0;
    //fx = 0;
    //fy = 0;
    //fz = 0;

}

HRobotArmUR::~HRobotArmUR()
{

}
void HRobotArmUR::SlotReadyRead(QByteArray byteArray)
{
    double step = 0.0005;
    bool ok;
    QString p = QVariant(byteArray).toString();
    QString p_remove;
    p_remove = (p.remove(0, 2)).remove(']');
    QStringList list_p = p_remove.split(QChar(','));
    static double ztest = 0;


    static double px = 0;
    static double py = 0;
    static double pz = 0;
    if (list_p.count() == 20)
    {
        px = list_p[15].toDouble(&ok);
        py = list_p[16].toDouble(&ok);
        pz = list_p[17].toDouble(&ok);

    }
    /*
        static bool IsFirstGet = true;
    double x = 0;
    double y = 0;
    double z = 0;
    if (m_pSensorSRI->GetPressureSensorInfo(x, y, z))
    {
        
        if (IsFirstGet)
        {
            static int count = 0;
            count++;
            if (count > 100)
            {
                fx_zero = x;
                fy_zero = y;
                fz_zero = z;
                IsFirstGet = false;
}


        }
        else
        {
            fx = x - fx_zero;
            fy = y - fy_zero;
            fz = -(z - fz_zero);

            if (fz<1)
            {
                ztest = ztest + step;
            }
            else
            {
                qDebug() << "dayu1";
            }
        }
    }
    */


    
    //static double z = 0;
    //if (fz < 1)
    //{
    //    z = z + 0.002;
    //}

    double x_send = 0, y_send = 0, z_send = 0, rx_send = 0, ry_send = 0, rz_send = 0;
    static double a = 0;
    if (Xmove_state ==1)
    {
        //x_send = px + 0.004;
        a = a + 0.002;
        //qDebug() << "1111";
    }
    else if(Xmove_state ==2)
    {
        //x_send = px - 0.004;
        a = a - 0.002;
        //qDebug() << "2222";

    }
    else
    {
        //x_send = px;
        //qDebug() << "00000";
    }
    x_send = a;
    //static int i = 0;    
    //if (i < 50)
    //{
    //    /*if (i==0)
    //    {
    //        qDebug() << "111send_x=" << a;
    //        qDebug() << "111current_x=" << m_currentX;
    //    }*/
    //    a = a + 0.002;
    //}
    //else if (i < 100)
    //{
    //    /*if (i == 50)
    //    {
    //        qDebug() << "222send_x=" << a;
    //        qDebug() << "222current_x=" << m_currentX;
    //    }*/
    //    a = a - 0.002;
    //}
    //else if(i<400)
    //{
    //    /*if (i == 100)
    //    {
    //        qDebug() << "333send_x=" << a;
    //        qDebug() << "333current_x=" << m_currentX;
    //    }
    //    if (i == 200)
    //    {
    //        qDebug() << "444send_x=" << a;
    //        qDebug() << "444current_x=" << m_currentX;
    //    }
    //    if (i == 300)
    //    {
    //        qDebug() << "555send_x=" << a;
    //        qDebug() << "555current_x=" << m_currentX;
    //    }*/
    //    
    //}
    //else
    //{
    //    i = -1;
    //}
    //i++;
   
    //static bool Isstop = false;
    //static double stop_z = 0;
    //if (!Isstop)
    //{
    //    z_send = ztest;
    //    if (fz > 1)
    //    {
    //        Isstop = true;
    //        stop_z = pz;
    //    }

    //}
    //else
    //{
    //    z_send = stop_z;

    //}
    //z_send = ztest;
    //HLogManager::GetCommonLog()->CollectData(HCODE_LOCATION, LOG_COLLECTION_TYPE_0," z_send= %f, z_true = %f ", z_send,pz);
    

    QByteArray arrayMove ;
    QString strMoveMessage ;
    strMoveMessage = "(";
    strMoveMessage += QString::number(x_send);
    strMoveMessage += ",";
    strMoveMessage += QString::number(y_send);
    strMoveMessage += ",";
    strMoveMessage += QString::number(z_send);
    strMoveMessage += ",";
    strMoveMessage += QString::number(rx_send);
    strMoveMessage += ",";
    strMoveMessage += QString::number(ry_send);
    strMoveMessage += ",";
    strMoveMessage += QString::number(rz_send);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);

    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);

    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);
    strMoveMessage += ",";
    strMoveMessage += QString::number(0);

    strMoveMessage += ")\n";

    arrayMove = strMoveMessage.toLatin1();

    SendData(arrayMove);
}

void HRobotArmUR::SendData(QByteArray array)
{
    emit SigWrite(array);
}

void HRobotArmUR::SlotXMovestate(int state)
{
    Xmove_state = state;
}

void HRobotArmUR::SltRecvData(double x, double y, double z, \
    double rx, double ry, double rz)
{
    qDebug() << QTime::currentTime()<< m_currentX;

    m_currentX = x;
    m_currentY = y;
    m_currentZ = z;

}
