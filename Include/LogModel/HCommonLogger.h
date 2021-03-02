#ifndef H_COMMON_LOGGER_H
#define H_COMMON_LOGGER_H

#include "HLogger.h"
#include "HLogDefines.h"

class LOGMODEL_EXPORT HCommonLogger : public HLogger
{
    REGISTER_FRIEND_CLASS(HLogManager)

public:
    ~HCommonLogger();

    virtual void Trace(const char *fmt, ...) override;
    virtual void Trace(HCodeLocation location, const char *fmt, ...) override;

    virtual void Debug(const char *fmt, ...) override;
    virtual void Debug(HCodeLocation location, const char *fmt, ...) override;

    virtual void Info(const char *fmt, ...) override;
    virtual void Info(HCodeLocation location, const char *fmt, ...) override;

    virtual void Warn(const char *fmt, ...) override;
    virtual void Warn(HCodeLocation location, const char *fmt, ...) override;

    virtual void Error(const char *fmt, ...) override;
    virtual void Error(HCodeLocation location, const char *fmt, ...) override;

    virtual void Fatal(const char *fmt, ...) override;
    virtual void Fatal(HCodeLocation location, const char *fmt, ...) override;

    virtual void Dump(int logLevel, const void *buffer, size_t bufLen, const char* fmt = nullptr, ...) override;
    virtual void Dump(int logLevel, HCodeLocation location, const void *buffer, size_t bufLen, const char* fmt = nullptr, ...) override;

    virtual void CollectData(HCodeLocation location, LogCollectionType collectType, const char* format, ...) override;

private:
    virtual void LogProxy(int level, HCodeLocation location, std::string message);
    virtual void DumpProxy(int level, const void *buffer, size_t bufLen, std::string msg);
    virtual void DumpProxy(int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg);

protected:
    HCommonLogger();
};

#endif // H_COMMON_LOGGER_H
