#include "HConnector.h"
#include <QTimer>
#include "TypeDef.h"
#include <QNetworkProxy>
QMutex m_Mutex(QMutex::NonRecursive);
HTcpSocket::HTcpSocket(QHostAddress serverIp,uint serverPort)
{
    m_serverIp = serverIp;
    m_serverPort = serverPort;
}

HTcpSocket::~HTcpSocket()
{
    //下线消息
    ConnectNotify(false);
}

void HTcpSocket::SlotTryToConnect()
{
    connectToHost(m_serverIp,m_serverPort);
}

void HTcpSocket::SlotWrite(QByteArray byteArray)
{
    write(byteArray);
    flush();
    //qDebug()<<"write socket size = " << byteArray.size();
}



void HTcpSocket::SlotConnected()
{
    this->setSocketOption(QAbstractSocket::KeepAliveOption,1);
    //上线消息
    ConnectNotify(true);
}

void HTcpSocket::ConnectNotify(bool isOnLine)
{
    emit SigConnectState(isOnLine);
}


HConnector::HConnector(bool isServer,QHostAddress serverIp,uint serverPort)
{
    m_bConnect = false ;
    m_isServer = isServer;
    m_serverIp = serverIp;
    m_serverPort = serverPort;
    m_pTcpSocket = NULL ;
    m_pSocketThread = NULL;
    setProxy(QNetworkProxy::NoProxy);
}

void HConnector::incomingConnection(qintptr socketDescriptor )
{
    AddConnector(socketDescriptor);
    m_bConnect = true ;
}

void HConnector::AddConnector(qintptr socketDescriptor)
{
    if (NULL == m_pTcpSocket)
    {
        m_pTcpSocket = new HTcpSocket(m_serverIp,m_serverPort);
        m_pTcpSocket->setProxy(QNetworkProxy::NoProxy);
        connect(m_pTcpSocket,SIGNAL(connected()),this,SLOT(SlotConnectState()));
        connect(m_pTcpSocket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
        connect(m_pTcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SIGNAL(SigStateChanged(QAbstractSocket::SocketState)));
        connect(m_pTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(SlotError(QAbstractSocket::SocketError)));
        connect(this,SIGNAL(SigReconnect()),m_pTcpSocket,SLOT(SlotTryToConnect()));
    }

    if (m_isServer)
    {
        m_pTcpSocket->setSocketDescriptor(socketDescriptor);
    }
    if (false == m_isServer)
    {
        m_pTcpSocket->connectToHost(QHostAddress(HConnector::m_serverIp),HConnector::m_serverPort);
    }
}

void HConnector::SlotError(QAbstractSocket::SocketError socketError)
{
    //下线消息
    m_bConnect = false ;

}

void HConnector::SlotConnectState()
{
    m_bConnect = true;
    emit SigConnected();
}

void HConnector::SlotInit()
{
    Init();
}

bool HConnector::Init()
{
    //分别对服务端、客户端进行初始化处理
    if(HConnector::m_isServer == true)
    {
        if(!listen(QHostAddress(HConnector::m_serverIp),HConnector::m_serverPort))
        {
            return false;
        }
    }
    else
    {
        AddConnector() ;
    }
    return true;
}

bool HConnector::IsConnect()
{
    return m_bConnect ;
}

void HConnector::ReConnect()
{
    emit SigReconnect();
}

void HConnector::SlotWrite(QByteArray byteArray)
{
    if (NULL == m_pTcpSocket)
    {
        return ;
    }
    if (false == m_bConnect)
    {
        return ;
    }
    int ret = m_pTcpSocket->write(byteArray);
    static int nCount = 0 ;
    if (nCount >= 100)
    {
        nCount = 0 ;
    }
    nCount++ ;
}

void HConnector::SlotReadyRead()
{
    if (NULL == m_pTcpSocket)
    {
        return ;
    }
    QByteArray byteArray = m_pTcpSocket->readAll();
    emit SigReadyRead(byteArray);

    static int nCount = 0 ;
    if (nCount >= 100)
    {
        nCount = 0 ;
    }
    nCount++ ;
}

QByteArray HConnector::ReadAll()
{
    m_Mutex.lock();
    QByteArray byteArray = m_ByteArray ;
    m_ByteArray.clear();
    m_Mutex.unlock();
    return  byteArray;
}
