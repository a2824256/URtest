#include "HAlarmLogger.h"

HAlarmLogger::HAlarmLogger()
{
}

HAlarmLogger::~HAlarmLogger()
{
}

void HAlarmLogger::LogProxy(int level, HCodeLocation location, std::string message)
{
    HLogger::Log(ms_AlarmLoggerID, level, location, message);
}

void HAlarmLogger::DumpProxy(int level, const void *buffer, size_t bufLen, std::string msg)
{
    HLogger::Dump(ms_AlarmLoggerID, level, buffer, bufLen, msg);
}

void HAlarmLogger::DumpProxy(int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg)
{
    HLogger::Dump(ms_AlarmLoggerID, level, location, buffer, bufLen, msg);
}
