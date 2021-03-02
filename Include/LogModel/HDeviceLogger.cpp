#include "HDeviceLogger.h"

QMap<qulonglong, QString> HDeviceLogger::ms_mapClassID;

HDeviceLogger::HDeviceLogger()
{
}

HDeviceLogger::~HDeviceLogger()
{
}

void HDeviceLogger::AddDeviceClassID(qulonglong classID, const QString& className)
{
    ms_mapClassID.insert(classID, className);
}

QMap<qulonglong, QString> HDeviceLogger::GetDeviceClassMap()
{
    return ms_mapClassID;
}

//void HDeviceLogger::Debug(HDevice *pClass, const char *fmt, ...)
//{
//    if (ms_LogLevel <= HLOG_LEVEL_DEBUG)
//    {
//        std::string fieldString = this->GetFieldString();
//        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
//        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
//        fieldString.append(msgBuffer);
//        HLogger::Log(HLOG_LEVEL_DEBUG, fieldString.c_str());
//    }
//}
//
//void HDeviceLogger::Debug(HDevice *pClass, HCodeLocation location, const char *fmt, ...)
//{
//    if (ms_LogLevel <= HLOG_LEVEL_DEBUG)
//    {
//        std::string fieldString = this->GetFieldString();
//        char msgBuffer[DEAFAULT_LOG_BUFFER_LENGTH];
//        VA_FORMAT(msgBuffer, fmt, DEAFAULT_LOG_BUFFER_LENGTH - 1);
//        fieldString.append(msgBuffer);
//        HLogger::Log(HLOG_LEVEL_DEBUG, location, fieldString.c_str());
//    }
//}

//std::string HDeviceLogger::GetFieldString(void *pClass)
//{
//    std::string fieldString;
//    QMap<QString, IFieldValue*>::Iterator mapIt = m_mapLogField.begin();
//    while (mapIt != m_mapLogField.end())
//    {
//        IFieldValue *pField = mapIt.value();
//        fieldString += pField->GetFormatString(pClass).c_str();
//        fieldString += " ";
//        ++mapIt;
//    }
//    return fieldString;
//}
