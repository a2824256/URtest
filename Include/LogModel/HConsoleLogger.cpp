#include "HConsoleLogger.h"

HConsoleLogger::HConsoleLogger()
{
}

HConsoleLogger::~HConsoleLogger()
{
}

void HConsoleLogger::LogProxy(int level, HCodeLocation location, std::string message)
{
    HLogger::Log(ms_ConsoleLoggerID, level, location, message);
}

void HConsoleLogger::DumpProxy(int level, const void *buffer, size_t bufLen, std::string msg)
{
    HLogger::Dump(ms_ConsoleLoggerID, level, buffer, bufLen, msg);
}

void HConsoleLogger::DumpProxy(int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg)
{
    HLogger::Dump(ms_ConsoleLoggerID, level, location, buffer, bufLen, msg);
}
