#include "HArmRealtime.h"
#include "Eigen/Dense"
#include <QElapsedTimer>
#include <QtEndian>
using namespace Eigen;


#define PI 3.1415926
#define  RAD_TO_DEG 180/3.1415926

HArmRealtime::HArmRealtime(QString Ip, int port)
	:m_Ip(Ip)
	,m_port(port)
    ,m_pSocket(NULL)
    ,m_isSuccConn(false)
{
	m_x = m_y = m_z = m_rx = m_ry = m_rz = 0;
}

HArmRealtime::~HArmRealtime()
{
	qDebug() << "HArmRealtime Destructing";
}

void HArmRealtime::SltInitialise()
{
	m_pSocket = new QTcpSocket(this);
	bool ok = connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(SltReadData()));
	ok = connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(SltDisconnect()));
	ok = connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SltError(QAbstractSocket::SocketError)));
	TcpConnect();
}

void HArmRealtime::SltReadData()
{
    QByteArray recvData = m_pSocket->readAll();
    ParseData(recvData);
}

void HArmRealtime::SltError(QAbstractSocket::SocketError err)
{
	qDebug() << err;
}

void HArmRealtime::SltReconnect()
{
    m_pSocket->close();
    TcpConnect();
}

void HArmRealtime::TcpConnect()
{
	m_pSocket->connectToHost(m_Ip, m_port);
	if (!m_pSocket->waitForConnected(1000))
	{
		m_isSuccConn = false;
        emit SigConnect(false);
        qDebug() << "connect failed!";
		return;
	}
	m_isSuccConn = true;
    emit SigConnect(true);
	qDebug() << "connect succeed!";
}

void HArmRealtime::SltDisconnect()
{
	//output logger
    emit SigConnect(false);
	emit SigOutputMsg(QStringLiteral("机械臂断开连接..."));
}

void HArmRealtime::ParseData(QByteArray& ba)
{

	if (ba.size() == 0)
	{
		return;
	}

// 	if ((ba.size() % REALTIME_LEN == 0))
// 	{
// 		ba = ba.right(REALTIME_LEN);
// 	}
//	QByteArray data = ba;
    QElapsedTimer time;
    time.restart();

	char* pHead = NULL;
	while (ba.size())
	{
		pHead = ba.data();
		int length = qFromBigEndian(*(qint32*)pHead);
		if (length == REALTIME_LEN)
		{
			break;
		}
		else
		{
			ba = ba.remove(0, 1);
		}
	}
	
    int iTime = time.elapsed();
    if (iTime >= 500)
    {
        qDebug() << "Elapse timeout";
    }

	if (ba.size() < (DATA_START_POS + DATA_LEN))
	{
		return;
	}
// 	if (lenth != ba.size())
// 	{
// 		qDebug() << "parse failed!";
// 		return;
// 	}

//	qDebug() << "lenth:" << lenth;

//////////////////////////////////////////////////////////////////////////
// 	qDebug() << "time: " << ba.mid(4, 8).toHex();
// 	qDebug() << "timeOrigEdin"<< *(double*)(pHead + 4);
// 	qint64 time = qFromBigEndian(*(qint64*)(pHead  + 4));
// 	double dbTime = *(double*)(&time);
// 	qDebug() << "dbTime: " << dbTime;

//////////////////////////////////////////////////////////////////////////
// 	qDebug() << "m_z" << ba.mid(DATA_START_POS + 16, 8).toHex();
// 	qint64 iz = qFromBigEndian(*(qint64*)(pHead + DATA_START_POS + 16));
// 	qDebug()<<"z: "<< *(double*)(&iz);
//////////////////////////////////////////////////////////////////////////

	int count = 0;
	qint64 ix = qFromBigEndian(*(qint64*)(pHead + DATA_START_POS + (count++) * 8));
	m_x = *(double*)(&ix);
	
//	qDebug() << "m_y" << ba.mid(DATA_START_POS + count * 8, 8).toHex();
 	qint64 iy = qFromBigEndian(*(qint64*)(pHead + DATA_START_POS + (count++) * 8));
	m_y = *(double*)(&iy);
	
//	qDebug() << "m_z" << ba.mid(DATA_START_POS + count * 8, 8).toHex();
	qint64 iz = qFromBigEndian(*(qint64*)(pHead + DATA_START_POS + (count++) * 8));
	m_z = *(double*)(&iz);

//	qDebug() << "m_rx" << ba.mid(DATA_START_POS + count * 8, 8).toHex();
	qint64 irx = qFromBigEndian(*(qint64*)(pHead + DATA_START_POS + (count++) * 8));
	m_rx = *(double*)(&irx);

//	qDebug() << "m_ry" << ba.mid(DATA_START_POS + count * 8, 8).toHex();
	qint64 iry = qFromBigEndian(*(qint64*)(pHead + DATA_START_POS + (count++) * 8));
	m_ry = *(double*)(&iry);

//	qDebug() << "m_rz" << ba.mid(DATA_START_POS + count * 8, 8).toHex();
	qint64 irz = qFromBigEndian(*(qint64*)(pHead + DATA_START_POS + (count++) * 8));
	m_rz = *(double*)(&irz);

//	emit SigRecvData(m_x, m_y, m_z, m_rx, m_ry, m_rz);


//	qDebug() << "x|y|z|rx|ry|rz:" << m_x <<" " << m_y << " " << m_z << " " << m_rx << " "
//		                          << m_ry << " " << m_rz;

	RobottoTool(m_x, m_y, m_z, m_rx, m_ry, m_rz);
}

