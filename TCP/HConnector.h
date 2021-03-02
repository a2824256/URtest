#ifndef HDEVICESOCKET_H
#define HDEVICESOCKET_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>

class HTcpSocket : public QTcpSocket
{
Q_OBJECT
public:
    HTcpSocket(QHostAddress serverIp,uint serverPort);
    ~HTcpSocket();

    //上、下线通知
    void ConnectNotify(bool isOnLine);
private:

    QByteArray m_bufferData;
signals:
    void SigConnectState(bool);
public slots:
    void SlotWrite(QByteArray byteArray);
    //连接成功
    void SlotConnected();

    //网络断开，尝试重新连接
    void SlotTryToConnect();
private:
    QHostAddress m_serverIp;
    uint m_serverPort;
};

class  HConnector : public QTcpServer
{
    Q_OBJECT
public:
    HConnector(bool isServer,QHostAddress serverIp,uint serverPort);
    void incomingConnection(qintptr socketDescriptor );
    void AddConnector(qintptr socketDescriptor = NULL);
    bool Init();
    bool IsConnect();
    void ReConnect();
    QByteArray ReadAll();
signals:
    void SigConnected();
    void SigReadyRead(QByteArray);
    void SigReconnect();
    void SigStateChanged(QAbstractSocket::SocketState);
public slots:
    void SlotConnectState();
    void SlotInit();
    //连接断开
    void SlotError(QAbstractSocket::SocketError);
private slots:
    void SlotWrite(QByteArray);
    void SlotReadyRead();
private:
    HTcpSocket* m_pTcpSocket;
    QThread     *m_pSocketThread;
public:
    bool         m_isServer;
    QHostAddress m_serverIp;
    uint         m_serverPort;
    bool m_bConnect ;
    QByteArray m_ByteArray ;
    QMutex m_Mutex;
};

#endif // HDEVICESOCKET_H
