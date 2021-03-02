#ifndef H_LOGGER_H
#define H_LOGGER_H

#include "LogModel_global.h"
#include "HLogDefines.h"
#include "HCodeLocation.h"

#include <QString>
#include <QList>
#include <QMutex>

/*************************************************************************/
/*  将日志信息传递出去，可能在多线程中被调用。                              */
/*  logLevel  日志等级 HLogDefines.h 中定义                               */
/*  lineNum   日志打印处的行号，未指定时为 0                               */
/*  filename  日志打印处所在文件名，未指定时为 “null”                      */
/*  timestamp 日志打印时间戳 yyyy-MM-dd hh:mm:ss.zzz                      */
/*************************************************************************/
class LOGMODEL_EXPORT ILogCallback
{
public:
    ILogCallback() {}
    virtual ~ILogCallback() {}
    virtual void LogCommon(int logLevel, ulong threadID, int lineNum, const QString& filename, const QString& funcname, const QString& logMsg, const QString& timestamp)
    {
        Q_UNUSED(logLevel);
        Q_UNUSED(threadID);
        Q_UNUSED(lineNum);
        Q_UNUSED(filename);
        Q_UNUSED(funcname);
        Q_UNUSED(logMsg);
        Q_UNUSED(timestamp);
    }
    virtual void LogDevice(int logLevel, ulong threadID, qulonglong classID, int lineNum, const QString& filename, const QString& funcname, const QString& logMsg, const QString& timestamp)
    {
        Q_UNUSED(logLevel);
        Q_UNUSED(threadID);
        Q_UNUSED(classID);
        Q_UNUSED(lineNum);
        Q_UNUSED(filename);
        Q_UNUSED(funcname);
        Q_UNUSED(logMsg);
        Q_UNUSED(timestamp);
    }
    virtual void LogOneLine(int logLevel, const QString& logMessage)
    {
        Q_UNUSED(logLevel);
        Q_UNUSED(logMessage);
    }
};

class LOGMODEL_EXPORT HLogger
{
    REGISTER_FRIEND_CLASS(HLogManager)

public:
    HLogger();
    virtual ~HLogger();

    virtual void Trace(const char *fmt, ...) = 0;
    virtual void Trace(HCodeLocation location, const char *fmt, ...) = 0;

    virtual void Debug(const char *fmt, ...) = 0;
    virtual void Debug(HCodeLocation location, const char *fmt, ...) = 0;

    virtual void Info(const char *fmt, ...) = 0;
    virtual void Info(HCodeLocation location, const char *fmt, ...) = 0;

    virtual void Warn(const char *fmt, ...) = 0;
    virtual void Warn(HCodeLocation location, const char *fmt, ...) = 0;

    virtual void Error(const char *fmt, ...) = 0;
    virtual void Error(HCodeLocation location, const char *fmt, ...) = 0;

    virtual void Fatal(const char *fmt, ...) = 0;
    virtual void Fatal(HCodeLocation location, const char *fmt, ...) = 0;

    virtual void Dump(int logLevel, const void *buffer, size_t bufLen, const char* fmt = nullptr, ...) = 0;
    virtual void Dump(int logLevel, HCodeLocation location, const void *buffer, size_t bufLen, const char* fmt = nullptr, ...) = 0;

    virtual void CollectData(HCodeLocation location, LogCollectionType collectType, const char* format, ...) = 0;

    void AddCallback(ILogCallback* pCallback);
    void RemoveCallback(ILogCallback* pCallback);

private:
    static void Initialize(LogLevelType logLevel, bool isDisplayOnConsole);
    void DoLogCallback(int logLevel, HCodeLocation location, QString logMsg);
    void DoLogCallback(int logLevel, qulonglong classID, HCodeLocation location, QString logMsg);

protected:
    static LogLevelType  ms_LogLevel;
    static int           ms_CommonLoggerID;
    static int           ms_OperationLoggerID;
    static int           ms_ConsoleLoggerID;
    static int           ms_DeviceLoggerID;
    static int           ms_AlarmLoggerID;
    void Log(int loggerID, int level, HCodeLocation location, std::string message);
    void Log(int loggerID, int level, qulonglong classID, HCodeLocation location, std::string message);
    void Dump(int loggerID, int level, const void *buffer, size_t bufLen, std::string msg = "");
    void Dump(int loggerID, int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg = "");
    void CollectData(HCodeLocation location, LogCollectionType collectType, std::string msg);

private:
    static int           ms_CollectionLogs[LOG_COLLECTION_TYPE_MAX]; // 集中收集某一项调试数据（独立日志文件），便于使用 Excel 等工具进行分析。
    QMutex               m_MutexCallbackList;
    QList<ILogCallback*> m_ListCallback;
};

#endif // H_LOGGER_H