void HArmRealtime::RobottoTool(double x, double y, double z, double rx, double ry, double rz)
{
	double x_offset = 0;
	double y_offset = -0.56;
	double z_offset = 0.05;
	double mol = sqrt(rx*rx + ry*ry + rz*rz);
	Vector3d rotvec(rx / mol, ry / mol, rz / mol);
	AngleAxisd rotation_vector(mol, rotvec);
	Matrix3d R_robot; //当前末端相对于机器人基座的旋转矩阵
	R_robot = rotation_vector.matrix();
	Vector3d p_robot(x - x_offset, y - y_offset, z - z_offset); //当前末端相对于机器人基座的位置

	Matrix3d R_robot_to_tool;
	R_robot_to_tool << cos(PI), 0, sin(PI),
		0, 1, 0,
		-sin(PI), 0, cos(PI);

	Matrix3d R_tool;
	R_tool = R_robot_to_tool*R_robot;
	//Vector3d RPY = R_tool.eulerAngles(2, 1, 0);

	m_ry = atan2(-R_tool(2,0), sqrt(1 - pow(R_tool(2, 0), 2)));
	m_rz = atan2((R_tool(1, 0) / cos(m_ry)), (R_tool(0, 0) / cos(m_ry)));
	m_rx = atan2((R_tool(2, 1) / cos(m_ry)), (R_tool(2, 2) / cos(m_ry)));


	Vector3d p_tool;
	p_tool = R_robot_to_tool*p_robot;

	m_x = p_tool(0);
	m_y = p_tool(1);
	m_z = p_tool(2);
	//m_rx = RPY(2);
	//m_ry = RPY(1);
	//m_rz = RPY(0);

// 	cout << "x: " << p_tool(0) << endl;
// 	cout << "y: " << p_tool(1) << endl;
// 	cout << "z: " << p_tool(2) << endl;
// 	cout << "rx: " << RPY(2) << endl;
// 	cout << "ry: " << RPY(1) << endl;
// 	cout << "rz: " << RPY(0) << endl;


	emit SigRecvData(m_x, m_y, m_z, m_rx, m_ry, m_rz);
//	qDebug() << "x1:y1:z1:rx:ry:rz:" << m_x << " " << m_y << " " << m_z << " " << m_rx*RAD_TO_DEG << " " << m_ry*RAD_TO_DEG << " " << m_rz*RAD_TO_DEG;

}
