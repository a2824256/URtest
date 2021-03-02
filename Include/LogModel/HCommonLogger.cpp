#include "HCommonLogger.h"
#include "zlog.h"

HCommonLogger::HCommonLogger()
{
}

HCommonLogger::~HCommonLogger()
{
}

void HCommonLogger::Trace(const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_TRACE)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_TRACE, HCodeLocation("null", "", 0), msgBuffer);
    }
}

void HCommonLogger::Trace(HCodeLocation location, const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_TRACE)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_TRACE, location, msgBuffer);
    }
}

void HCommonLogger::Debug(const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_DEBUG)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_DEBUG, HCodeLocation("null", "", 0), msgBuffer);
    }
}

void HCommonLogger::Debug(HCodeLocation location, const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_DEBUG)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_DEBUG, location, msgBuffer);
    }
}

void HCommonLogger::Info(const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_INFO)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_INFO, HCodeLocation("null", "", 0), msgBuffer);
    }
}

void HCommonLogger::Info(HCodeLocation location, const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_INFO)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_INFO, location, msgBuffer);
    }
}

void HCommonLogger::Warn(const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_WARN)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_WARN, HCodeLocation("null", "", 0), msgBuffer);
    }
}

void HCommonLogger::Warn(HCodeLocation location, const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_WARN)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_WARN, location, msgBuffer);
    }
}

void HCommonLogger::Error(const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_ERROR)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_ERROR, HCodeLocation("null", "", 0), msgBuffer);
    }
}

void HCommonLogger::Error(HCodeLocation location, const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_ERROR)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_ERROR, location, msgBuffer);
    }
}

void HCommonLogger::Fatal(const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_FATAL)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_FATAL, HCodeLocation("null", "", 0), msgBuffer);
    }
}

void HCommonLogger::Fatal(HCodeLocation location, const char *fmt, ...)
{
    if (ms_LogLevel <= HLOG_LEVEL_FATAL)
    {
        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
        this->LogProxy(HLOG_LEVEL_FATAL, location, msgBuffer);
    }
}

void HCommonLogger::Dump(int logLevel, const void *buffer, size_t bufLen, const char* fmt /* = nullptr */, ...)
{
    if (ms_LogLevel <= logLevel)
    {
        if (fmt == nullptr)
        {
            this->DumpProxy(logLevel, buffer, bufLen, std::string(""));
        }
        else
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH] = { 0 };
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            this->DumpProxy(logLevel, buffer, bufLen, std::string(msgBuffer));
        }
    }
}

void HCommonLogger::Dump(int logLevel, HCodeLocation location, const void *buffer, size_t bufLen, const char* fmt /* = nullptr */, ...)
{
    if (ms_LogLevel <= logLevel)
    {
        if (fmt == nullptr)
        {
            this->DumpProxy(logLevel, location, buffer, bufLen, std::string(""));
        }
        else
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH] = { 0 };
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            this->DumpProxy(logLevel, location, buffer, bufLen, std::string(msgBuffer));
        }
    }
}

void HCommonLogger::CollectData(HCodeLocation location, LogCollectionType collectType, const char* format, ...)
{
    if (collectType < 0 || collectType >= LOG_COLLECTION_TYPE_MAX) return;

    char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
    VA_FORMAT(msgBuffer, format, DEAFAULT_LOG_BUFFER_LENGTH - 1);
    HLogger::CollectData(location, collectType, std::string(msgBuffer));
}

void HCommonLogger::LogProxy(int level, HCodeLocation location, std::string message)
{
    HLogger::Log(ms_CommonLoggerID, level, location, message);
}

void HCommonLogger::DumpProxy(int level, const void *buffer, size_t bufLen, std::string msg)
{
    HLogger::Dump(ms_CommonLoggerID, level, buffer, bufLen, msg);
}

void HCommonLogger::DumpProxy(int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg)
{
    HLogger::Dump(ms_CommonLoggerID, level, location, buffer, bufLen, msg);
}
