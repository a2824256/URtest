#ifndef H_LOG_CLEANER_H
#define H_LOG_CLEANER_H

#include <QThread>
#include <QList>
#include <QMap>

class HLogCleaner : public QThread
{
public:
    HLogCleaner(QObject *parent = Q_NULLPTR);
    ~HLogCleaner();
    void Start();
    void Stop();

private:
    void CleanLogFiles(const QString& filename);
    void CleanZipFiles(const QString& filename);
    void MakeLogZipFiles(const QString& zipFilename, const QList<QString>& filenameInZip);

protected:
    virtual void run();
    volatile bool m_runningFlag;

private:
    QMap<QString, QList<QString>> m_mapZipFilename;

//private:
//    class AutoDestructHelper
//    {
//    private:
//        QList<HLogCleaner*> m_listCleaners;
//    public: 
//        AutoDestructHelper() {}
//        ~AutoDestructHelper()
//        {
//            for each(HLogCleaner *pCleaner in m_listCleaners)
//            {
//                delete pCleaner;
//            }
//        }
//        void AddCleaner(HLogCleaner *pCleaner)
//        {
//            m_listCleaners.append(pCleaner);
//        }
//        void RemoveCleaner(HLogCleaner *pCleaner)
//        {
//            m_listCleaners.removeAll(pCleaner);
//        }
//    };
//    static AutoDestructHelper m_gAutoDestructHelper; 
};

#endif // H_LOG_CLEANER_H
