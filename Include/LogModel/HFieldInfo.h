#ifndef H_FIELD_INFO_H
#define H_FIELD_INFO_H

#include <QString>
#include <QList>
#include <type_traits>

/********************************************************************/
/*  动态绑定类成员，实现日志内容定制（针对设备日志 ID Name 输出）      */
/*******************************************************************/

template<typename T, typename V>
std::string Global_FormatFieldString(T* pOnwer, V T::*fieldMember, const std::string& fieldTip)
{
    std::string retValue = fieldTip;
    retValue += ":UnsupportedType";
    return retValue;
}

template<typename T, typename V>
std::string Global_FormatFieldString(T* pOnwer,
                                     typename std::enable_if<!std::is_class<V>::value && std::is_integral<V>::value && std::is_signed<V>::value,V>::type T::*fieldMember,
                                     const std::string& fieldTip)
{
    char fieldBuffer[128] = { 0 };
    sprintf_s(fieldBuffer, 128, ":%ld", pOnwer->*fieldMember);
    std::string retValue = fieldTip;
    retValue += fieldBuffer;
    return retValue;
}

template<typename T, typename V>
std::string Global_FormatFieldString(T* pOnwer, typename std::enable_if<!std::is_class<V>::value && std::is_integral<V>::value && std::is_unsigned<V>::value, V>::type T::*fieldMember, const std::string& fieldTip)
{
    char fieldBuffer[128] = { 0 };
    sprintf_s(fieldBuffer, 128, ":%lu", pOnwer->*fieldMember);
    std::string retValue = fieldTip;
    retValue += fieldBuffer;
    return retValue;
}

template<typename T, typename V>
std::string Global_FormatFieldString(T* pOnwer, typename std::enable_if<!std::is_class<V>::value && !std::is_integral<V>::value && std::is_arithmetic<V>::value, V>::type T::*fieldMember, const std::string& fieldTip)
{
    char fieldBuffer[128] = { 0 };
    sprintf_s(fieldBuffer, 128, ":%lf", pOnwer->*fieldMember);
    //sprintf_s(fieldBuffer, 128, ":%lf(%e)", pOnwer->*fieldMember, pOnwer->*fieldMember);
    std::string retValue = fieldTip;
    retValue += fieldBuffer;
    return retValue;
}

template<typename T, typename V>
std::string Global_FormatFieldString(T* pOnwer, typename std::enable_if<std::is_pointer<V>::value, V>::type T::*fieldMember, const std::string& fieldTip)
{
    char fieldBuffer[128] = { 0 };
    sprintf_s(fieldBuffer, 128, ":0x%p", pOnwer->*fieldMember);
    std::string retValue = fieldTip;
    retValue += fieldBuffer;
    return retValue;
}

template<typename T, typename V>
std::string Global_FormatFieldString(T* pOnwer, std::string T::*fieldMember, const std::string& fieldTip)
{
    char fieldBuffer[128] = { 0 };
    sprintf_s(fieldBuffer, 128, ":%s", (pOnwer->*fieldMember).empty() ? "null" : (pOnwer->*fieldMember).c_str());
    std::string retValue = fieldTip;
    retValue += fieldBuffer;
    return retValue;
}

template<typename T, typename V>
std::string Global_FormatFieldString(T* pOnwer, QString T::*fieldMember, const std::string& fieldTip)
{
    char fieldBuffer[128] = { 0 };
    QString tempField = pOnwer->*fieldMember;
    if (tempField.isEmpty())
    {
        tempField = "null";
    }
    sprintf_s(fieldBuffer, 128, ":%s", tempField.toStdString().c_str());
    std::string retValue = fieldTip;
    retValue += fieldBuffer;
    return retValue;
}

/************************************************************************/
/* 作为没有基类的标识，不可继承，不科实例化 。                             */
/*     绑定字段时继承该类，则跳过基类处理                                 */
/************************************************************************/
#define NONE_BASE_CLASS none_base_class
class none_base_class
{
private:
    none_base_class() {}
public:
    virtual ~none_base_class() {}
    virtual void FormatFieldString() = 0;
};

template<typename T>
class IFieldInfo
{
public:
    IFieldInfo() {}
    virtual ~IFieldInfo() {}

    virtual std::string FormatString(T* pOwnerClass) = 0;
};

template <typename T, typename V>
class HFiledInfo : public IFieldInfo<T>
{
private:
    V T::* mFieldMember;
    std::string mFiledTip;

public:
    HFiledInfo(const std::string& fieldTip, V T::* fieldMember)
        :mFieldMember(fieldMember) 
        , mFiledTip(fieldTip)
    {
    }

    ~HFiledInfo() {}

    virtual std::string FormatString(T *pOwner) override
    {
        std::string retValue = mFiledTip + ":FailedFormat";
        if (pOwner != nullptr)
        {
            retValue = Global_FormatFieldString<T, V>(pOwner, mFieldMember, mFiledTip);
        }
        return retValue;
    }
};

