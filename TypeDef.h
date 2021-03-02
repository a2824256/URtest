#ifndef TYPEDEF_H
#define TYPEDEF_H

#define __DEBUG__ qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")<<__FUNCTION__<<__LINE__

#include <QDebug>
#include <QtGlobal>
#include <memory>
#include <QString>
#include <QList>
#include <QDateTime>
#include <QMetaType>

/*past--backward--|now|---forward---future*/
/*------------|now|-------------*/

#define H_NETWORK_DELAY_GOOD    100
#define H_NETWORK_DELAY_BAD     500

#define H_NETWORK_LOST_GOOD     5
#define H_NETWORK_LOST_BAD      10

#define H_TIME_OUT        6       // 单位： 秒
#define H_TIME_OUT_TIMES  5       // 超时次数，约 30 秒，更换备选 IP


enum EXIT_SYSTEM_TYPE{
    EXIT_SYSTEM_NULL = 0,
    EXIT_SYSTEM_REBOOT = 1,
    EXIT_SYSTEM_POWEROFF = 2,
};

enum RecordType {
    BACKWARD = 0,   //P1
    FORWARD,        //P2
};

enum VIDEO_STATE {
    DIS_CONNECT_SERVER = 0,
    CONNECTING_SERVER,
    STREAMING_MEDIA,
};

typedef enum
{
    H_EVENT_ONLINE = 1,
    H_EVENT_OFFLINE,
}H_DEV_EVENT;

typedef enum
{
    H_SIDE_NULL = 0 ,
    H_SIDE_INITING = 1,
    H_SIDE_READY,           //在线就绪
    H_SIDE_OFFLINE,         //离线
    H_SIDE_CONNECTING,      //连接中
    H_SIDE_BUSY,            //在线忙碌
    H_SIDE_DISCONNECTING,   //断开中
    H_SIDE_ERROR,           //在线错误
}H_SIDE_STATE;


typedef enum
{
    H_RSP_NULL = 0 ,
    H_RSP_SUCESS,
    H_RSP_ERROR
}H_RSP_STATE;

typedef enum
{
    H_MSG_ALARM = 0,
    H_MSG_DEVICE,
    H_MSG_CONTROL,
    H_MSG_EXAMINE,
    H_MSG_DATA,
    H_MSG_MAX
}H_MSG_TYPE;


typedef enum
{
    H_SEND_TO_NULL = 0,
    H_SEND_TO_SEVER = 1,
    H_SEND_TO_PEER
}H_SEND_TYPE;

typedef enum
{
    H_ARM_NULL = 0 ,
    H_ARM_INIT = 0x0101 ,
    H_ARM_HOMGING ,
    H_ARM_RIGHT_HOME,
    H_ARM_PLAYPROGRAM,
    H_ARM_STOP,
    H_ARM_CLREA_ERROR,
    H_ARM_STATE,
    H_ARM_MOVE ,
    H_ARM_VELOCITY,
    H_ARM_EMERGENCY_STOP ,
    H_ARM_CAMERA_SWITCH,
    H_ARM_AUTO_STOP,
}H_ARM_CONTROL_TYPE;

typedef enum
{
    H_ARM_STATE_NULL = 0x0000,
    H_ARM_PHYSICALROBOTCONNECTED = 0x0002,
    H_ARM_REALROBOTENABLED = 0x0004,
    H_ARM_ROBOTPOWERON = 0x0008,
    H_ARM_EMERGENCYSTOPPED = 0x0010,
    H_ARM_PROTECTIVESTOPPED = 0x0020,
    H_ARM_PROGRAMRUNNING = 0x0040,
    H_ARM_PROGRAMPAUSED = 0x0080,
}H_ARM_RSP_STATE;

typedef enum
{
    ROBOT_UNINIT = 0,
    ROBOT_INIT = 1 ,
    ROBOT_MANUAL_START ,
    ROBOT_MANUAL_STOP ,
    ROBOT_EMERGENCY_STOPPED ,
    ROBOT_PROTECTIVE_STOPPED
}H_CONTROL_BTN_STATE;

