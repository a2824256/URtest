#include "HOperationLogger.h"

HOperationLogger::HOperationLogger()
{
}

HOperationLogger::~HOperationLogger()
{
}

void HOperationLogger::LogProxy(int level, HCodeLocation location, std::string message)
{
    HLogger::Log(ms_OperationLoggerID, level, location, message);
}

void HOperationLogger::DumpProxy(int level, const void *buffer, size_t bufLen, std::string msg)
{
    HLogger::Dump(ms_OperationLoggerID, level, buffer, bufLen, msg);
}

void HOperationLogger::DumpProxy(int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg)
{
    HLogger::Dump(ms_OperationLoggerID, level, location, buffer, bufLen, msg);
}
