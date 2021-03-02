#ifndef H_TEST_DEFINE_H
#define H_TEST_DEFINE_H

#define ONE_STEP_TIMEOUT 3000     //单步超时时间

#define  REALTIME_LEN          1116 //1108  V3.10->3.11
#define  DATA_START_POS        444
#define  DATA_LEN              48
#define  DEVIATION_LINE        8         //线速度误差:8mm
#define  DEVIATION_ANGLE       8         //角速度误差:
#define  LINE_DISTANCE         0.15     //线速度运动距离
#define  ANGLE_DISTANCE        60        //最大角速度运动
#define  MAX_SEND_COUNT        1000      //测试线速度最大发送次数
#define  MAX_DOWN_DISTANCE     0.355     //线速度运动距离
#define  UP_MOVE_DISTANCE      0.255     //线速度运动距离

struct Data3d
{
    double x;
    double y;
    double z;
    Data3d(double x, double y, double z)
        :x(x), y(y), z(z){}
    Data3d()
        :x(0), y(0), z(0){}
    Data3d& operator=(Data3d& point)
    {
        x = point.x;
        y = point.y;
        return *this;
    }
};

enum SpeedOrient
{
    SPEED_X = 1,
    SPEED_Y,
    SPEED_Z
};


enum TestStep
{
	TS_NONE = 0,
    /////////////////////     //
    TS_SAFE_TOUCH_POWER_X = 1,  //安全接触力X, Y, Z方向
    TS_SAFE_TOUCH_POWER_Y = 2,
    TS_SAFE_TOUCH_POWER_Z = 3,
    TS_RATED_SPEED_ABDOM = 4,  //额定速度腹部
    TS_RATED_SPEED_THROID = 5, //额定速度甲状腺
    TS_PROTECT_STOP_TIME = 6,
	TS_END,
	TS_ARM_RESET = 100,
};

enum StepRatedSpeedAbdom
{
    TS_RATED_SPEED_ABDOM_X = 41,
    TS_RATED_SPEED_ABDOM_Y = 42,
    TS_RATED_SPEED_ABDOM_Z_UP = 43,
    TS_RATED_SPEED_ABDOM_Z_DOWN = 44,
    TS_RATED_SPEED_ABDOM_RX = 45,
    TS_RATED_SPEED_ABDOM_RY = 46,
};

enum StepRatedSpeed_Abdom_Z_Up
{
    TS_RATED_SPEED_ABDOM_Z_UP_STEP1 = 431,  //down
    TS_RATED_SPEED_ABDOM_Z_UP_STEP2 = 432,  //up
};

enum StepRatedSpeedThroid
{
    TS_RATED_SPEED_THROID_X = 51,
    TS_RATED_SPEED_THROID_Y = 52,
    TS_RATED_SPEED_THROID_Z = 53,
    TS_RATED_SPEED_THROID_RX = 54,
    TS_RATED_SPEED_THROID_RY = 55,
};

enum enColor
{
    COLOR_NORMAL = 0,
    COLOR_GREEN = 1,
    COLOR_RED = 2,
};

#define DEG_TO_RAD  3.1415926/180
#define RAD_TO_DEG  180/3.1415926
#define MAX_SPEED 0.003

#define SPEED_REPEAT_NUM 5

#endif // H_TEST_DEFINE_H
