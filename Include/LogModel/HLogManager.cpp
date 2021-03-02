#include "HLogManager.h"

//#define VLD_FORCE_ENABLE
#include "vld.h"

/*******************************************************************************/
/* HDeviceLogger    : 设备日志，使用时须通过宏注册类信息，注册要格式化的数据成员， */
/*                    调试面板中可根据设备类型进行日志过滤。                      */
/* HConsoleLogger   : 控制台日志，内容仅输出到调试面板，适合大量重复性数据跟踪。   */
/* HOperationLogger : 操作日志，记录用户 UI 操作过程。                           */
/* HCommonLogger    : 通用日志，没有明确人类要求，用于调试跟踪问题。              */
/* HAlarmLogger    : 报警日志，设备出错时记录的详细日志，用于现场排查问题。              */
/*******************************************************************************/

void HLogManager::Initialize(LogLevelType logLevel, bool isDisplayOnConsole)
{
    HLogger::Initialize(logLevel, isDisplayOnConsole);
}

HDeviceLogger* HLogManager::GetDeviceLog()
{
    static HDeviceLogger deviceLogger;
    return &deviceLogger;
}

HCommonLogger* HLogManager::GetCommonLog()
{
    static HCommonLogger commonLogger;
    return &commonLogger;
}

HOperationLogger* HLogManager::GetOperationLog()
{
    static HOperationLogger operationLogger;
    return &operationLogger;
}

HConsoleLogger* HLogManager::GetConsoleLog()
{
    static HConsoleLogger consoleLogger;
    return &consoleLogger;
}

HAlarmLogger* HLogManager::GetAlarmLog()
{
    static HAlarmLogger alarmLogger;
    return &alarmLogger;
}