#define BEGIN_FIELD_MAP(ClassType, ClassName, BassClass)                                              \
private:                                                                                   \
    static QList<IFieldInfo<ClassType>*> ms_fieldInfoList;                                 \
    class AutoDestructHelper                                                                       \
    {                                                                                      \
    public:                                                                                \
        AutoDestructHelper()                                                                       \
        {                                                                                  \
            HDeviceLogger::AddDeviceClassID(typeid(ClassType).hash_code(), QString(ClassName));

#define REGISTER_FIELD_INFO(tip, T, V, fieldMember)                                        \
            ms_fieldInfoList.push_back(new HFiledInfo<T, V>(tip, fieldMember));

#define END_FIELD_MAP(ClassType, BaseClass)                                                \
        }                                                                                  \
        ~AutoDestructHelper()                                                                      \
        {                                                                                  \
            while (!ms_fieldInfoList.isEmpty())                                            \
            {                                                                              \
                QList<IFieldInfo<ClassType>*>::Iterator it = ms_fieldInfoList.begin();     \
                IFieldInfo<ClassType> *pFieldInfo = *it;                                   \
                ms_fieldInfoList.erase(it);                                                \
                delete pFieldInfo;                                                         \
            }                                                                              \
        }                                                                                  \
    };                                                                                     \
    static AutoDestructHelper autoHelper;                                                          \
public:                                                                                    \
    size_t GetClassID()                                                                    \
    {                                                                                      \
        static size_t hashCode = typeid(ClassType).hash_code();                            \
        return hashCode;                                                                   \
    }                                                                                      \
    std::string FormatFieldString()                                                        \
    {                                                                                      \
        std::string fieldString;                                                           \
        QList<IFieldInfo<ClassType>*>::Iterator listIt = ms_fieldInfoList.begin();         \
        while (listIt != ms_fieldInfoList.end())                                           \
        {                                                                                  \
            IFieldInfo<ClassType> *pField = *listIt;                                       \
            if (listIt != ms_fieldInfoList.begin())                                        \
            {                                                                              \
                fieldString += " ";                                                        \
            }                                                                              \
            fieldString += pField->FormatString(this).c_str();                             \
            ++listIt;                                                                      \
        }                                                                                  \
        std::string parentField = Global_GetParentFieldString<ClassType, BaseClass>(this); \
        if (!parentField.empty())                                                          \
        {                                                                                  \
            fieldString.append(" ");                                                       \
            fieldString.append(parentField);                                               \
        }                                                                                  \
        return fieldString;                                                                \
    }

#define REGISTER_FIELD_LIST(ClassType)                                                     \
QList<IFieldInfo<ClassType>*> ClassType::ms_fieldInfoList;                                 \
ClassType::AutoDestructHelper ClassType::autoHelper;

//private:
//    static QList<IFieldInfo<HOperatingHandle>*> ms_fieldInfoList;
//    class AutoHelper
//    {
//    public:
//        AutoHelper()
//        {
//            ms_fieldInfoList.push_back(new HFiledInfo<HOperatingHandle, double>("PressureValue", &HOperatingHandle::m_dPressureDispValue));
//        }
//        ~AutoHelper()
//        {
//            while (!ms_fieldInfoList.isEmpty())
//            {
//                QList<IFieldInfo<HOperatingHandle>*>::Iterator it = ms_fieldInfoList.begin();
//                IFieldInfo<HOperatingHandle> *pFieldInfo = *it;
//                ms_fieldInfoList.erase(it);
//                delete pFieldInfo;
//            }
//        }
//    };
//    static AutoHelper autoHelper;
//public:
//    std::string FormatFieldString()
//    {
//        std::string fieldString;
//        QList<IFieldInfo<HOperatingHandle>*>::Iterator listIt = ms_fieldInfoList.begin();
//        while (listIt != ms_fieldInfoList.end())
//        {
//            IFieldInfo<HOperatingHandle> *pField = *listIt;
//            if (listIt != ms_fieldInfoList.begin())
//            {
//                fieldString += " ";
//            }
//            fieldString += pField->FormatString(this).c_str();
//            ++listIt;
//        }
//        std::string parentField = Global_GetParentFieldString<HOperatingHandle, HDevice>(this);
//        if (!parentField.empty())
//        {
//            fieldString.append(" ");
//            fieldString.append(parentField);
//        }
//        return fieldString;
//    }

#define HAS_MEMBER_FUNCTION(XXX)                                \
template<typename T>                                            \
struct has_member_function_##XXX                                \
{                                                               \
    template<typename U, std::string (U::*)() = &U::XXX>        \
    static constexpr bool check(U*) { return true; }            \
    static constexpr bool check(...) { return false; }          \
    static constexpr bool value = check(static_cast<T*>(0));    \
};
HAS_MEMBER_FUNCTION(FormatFieldString)
#undef HAS_MEMBER_FUNCTION

template<typename Derived, typename Base>
std::string Global_GetParentFieldString(Derived* pclass)
{
    Q_UNUSED(pclass);
    return std::string("");
}

template<typename Derived, typename Base, std::string (Base::*)() = &Base::FormatFieldString>
std::string Global_GetParentFieldString(
    typename std::enable_if<std::is_base_of<Base, Derived>::value, Derived>::type *pClass)
{
    return pClass->Base::FormatFieldString();
}

#endif // H_FIELD_INFO_H
