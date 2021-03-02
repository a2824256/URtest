#include "HLogger.h"

#include <sstream>
#include <QMutexLocker>
#include <QDateTime>
#include <QThread>

#include "zlog.h"
#include "HLogCleaner.h"

#define LOG_FILE_SIZE_LIMIT 20 // MByte

LogLevelType HLogger::ms_LogLevel = HLOG_LEVEL_NONE;
int          HLogger::ms_CommonLoggerID = 0;
int          HLogger::ms_OperationLoggerID = 0;
int          HLogger::ms_ConsoleLoggerID = 0;
int          HLogger::ms_DeviceLoggerID = 0;
int          HLogger::ms_AlarmLoggerID = 0;
int          HLogger::ms_CollectionLogs[LOG_COLLECTION_TYPE_MAX] = { 0 };

HLogger::HLogger()
{
}

HLogger::~HLogger()
{
}

void HLogger::Initialize(LogLevelType logLevel, bool isDisplayOnConsole)
{
    // zlog 初始化设置
    if (ms_CommonLoggerID == 0)
    {
        ms_LogLevel = logLevel;
        zlog::IZLogManager::getRef().setIsWriteToFile(zlog::ZLOG_MAIN_LOGGER_ID, false);
        // 通用日志
        ms_CommonLoggerID = zlog::IZLogManager::getRef().createLogger("CommonLogger");
        zlog::IZLogManager::getRef().setLogFilePath(ms_CommonLoggerID, "./logs/");
        zlog::IZLogManager::getRef().setFilterLogLevel(ms_CommonLoggerID, logLevel);
        zlog::IZLogManager::getRef().setLogFileSizeLimit(ms_CommonLoggerID, LOG_FILE_SIZE_LIMIT);
        zlog::IZLogManager::getRef().setIsDisplayOnConsole(ms_CommonLoggerID, isDisplayOnConsole);
        zlog::IZLogManager::getRef().setIsWriteToFile(ms_CommonLoggerID, true);
        // 操作日志
        ms_OperationLoggerID = zlog::IZLogManager::getRef().createLogger("OperationLogger");
        zlog::IZLogManager::getRef().setLogFilePath(ms_OperationLoggerID, "./logs/");
        zlog::IZLogManager::getRef().setFilterLogLevel(ms_OperationLoggerID, logLevel);
        zlog::IZLogManager::getRef().setLogFileSizeLimit(ms_OperationLoggerID, LOG_FILE_SIZE_LIMIT);
        zlog::IZLogManager::getRef().setIsDisplayOnConsole(ms_OperationLoggerID, isDisplayOnConsole);
        zlog::IZLogManager::getRef().setIsWriteToFile(ms_OperationLoggerID, true);
        // 设备日志
        ms_DeviceLoggerID = zlog::IZLogManager::getRef().createLogger("DeviceLogger");
        zlog::IZLogManager::getRef().setLogFilePath(ms_DeviceLoggerID, "./logs/");
        zlog::IZLogManager::getRef().setFilterLogLevel(ms_DeviceLoggerID, logLevel);
        zlog::IZLogManager::getRef().setLogFileSizeLimit(ms_DeviceLoggerID, LOG_FILE_SIZE_LIMIT);
        zlog::IZLogManager::getRef().setIsDisplayOnConsole(ms_DeviceLoggerID, isDisplayOnConsole);
        zlog::IZLogManager::getRef().setIsWriteToFile(ms_DeviceLoggerID, true);
        // 控制台日志
        ms_ConsoleLoggerID = zlog::IZLogManager::getRef().createLogger("ConsoleLogger");
        zlog::IZLogManager::getRef().setFilterLogLevel(ms_ConsoleLoggerID, logLevel);
        zlog::IZLogManager::getRef().setIsDisplayOnConsole(ms_ConsoleLoggerID, isDisplayOnConsole);
        zlog::IZLogManager::getRef().setIsWriteToFile(ms_ConsoleLoggerID, false);

        // 报警日志
        ms_AlarmLoggerID = zlog::IZLogManager::getRef().createLogger("AlarmLogger");
        zlog::IZLogManager::getRef().setLogFilePath(ms_AlarmLoggerID, "./logs/");
        zlog::IZLogManager::getRef().setFilterLogLevel(ms_AlarmLoggerID, logLevel);
        zlog::IZLogManager::getRef().setLogFileSizeLimit(ms_AlarmLoggerID, LOG_FILE_SIZE_LIMIT);
        zlog::IZLogManager::getRef().setIsDisplayOnConsole(ms_AlarmLoggerID, isDisplayOnConsole);
        zlog::IZLogManager::getRef().setIsWriteToFile(ms_AlarmLoggerID, true);

        // 用于收集调试数据的日志（预留个数 LOG_COLLECTION_TYPE_MAX）
        std::stringstream oss;
        for (int i = 0; i < LOG_COLLECTION_TYPE_MAX; ++i)
        {
            oss.str("");
            oss << "Collection_Type_" << i;
            int logId = zlog::IZLogManager::getRef().createLogger(oss.str().c_str());
            zlog::IZLogManager::getRef().setLogFilePath(logId, "./logs/");
            zlog::IZLogManager::getRef().setFilterLogLevel(logId, HLOG_LEVEL_INFO);
            zlog::IZLogManager::getRef().setLogFileSizeLimit(logId, LOG_FILE_SIZE_LIMIT);
            zlog::IZLogManager::getRef().setIsDisplayOnConsole(logId, false);
            zlog::IZLogManager::getRef().setIsWriteToFile(logId, true);
            ms_CollectionLogs[i] = logId;
        }
        zlog::IZLogManager::getRef().start();

        // 启动日志文件整理线程
        static HLogCleaner logCleaner;
        logCleaner.Start();
    }
}

