#ifndef __H__HTcpCommunicateClient_H__
#define __H__HTcpCommunicateClient_H__

#include <QObject>
#include <QThread>
#include <QString>
#include <QQueue>
#include <QByteArray>
#include <QMutex>
#include <QTimer>
#include <QTcpSocket>
#include <TypeDef.h>




class QTcpSocket;
class HTcpCommunicateClient : public QObject
{
    Q_OBJECT

public:
    HTcpCommunicateClient();
    HTcpCommunicateClient(const QString & IP, int port);
    ~HTcpCommunicateClient();
	bool TcpConnect();
	bool TcpDisconnect();
    void SetTarget(const QString & IP, int port);

    void Request(const char* SendData, int ilen);
    void Request(const QString cmd);
    void ReadConnectState();
    //void AddReceiveData(unsigned char* Data, int iFramelen);
    bool IsConnect();
signals:
    void Error(int socketError, const QString &message);
    void ResponseData(int iDeviceType,unsigned char* data, int len);
    void SendConnectState(bool);
    void SigConnect();
    void SigReadyRead(QByteArray);
    void SigRequest(const char* SendData, int ilen);
    void SigRequest(const QString arrayData);
public slots:
    void SlotRequest(const char* SendData, int ilen);
    void SlotRequest(const QString);
    void SlotReadData();
    void SltConnected();
    void SlotError(QAbstractSocket::SocketError);
    void SlotTimeout();
public:
    QString				m_targetIP;
    int					m_targetPort;
    //QMutex m_ReceiveDatamutex;
    //QMutex m_SendDatamutex;
    QTimer *m_pTimer;
    bool				m_isLongConn;
    QTcpSocket*         m_socketClient;
    bool				m_isSuccConn;
    bool                m_IsSubThread; // as a subThread or just called by new()
};

#endif // __H__HTcpCommunicateClient_H__