typedef enum
{
    H_CAMERA_STOP = 1,
    H_CAMERA_UP ,
    H_CAMERA_DOWN ,
    H_CAMERA_RIGHT ,
    H_CAMERA_LEFT ,
    H_CAMERA_PLUS ,
    H_CAMERA_DECREASE,
}H_CAMERA_STATE;

typedef enum
{
    H_US_MOUSE = 1,
    H_US_STANDARD_KEY,
    H_US_FUNKEY,
    H_US_OTHER,
}H_US_CONTROL_TYPE;

typedef enum
{
    US_VENDER_WISONC = 1,
    US_VENDER_STORK = 2,
    US_VENDER_END,
}US_VENDER_TYPE;

//typedef enum
//{
//    WAIT_EXAMINE = 1, //等待检查
//    EXAMINING,        //正在检查
//    EXAMINED,         //结束检查
//    REPORTED,         //已出报告
//    REPORT_PRINTED,   //已打印报告
//}H_EXAM_STATE;

typedef enum
{
    SAFETY_MODE_NORMAL = 1,
    SAFETY_MODE_REDUCED,
    SAFETY_MODE_PROTECTIVE_STOP,
    SAFETY_MODE_RECOVERY,
    SAFETY_MODE_SAFEGUARD_STOP,
    SAFETY_MODE_SYSTEM_EMERGENCY_STOP,
    SAFETY_MODE_ROBOT_EMERGENCY_STOP,
    SAFETY_MODE_VIOLATION,
    SAFETY_MODE_FAULT,
}H_ARM_SAFETY_MODE;

typedef enum
{
    UK_PROBE = 1,
    UK_REVIEW = 2,
}US_ULTRASOUNDFUNKEY_VALUE;

enum
{
    NULL_COUNT = 0,
    IMAGE_COUNT,
    VIDEO_COUNT,
};

enum LanguageId
{
    LAN_CH = 0,
    LAN_EN,
};

/*************************************/
#define WISONIC_HEAD_LEN   20
#define WISONIC_HEAD_CODE  0xABEF0001
#define US_CONNECT_TIMEOUT 1000
#define US_RECONNECT_TIME  1000

struct WisonicHeade
{
    quint32   headeCode;
    quint32   length;
    quint64   sessionId;
    quint8    type;
    quint8    priority;
    quint8    crc;
    quint8    reserved;
};

enum WisoncMsgType
{
    WT_BUSINESS = 0,
    WT_BUSINESS_RSP,
    WT_SHAKEHAND,
    WT_SHAKEHAND_RSP,
    WT_HEARTBEAT,
    WT_HEARTBEAT_RSP
};

enum SOUND_TYPE{
    SOUND_ERRPR = -1,
    SOUND_ON = 0,
    SOUND_OFF = 1,
};

typedef enum
{
    ROBOT_ICON = 0,
    NETWORK_ICON,
    SOUND_ICON,
    CAMERA_ICON,
    ALARM_ICON,
    TASK_ICON,
    VOLUME_ICON,
}ICON_TYPE;

typedef enum
{
    PROBE_NORMAL = 0,
    PROBE_EMC,
    PROBE_AUTO,
}H_PROBE_SYSTEM;

typedef enum
{
    ARM_BODY_PART_ABDOMEN = 0,
    ARM_BODY_PART_THYROID
}H_ARM_SYSTEM;

enum TouchscreenType
{
    SCREEN_BIG = 0,
    SCREEN_SMALL = 1
};

/*************************************/
// Ultrasound Stork
/*************************************/
#define STORK_HEAD_LEN 12
#define STORK_HEAD_CODE  0xFFFFFFFF
struct StorkHead
{
    quint32   headeCode;
    quint32   cmdId;
    quint32   length;
};

//////////////////////////////////////////////////////////////////////////
// patientInfo  examInfo
//////////////////////////////////////////////////////////////////////////
#define PATIENTID_SHOW_LEN  9            //patient id show length
#define USID_SHOWL_LEN      10           //examine id show length
#define FREEZE_TIME_SEC     86400        //freeze time
#define FREEZE_CHECK_TIME   30 * 60000   //30 mi
#define UPLOAD_IMAGE_SIZE   2097152      //2 * 1024 * 1024 = 2097152
#define MAX_EXAM_NUM        2000         //Maximum number of records.need backup 


