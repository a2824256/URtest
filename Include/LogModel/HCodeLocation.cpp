#include "HCodeLocation.h"

#include <iostream>
#include <sstream>

HCodeLocation::HCodeLocation(const char* fileName, const char* funcName, int lineNumber)
    : m_strFileName(fileName)
    , m_strFuncName(funcName)
    , m_nLineNumber(lineNumber)
{
}

HCodeLocation::~HCodeLocation()
{
    //std::cout << "HCodeLocation::~HCodeLocation()" << std::endl;
}

int HCodeLocation::GetLineNumber()
{
    return m_nLineNumber;
}

std::string HCodeLocation::GetFileName()
{
    return m_strFileName;
}

std::string HCodeLocation::GetShortFileName()
{
    size_t index = std::string::npos;
    m_strShortFileName = m_strFileName;

    index = m_strFileName.find_last_of('\\');
    if (index != std::string::npos)
    {
        m_strShortFileName.erase(0, index + 1);
    }

    return m_strShortFileName;
}

std::string HCodeLocation::GetShortClassName()
{
    std::string className("");
    size_t index = m_strFuncName.find_last_of(":");
    if (index != std::string::npos)
    {
        className = m_strFuncName.substr(0, index - 1);
    }
    index = className.find_last_of(":");
    if (index != std::string::npos)
    {
        className.erase(0, index + 1);
    }

    return className;
}

std::string HCodeLocation::GetFunctionName()
{
    std::string funcName = m_strFuncName;
    size_t index = funcName.find_last_of(":");
    if (index != std::string::npos)
    {
        funcName.erase(0, index + 1);
    }

    return funcName;
}

std::string HCodeLocation::GetFunctionNameFull()
{
    return m_strFuncName;
}

std::string HCodeLocation::ToString()
{
    std::ostringstream oss;
    oss << m_nLineNumber;
    std::string retString = "[ ";
    retString.append(m_strFuncName);
    retString.append(" ");
    retString.append(GetShortFileName());
    retString.append(":");
    retString.append(oss.str());
    retString.append(" ]");

    return retString;
}