void HLogger::AddCallback(ILogCallback* pCallback)
{
    if (pCallback == nullptr)
    {
        return;
    }
    QMutexLocker locker(&m_MutexCallbackList);
    if (-1 == m_ListCallback.indexOf(pCallback))
    {
        m_ListCallback.append(pCallback);
    }
}

void HLogger::RemoveCallback(ILogCallback* pCallback)
{
    if (pCallback == nullptr)
    {
        return;
    }
    QMutexLocker locker(&m_MutexCallbackList);
    m_ListCallback.removeAll(pCallback);
}

void HLogger::Log(int loggerID, int level, HCodeLocation location, std::string message)
{
    int lineNum = location.GetLineNumber();
    std::string filename = location.GetFileName();
    std::string funcname = location.GetFunctionNameFull();
    std::string tempMsg = message;
    tempMsg.append(" <-- ").append(location.GetFunctionNameFull());
    LOG_STREAM(loggerID, level, filename.c_str(), lineNum, tempMsg);
    this->DoLogCallback(level, location, QString(message.c_str()));
}

void HLogger::Log(int loggerID, int level, qulonglong classID, HCodeLocation location, std::string message)
{
    int lineNum = location.GetLineNumber();
    std::string filename = location.GetFileName();
    std::string funcname = location.GetFunctionNameFull();
    std::string tempMsg = message;
    tempMsg.append(" <-- ").append(location.GetFunctionNameFull());
    LOG_STREAM(loggerID, level, filename.c_str(), lineNum, tempMsg);
    this->DoLogCallback(level, classID, location, QString(message.c_str()));
}

void HLogger::Dump(int loggerID, int level, const void *buffer, size_t bufLen, std::string msg /* = "" */)
{
    char binaryBuf[DEAFAULT_LOG_BUFFER_LENGTH] = { 0 };
    zlog::ZLogStream binaryStream(binaryBuf, DEAFAULT_LOG_BUFFER_LENGTH);
    binaryStream << zlog::ZLogBinary(buffer, bufLen);
    LOG_STREAM(loggerID, level, "null", 0, msg + binaryBuf);
    this->DoLogCallback(level, HCodeLocation("null", "", 0), QString("%1 %2").arg(msg.c_str()).arg(binaryBuf));
}

void HLogger::Dump(int loggerID, int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg /* = "" */)
{
    char binaryBuf[DEAFAULT_LOG_BUFFER_LENGTH] = { 0 };
    zlog::ZLogStream binaryStream(binaryBuf, DEAFAULT_LOG_BUFFER_LENGTH);
    binaryStream << zlog::ZLogBinary(buffer, bufLen);
    int lineNum = location.GetLineNumber();
    std::string filename = location.GetFileName();
    std::string funcname = location.GetFunctionName();
    std::string tempString = msg + binaryBuf;
    tempString.append(location.GetFunctionNameFull());
    LOG_STREAM(loggerID, level, filename.c_str(), lineNum, tempString);
    this->DoLogCallback(level, location, QString(msg.append(binaryBuf).c_str()));
}

void HLogger::CollectData(HCodeLocation location, LogCollectionType collectType, std::string msg)
{
    int lineNum = location.GetLineNumber();
    std::string filename = location.GetFileName();
    std::string tempMsg(msg);
    tempMsg.append(" <-- ").append(location.GetFunctionNameFull());
    LOG_STREAM(ms_CollectionLogs[collectType], HLOG_LEVEL_INFO, filename.c_str(), lineNum, tempMsg);
}

void HLogger::DoLogCallback(int logLevel, HCodeLocation location, QString logMsg)
{
    static const char* logLevelString[HLOG_LEVEL_NONE] = { "TRACE", "DEBUG", "INFO", "WARN ", "ERROR", "ALAEM", "FATAL" };
    int lineNum = location.GetLineNumber();
    QString filename = QString::fromStdString(location.GetFileName());
    QString funcname = QString::fromStdString(location.GetFunctionNameFull());
    QMutexLocker locker(&m_MutexCallbackList);
    QList<ILogCallback*>::Iterator it = m_ListCallback.begin();
    if (it != m_ListCallback.end())
    {
        qulonglong tid = (qulonglong)QThread::currentThreadId();

        QString timeString = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        (*it)->LogCommon(logLevel, tid, lineNum, filename, funcname, logMsg, timeString);

        QString oneLineMsg = timeString;
        oneLineMsg.append("[").append(QString("%1").arg(tid, 6, 10, QLatin1Char('0'))).append("]");
        if (logLevel>=HLOG_LEVEL_DEBUG && logLevel<=HLOG_LEVEL_NONE)
        {
            oneLineMsg.append(" ").append(logLevelString[logLevel]);
        }
        oneLineMsg.append(" ").append(logMsg);
        oneLineMsg.append(" <-- ").append(filename).append(":").append(QString("%1").arg(lineNum));
        (*it)->LogOneLine(logLevel, oneLineMsg);
    }
}

void HLogger::DoLogCallback(int logLevel, qulonglong classID, HCodeLocation location, QString logMsg)
{
    int lineNum = location.GetLineNumber();
    QString filename = QString::fromStdString(location.GetFileName());
    QString funcname = QString::fromStdString(location.GetFunctionNameFull());
    QMutexLocker locker(&m_MutexCallbackList);
    QList<ILogCallback*>::Iterator it = m_ListCallback.begin();
    if (it != m_ListCallback.end())
    {
        qulonglong tid = (qulonglong)QThread::currentThreadId();
        QString timeString = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        (*it)->LogDevice(logLevel, tid, classID, lineNum, filename, funcname, logMsg, timeString);
    }
}
