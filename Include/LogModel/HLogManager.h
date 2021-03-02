#ifndef H_LOG_MANAGER_H
#define H_LOG_MANAGER_H

#include "LogModel_global.h"

#include "HDeviceLogger.h"
#include "HCommonLogger.h"
#include "HOperationLogger.h"
#include "HConsoleLogger.h"
#include "HLogDefines.h"
#include "HFieldInfo.h"
#include "HAlarmLogger.h"

class LOGMODEL_EXPORT HLogManager
{
public:
    HLogManager() = delete;
    HLogManager(HLogManager &) = delete;

    static void Initialize(LogLevelType logLevel, bool isDisplayOnConsole);
    static HDeviceLogger* GetDeviceLog();
    static HCommonLogger* GetCommonLog();
    static HOperationLogger* GetOperationLog();
    static HConsoleLogger* GetConsoleLog();
    static HAlarmLogger* GetAlarmLog() ;
};

#endif // H_LOG_MANAGER_H
