#include "HTcpCommunicateClient.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
//#include "pubfun.h"
#include <QNetworkProxy>

const int TIME_OUT = 1* 660;

HTcpCommunicateClient::HTcpCommunicateClient()
	: m_targetIP("")
    , m_targetPort(0)
	, m_IsSubThread(false) // caller::new()
{
	m_isLongConn = true;
	m_isSuccConn = false;
    m_socketClient = new QTcpSocket;
    m_socketClient->setProxy(QNetworkProxy::NoProxy);
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(SlotTimeout()));
    connect(this,SIGNAL(SigRequest(const char*, int)),this,SLOT(SlotRequest(const char*, int)));
    connect(this,SIGNAL(SigRequest(const QString)),this,SLOT(SlotRequest(const QString)));

    connect(m_socketClient,SIGNAL(readyRead()),this,SLOT(SlotReadData()));
    connect(m_socketClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SlotError(QAbstractSocket::SocketError)));
    connect(m_socketClient, SIGNAL(connected()), this, SLOT(SltConnected()));
    m_pTimer->start(US_RECONNECT_TIME);
}

HTcpCommunicateClient::HTcpCommunicateClient(const QString & IP, int port)
	: m_targetIP(IP)
	, m_targetPort(port)
    , m_socketClient(NULL)
	, m_IsSubThread(true) // newThread::start()
{
	m_isLongConn = true;
	m_isSuccConn = false;
    m_pTimer = NULL ;
}

HTcpCommunicateClient::~HTcpCommunicateClient()
{	
    if (m_socketClient != NULL)
    {
        delete m_socketClient;
        m_socketClient = NULL;
    }
}

void HTcpCommunicateClient::SlotTimeout()
{
    if (!m_isSuccConn)
    {
        TcpConnect();
    }
    else
    {
        m_pTimer->stop();
    }
}

void HTcpCommunicateClient::SltConnected()
{
    m_isSuccConn = true ;
    m_pTimer->stop();
}

void HTcpCommunicateClient::SlotError(QAbstractSocket::SocketError)
{
    m_isSuccConn = false ;
    //TcpConnect();
    if(!m_pTimer->isActive())
    {
        m_pTimer->start(US_RECONNECT_TIME);
    }
}

bool HTcpCommunicateClient::TcpConnect()
{
    if (m_isSuccConn)
    {
        return true ;
    }
    if (NULL == m_socketClient || m_targetIP.isEmpty() || m_targetPort == 0)
    {
        return false;
    }
    m_socketClient->connectToHost(m_targetIP, m_targetPort);
    if (!m_socketClient->waitForConnected(10))
    {
            m_isSuccConn = false;
            emit SendConnectState(m_isSuccConn);
            return false;
    }
    //lsAdd
    m_isSuccConn = true;
    emit SendConnectState(m_isSuccConn);
    m_socketClient->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    return true;
}

bool HTcpCommunicateClient::TcpDisconnect()
{
    if (NULL == m_socketClient )
    {
        return false;
    }
    m_socketClient->disconnectFromHost();
    m_socketClient->waitForDisconnected(TIME_OUT);
    m_isSuccConn = false;
    emit SendConnectState(m_isSuccConn);
    return true;
}

void HTcpCommunicateClient::SetTarget(const QString & IP, int port)
{

    m_targetIP = IP;
    m_targetPort = port;
}

void HTcpCommunicateClient::ReadConnectState()
{
    if (NULL == m_socketClient )
    {
        return ;
    }
    while (m_socketClient->bytesAvailable() < 255)
    {
        if (!m_socketClient->waitForReadyRead(TIME_OUT))
        {
            if (!m_isLongConn)
                disconnect();
            break ;
        }
    }
    m_socketClient->readAll();
}

void HTcpCommunicateClient::Request(const char* SendData, int ilen)
{
    emit SigRequest(SendData,ilen);
}

void HTcpCommunicateClient::Request(const QString cmd)
{
    emit SigRequest(cmd);
}

void HTcpCommunicateClient::SlotRequest(const QString array)
{
    SlotRequest(array.toLatin1(),array.length());
}


void HTcpCommunicateClient::SlotRequest(const char* SendData, int ilen)
{
    if (NULL == m_socketClient )
    {
        return ;
    }
    if (!m_isSuccConn)
    {
         return ;
    }
    int writeLen = m_socketClient->write((char*)SendData, ilen);
    if(m_socketClient->waitForBytesWritten(TIME_OUT))
        qt_noop(); // 空语句
    if (writeLen <= 0)
    {

        //qDebug() << "write error";
        return ;
    }
    return ;
}

void HTcpCommunicateClient::SlotReadData()
{
    QByteArray byteArray = m_socketClient->readAll();
    emit SigReadyRead(byteArray);
}

bool HTcpCommunicateClient::IsConnect()
{
    return m_isSuccConn;
}
