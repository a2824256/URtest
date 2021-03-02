#ifndef H_OPERATION_LOGGER_H
#define H_OPERATION_LOGGER_H

#include "HCommonLogger.h"

class LOGMODEL_EXPORT HOperationLogger : public HCommonLogger
{
    REGISTER_FRIEND_CLASS(HLogManager)

public:
    ~HOperationLogger();

private:
    HOperationLogger();

    virtual void LogProxy(int level, HCodeLocation location, std::string message) override;
    virtual void DumpProxy(int level, const void *buffer, size_t bufLen, std::string msg = "") override;
    virtual void DumpProxy(int level, HCodeLocation location, const void *buffer, size_t bufLen, std::string msg = "") override;
};

#endif // H_OPERATION_LOGGER_H