//enum Patient_State
//{
//   Patient_NULL,       //没人病人
//   Patient_Reg,        //已登记病人信息
//   Patient_Scanning,   //正在检查
//   Patient_Pause,      //暂停检查
//   Patient_EndExam,    //已结束检查
//};

class PatientInfo
{
public:
    QString         depName;
    QString         firstName;
    QString         lastName;
    QString         folk;
    QString         caseId;
    QString         clinicNum;
    unsigned char   checkParts;
    float           weight;
    unsigned char   weightUnit;
    float           height;
    unsigned char   heightUnit;
    QDate           birthDay;
    unsigned char   age;
    unsigned char   sex;
    unsigned char   blood;
    unsigned char   categoryType;
    QString         addrSite;
    QString         postCode;
    QString         telNumber;
    QString         Perf_Physician; //诊断医生
    QString         Pef_Physician; //主治医生
    QString         operatorName; //操作者
    QDateTime       receiveDateTime;
    QDateTime       startDayTime;
    QDateTime       endDateTime;
    QString         remarks;
    unsigned char   state;
    QString         medicalHistory;
};


typedef struct _TEMPLATE_INFO
{
    int parentId;
    int id;
    QString strName;
    QString strExam;
    QString strInterpretation;
}TemplateInfo;

enum enAddMode
{//the mode of import patient or exam
    AM_NORMAL = 0,
    AM_BATCH
};

enum enPushMode
{
    PM_ALL = 0,
    PM_PATIENT_INFO,
};

enum GENDER_TYPE
{
    MALE = 0,   //default
    FEMALE,
};

enum Exam_State
{
    EXAM_NULL,
    EXAM_READY = 1,         //就绪
    EXAM_SCANNING = 2,      //检查中
    EXAM_PAUSE = 3,         //暂停
    EXAM_END_EXAM = 4,      //结束
    EXAM_REPORTED = 5,      //已出报告
    EXAM_FREEZE = 6         //冻结
};

enum UserType
{
    UT_NULL = 0,
    UT_ENGINEER = 1,
    UT_SUPER_ADMIN = 2,
    UT_ADMIN = 3,
    UT_USER  = 4
};

enum SyncFlag
{
    SF_NONE = 0,
    SF_SYNCHRONIZED = 1,
    SF_FROM_PEER = 2,
    SF_END = 3
};

enum AgeType
{
    AT_YEAR = 0,
    AT_MONTH = 1,
    AT_DAY = 2
};

class HExam
{
public:
    //--properties
    QString        caseId;             //超声号/检查号
    QString        patientId;          //病人ID
    int            examPart;           //检查部位
    QString        clinicNum;          //门诊号
    QString        applySection;       //申请科室
    QString        examWay;            //检查方法
    QDateTime      recvTime;           //录入时间 add2090425
    QDateTime      startTime;          //开始时间
    QDateTime      endTime;            //结束时间
    QDateTime      pauseTime;          //暂停时间
    QDateTime      reportTime;         //报告时间
    QDateTime      printTime;          //打印时间
    QDateTime      pushTime;           //推送时间
    QString        examPhysician;      //检查医生
    QString        reportPhysician;    //报告医生
    int            state;              //状态 等待检查/检查中/暂停检查/结束检查/已打印报告/冻结
    int            syncFlg;
/// //////////////////////////////////////////////
    QString         platformId;        //平台id(数据源)
    QString         platformExamId;    //平台-检查id

public:
    HExam()
    {
        examPart = 0;
        state = Exam_State::EXAM_READY;
        syncFlg = SyncFlag::SF_NONE;
    }
};

class HInformation
{
public:
    QString    msgId;     //消息id
    int        msgType;   //消息级别
    QDateTime  recvTime;  //消息时间
    QString    content;   //消息内容
};

