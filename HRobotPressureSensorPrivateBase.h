#ifndef HROBOTPRESSURESENSORPRIVATEBASE_H
#define HROBOTPRESSURESENSORPRIVATEBASE_H

#include <QObject>

typedef struct HPressureInfoStruct {
    double ForceX;
    double ForceY;
    double ForceZ;
    double TorqueX;
    double TorqueY;
    double TorqueZ;
} HPressureInfo;

class HRobotPressureSensorPrivateBase : public QObject
{
    Q_OBJECT
public:
    HRobotPressureSensorPrivateBase();
    virtual ~HRobotPressureSensorPrivateBase();
 //   virtual HPressureInfo GetPressureSensorInfo() = 0;
    virtual void SetNeedToCalibration(bool bCalibration) = 0;
//    virtual void Check() = 0 ;

signals:
    void SigPressureInfo(double x,double y,double z);
};

#endif // HROBOTPRESSURESENSORPRIVATEBASE_H
