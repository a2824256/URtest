#ifndef H_CODE_LOCATION_H
#define H_CODE_LOCATION_H

#include "LogModel_global.h"
#include <string>

#define HCODE_LOCATION HCodeLocation(__FILE__,__FUNCTION__,__LINE__)
#define HCODE_LOCATION_STRING HCodeLocation(__FILE__,__FUNCTION__,__LINE__).ToString()

class LOGMODEL_EXPORT HCodeLocation
{
private:
    std::string m_strFileName;       // 源文件名(含绝对路径)
    std::string m_strShortFileName;  // 短文件名(无绝对路径)
    std::string m_strFuncName;       // 函数名（全名  namespace::class::MemberFunction）
    int m_nLineNumber;               // 行号

public:
    HCodeLocation(const char* fileName, const char* funcName, int lineNumber);
    ~HCodeLocation();

    int GetLineNumber();
    std::string GetFileName();
    std::string GetShortFileName();
    std::string GetShortClassName();
    std::string GetFunctionName();
    std::string GetFunctionNameFull();
    std::string ToString();
};

#endif // H_CODE_LOCATION_H