class HPatient
{
public:
    //--properties
    QString        patientId;          //病人ID
    QString        idCard;             //身份证
    QDateTime      recvTime;           //录入时间
    QDateTime      modifyTime;         //上一次修改时间
    QString        name;               //firstName
    char           sex;                //性别  0:male 1:female
    QDate          birthDay;           //生日
    quint32        age;                //年龄
    QString        folk;               //名族
    QString        socialScyNum;       //社保卡号
    QString        telNumber;          //电话号码
    float          height;             //身高
    float          weight;             //体重
    QString        medicalHistory;     //既往病史
    QString        remarks;            //备注
    QString        admissionNum;       //住院号
    int            syncFlg;
    QString        lastName;           //last name
    int            referNum;           //Exam record num
    ///////////////////////////////////////
    QString         platformId;         // 平台id(数据源)
    QString         platformPatientId;  // 平台-检查id
    int             gender;             // 性别 GB/T 2261.1
    int             nation;             // 民族 GB/T 3304

public:
    HPatient() :patientId(""), idCard(""), recvTime(QDateTime()), modifyTime(QDateTime())\
        , name(""), sex(0), birthDay(QDate()), age(0), folk(""), socialScyNum("") \
        , telNumber(""), height(0), weight(0), medicalHistory(""), remarks("") \
        , admissionNum(""), syncFlg(SyncFlag::SF_NONE), lastName(""), referNum(0)  \
        , platformId(""), platformPatientId(""), gender(-1), nation(0) {}
};

class HUser
{
public:
    QString        userName;           //用户名
    QString        password;           //密码
    QString        name;               //姓名
    quint32        right;              //权限 eg.管理员/医生/技术支持
    QDateTime      recvTime;           //录入时间
    QDateTime      modifyTime;         //最后一次修改时间
    QDateTime      loginTime;          //最后一次登录时间
};

typedef std::shared_ptr<HPatient>     patient_ptr;
typedef std::vector<patient_ptr>      vector_patient;
typedef std::shared_ptr<HExam>        exam_ptr;
//typedef std::vector<exam_ptr>       vector_exam;
typedef QVector<exam_ptr>             vector_exam;
typedef std::shared_ptr<HUser>        user_ptr;
typedef std::vector<user_ptr>         vector_user;
typedef std::shared_ptr<HInformation> info_ptr;
typedef std::vector<info_ptr>         vector_info;

//user for send dialog
enum SendType
{
    ST_EXPORT,
    ST_IMPORT
};

//////////////////////////////////////////////////////////////////////////
//WebRTC
class NetParams
{
public:
    qint64 nNetDelay;
    qint64 nVideoDelay;
    qint32 nNetLost;
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//startup  shutdown
#define PSIDE_STARTUP_PIN    1
#define PSIDE_SHUTDOWN_PIN   2
#define P_SHUTDOWN_CHECK_PIN 0
#define D_SHUTDOWN_CHECK_PIN 4

// 图像存储区域
enum ImageRegion
{
    IR_FULL_SCREEN,
    IR_US_IMAGE,
    IR_MAX_COUNT
};

// 图像存储格式
enum ImageFormat
{
    IF_PNG,
    IF_JPEG,
    IF_BMP,
    IF_MAX_COUNT
};

typedef enum
{
    H_VOLTAGE_BASE = 0 ,
    H_VOLTAGE_VCORE ,
    H_VOLTAGE_VCORE2,
    H_VOLTAGE_5V,
    H_VOLTAGE_12V,
    H_VOLTAGE_5VSB,
    H_VOLTAGE_3V3,
    H_VOLTAGE_3VSB,
    H_VOLTAGE_VBAT,
    H_VOLTAGE_VTT,
    H_VOLTAGE_24V,
}H_VOLTAG_ID;

//sri安装角度合法值
const QList<int> SRI_ANGLE_ROTATIONS({ 0, 45 });

//PatientSide
struct ArmData
{
    double x;
    double y;
    double z;
    double rx;
    double ry;
    double rz;
    double p;
    double f;
    int type;
    int bodyPart;
    ArmData() { memset(this, 0, sizeof(ArmData)); }
    ArmData(double x, double y, double z,
            double rx, double ry, double rz,
            double p = 0, double f = 0, int type = 0, int bodyPart = 0)
            :x(x), y(y), z(z)
            ,rx(rx), ry(ry), rz(rz)
            ,p(p), f(f), type(type), bodyPart(bodyPart){}
};

Q_DECLARE_METATYPE(ArmData);

#define IMU_HEAD "594953"
#define IMU_LENTH 254

#define IMU_HEAD_NEW "5953"
#define IMU_LENTH_NEW 190

#endif // TYPEDEF_H
