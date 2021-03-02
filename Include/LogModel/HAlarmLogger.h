#ifndef HALARMLOGGER_H
#define HALARMLOGGER_H

#include "HCommonLogger.h"

class LOGMODEL_EXPORT HAlarmLogger : public HCommonLogger
{
    REGISTER_FRIEND_CLASS(HLogManager)

public:
    ~HAlarmLogger();

private:
    HAlarmLogger();

    virtual void LogProxy(int level, HCodeLocation location, std::string message) override;
    virtual void DumpProxy(int level, const void *buffer, size_t bufLen, std::string msg = "") override;
    virtual void DumpProxy(int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg = "") override;
};
#endif // HALARMLOGGER_H
