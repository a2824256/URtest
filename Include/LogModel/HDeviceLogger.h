#ifndef H_DEVICE_LOGGER_H
#define H_DEVICE_LOGGER_H

#include "HCommonLogger.h"
#include <QString>
#include <QMap>

#define HCODE_LOCATION_DEVICE \
this,HCODE_LOCATION

class LOGMODEL_EXPORT HDeviceLogger : public HCommonLogger
{
    REGISTER_FRIEND_CLASS(HLogManager)

public:
    ~HDeviceLogger();
    static void AddDeviceClassID(qulonglong classID, const QString& className);
    static QMap<qulonglong, QString> GetDeviceClassMap();

    template <typename T>
    void Trace(T *pClass, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_TRACE)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_TRACE, pClass->GetClassID(), HCodeLocation("null", "", 0), fieldString.c_str());
        }
    }

    template <typename T>
    void Trace(T *pClass, HCodeLocation location, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_TRACE)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_TRACE, pClass->GetClassID(), location, fieldString.c_str());
        }
    }

    template <typename T>
    void Debug(T *pClass, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_DEBUG)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_DEBUG, pClass->GetClassID(), HCodeLocation("null", "", 0), fieldString.c_str());
        }
    }

    template <typename T>
    void Debug(T *pClass, HCodeLocation location, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_DEBUG)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_DEBUG, pClass->GetClassID(), location, fieldString.c_str());
        }
    }

    template <typename T>
    void Info(T *pClass, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_INFO)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_INFO, pClass->GetClassID(), HCodeLocation("null", "", 0), fieldString.c_str());
        }
    }

    template <typename T>
    void Info(T *pClass, HCodeLocation location, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_INFO)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_INFO, pClass->GetClassID(), location, fieldString.c_str());
        }
    }

    template <typename T>
    void Warn(T *pClass, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_WARN)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_WARN, pClass->GetClassID(), HCodeLocation("null", "", 0), fieldString.c_str());
        }
    }

    template <typename T>
    void Warn(T *pClass, HCodeLocation location, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_WARN)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_WARN, pClass->GetClassID(), location, fieldString.c_str());
        }
    }

    template <typename T>
    void Error(T *pClass, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_ERROR)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_ERROR, pClass->GetClassID(), HCodeLocation("null", "", 0), fieldString.c_str());
        }
    }

    template <typename T>
    void Error(T *pClass, HCodeLocation location, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_ERROR)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_ERROR, pClass->GetClassID(), location, fieldString.c_str());
        }
    }

    template <typename T>
    void Fatal(T *pClass, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_FATAL)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_FATAL, pClass->GetClassID(), HCodeLocation("null", "", 0), fieldString.c_str());
        }
    }

    template <typename T>
    void Fatal(T *pClass, HCodeLocation location, const char *fmt, ...)
    {
        if (pClass == nullptr) return;

        if (ms_LogLevel <= HLOG_LEVEL_FATAL)
        {
            char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
            VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
            std::string fieldString = this->GetFieldString<T>(pClass);
            fieldString.append(" ").append(msgBuffer);
            HLogger::Log(ms_DeviceLoggerID, HLOG_LEVEL_FATAL, pClass->GetClassID(), location, fieldString.c_str());
        }
    }

private:
    HDeviceLogger();

    template<class T>
    std::string GetFieldString(T *pClass)
    {
        return std::string("");
    }

    template<class T, std::string (T::*U)() = &T::FormatFieldString>
    std::string GetFieldString(typename std::enable_if<std::is_class<T>::value, T>::type *pClass)
    {
        return pClass->FormatFieldString();
    }

private:
    static QMap<qulonglong, QString>  ms_mapClassID;
};

#endif // H_DEVICE_LOGGER_H
