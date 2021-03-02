#ifndef H_LOG_DEFINES_H
#define H_LOG_DEFINES_H

#include <QString>

#define DEAFAULT_LOG_BUFFER_LENGTH 2048

#ifdef WIN32
#define VA_FORMAT(buffer, fmt, length) \
va_list vaList; \
va_start(vaList, fmt); \
vsnprintf(buffer, length, fmt, vaList); \
va_end(vaList);
#else
#define VA_FORMAT(buffer, fmt, length) \
va_list vaList; \
va_start(vaList, fmt); \
snprintf(buffer, length, fmt, vaList); \
va_end(vaList);
#endif

#define REGISTER_FRIEND_CLASS(ClassName) \
friend class ClassName;

enum LogLevelType
{
    HLOG_LEVEL_TRACE,
    HLOG_LEVEL_DEBUG,
    HLOG_LEVEL_INFO,
    HLOG_LEVEL_WARN,
    HLOG_LEVEL_ERROR,
    HLOG_LEVEL_ALARM,
    HLOG_LEVEL_FATAL,
    HLOG_LEVEL_NONE
};

/************************************************************************/
/*  预留调试数据收集日志，每个数据采集项对应一个独立的日志文件              */
/*  避免与其他日志内容杂糅在一起                                          */
/************************************************************************/
enum LogCollectionType
{
    LOG_COLLECTION_TYPE_0,
    LOG_COLLECTION_TYPE_1,
    LOG_COLLECTION_TYPE_2,
    LOG_COLLECTION_TYPE_3,
    LOG_COLLECTION_TYPE_4,
    LOG_COLLECTION_TYPE_MAX,
};

#endif // H_LOG_DEFINES_H
