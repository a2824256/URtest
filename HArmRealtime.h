#ifndef ARMREALTIME_H
#define ARMREALTIME_H

#include <QObject>
#include <QTcpSocket>
#include "HTestDefine.h"

class  HArmRealtime : public QObject
{
	Q_OBJECT

public:
	HArmRealtime(QString Ip, int port);
	~HArmRealtime();

signals:
	void SigRecvData(double, double, double, \
		             double, double, double);
	void SigOutputMsg(QString);
    void SigConnect(bool);

public slots:
	void SltInitialise();
	void SltDisconnect();
	void SltReadData();
	void SltError(QAbstractSocket::SocketError err);
    void SltReconnect();

private:
	void TcpConnect();
	void ParseData(QByteArray& ba);
	void RobottoTool(double x, double y, double z, double rx, double ry, double rz);

private:
	QString     m_Ip;
	int         m_port;
	QTcpSocket *m_pSocket;
	bool        m_isSuccConn;
	double      m_x;
	double      m_y;
	double      m_z;
	double      m_rx;
	double      m_ry;
	double      m_rz;
};

#endif //ARMREALTIME_H
