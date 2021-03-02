#include "HLogCleaner.h"

#include <QDir>
#include <QDate>
#include <zip.h>

#include "HLogManager.h"

//HLogCleaner::AutoDestructHelper HLogCleaner::m_gAutoDestructHelper;

/* 整理日志 */
HLogCleaner::HLogCleaner(QObject *parent /* = Q_NULLPTR */)
    : QThread(parent)
    , m_runningFlag(false)
{
    //m_gAutoDestructHelper.AddCleaner(this);
}

HLogCleaner::~HLogCleaner()
{
    this->Stop();
    //this->wait(100);
    //m_gAutoDestructHelper.RemoveCleaner(this);
}

void HLogCleaner::Start()
{
    m_runningFlag = true;
    this->QThread::start();
}

void HLogCleaner::Stop()
{
    m_runningFlag = false;
}

void HLogCleaner::CleanLogFiles(const QString& filename)
{
    QRegExp regExpLogZlog("^((?!_)\\w+)_(?!_)\\w+_(\\d{8})_\\d{5}.log$");
    int pos = regExpLogZlog.indexIn(filename);
    int captureCount = regExpLogZlog.captureCount();
    if (pos != -1 && captureCount == 2)
    {
        QString createZipFilename = regExpLogZlog.cap(1) + "_" + regExpLogZlog.cap(2) + ".zip";
        QDate curDate = QDate::currentDate();
        QDate zipCreatedDate = QDate::fromString(regExpLogZlog.cap(2), "yyyyMMdd");
        if (zipCreatedDate < curDate)
        {
            QList<QString>& filesInZip = m_mapZipFilename[createZipFilename];
            filesInZip.append(filename);
        }
    }
    else
    {
        HLogManager::GetCommonLog()->Debug(HCODE_LOCATION, "%s indexIn %s does not match any string.", regExpLogZlog.pattern().toUtf8().data(), filename.toUtf8().data());
    }

    QRegExp regExpLogWebRTC("^((?!_)\\w+)_(\\d{4})-(\\d{2})-(\\d{2})_\\d{6}.log$");
    int rtcPos = regExpLogWebRTC.indexIn(filename);
    int rtcCaptureCount = regExpLogWebRTC.captureCount();
    if (rtcPos != -1 && rtcCaptureCount == 4)
    {
        QString rtcLogDate = regExpLogWebRTC.cap(2) + regExpLogWebRTC.cap(3) + regExpLogWebRTC.cap(4);
        QString createZipFilename = regExpLogWebRTC.cap(1) + "_" + rtcLogDate + ".zip";
        QDate curDate = QDate::currentDate();
        QDate zipCreatedDate = QDate::fromString(rtcLogDate, "yyyyMMdd");
        if (zipCreatedDate < curDate)
        {
            QList<QString>& filesInZip = m_mapZipFilename[createZipFilename];
            filesInZip.append(filename);
        }
    }
    else
    {
        HLogManager::GetCommonLog()->Debug(HCODE_LOCATION, "%s indexIn %s does not match any string.", regExpLogWebRTC.pattern().toUtf8().data(), filename.toUtf8().data());
    }
}

void HLogCleaner::CleanZipFiles(const QString& filename)
{
    QRegExp regExpLogFilename("^(?!_)\\w+_(\\d{8}).zip$");
    int pos = regExpLogFilename.indexIn(filename);
    int captureCount = regExpLogFilename.captureCount();
    if (pos != -1 && captureCount == 1)
    {
        QDate curDate = QDate::currentDate();
        QDate zipCreatedDate = QDate::fromString(regExpLogFilename.cap(1), "yyyyMMdd");
        HLogManager::GetCommonLog()->Debug(HCODE_LOCATION, "Compressed archive was created at: %s", zipCreatedDate.toString("yyyy-MM-dd").toUtf8().data());
        if (zipCreatedDate.daysTo(curDate) > 365)
        {
            QDir logDir("./logs");
            QString fullFileInZip = logDir.absolutePath() + "/" + filename;
            HLogManager::GetCommonLog()->Warn(HCODE_LOCATION, "Compressed archive will be deleted: %s", fullFileInZip.toUtf8().data());
            QFile::remove(fullFileInZip);
        }
    }
}

void HLogCleaner::MakeLogZipFiles(const QString& zipFilename, const QList<QString>& filenameInZip)
{
    HLogManager::GetCommonLog()->Info(HCODE_LOCATION, "Compressed archive will be created: %s", zipFilename.toUtf8().data());
    
    QDir logDir("./logs");
    QString tempFileInZip;
    QString fullZipFilename = logDir.absolutePath() + "/" + zipFilename;

    int errCode = ZIP_ER_OK;
    zip_t *pZipArchive = NULL;
    zip_source_t *pSourceFile = NULL;
    zip_error_t *pSourceFileError = NULL;

    pZipArchive = zip_open(fullZipFilename.toUtf8().data(), ZIP_CREATE, &errCode);
    if (pZipArchive == NULL)
    {
        zip_error_t error;
        zip_error_init_with_code(&error, errCode);
        HLogManager::GetCommonLog()->Error(HCODE_LOCATION, "Open or create file %s failed. Error[%d]: %s", fullZipFilename.toUtf8().data(), errCode, zip_error_strerror(&error));
        zip_error_fini(&error);
        return;
    }

    for (int i = 0; i < filenameInZip.size(); ++i)
    {
        QString filename = filenameInZip[i];
        tempFileInZip = logDir.absolutePath() + "/" + filename;
        HLogManager::GetCommonLog()->Debug(HCODE_LOCATION, "File in Zip: %s", tempFileInZip.toUtf8().data());
        pSourceFile = zip_source_file_create(tempFileInZip.toUtf8().data(), 0, 0, pSourceFileError);
        zip_add(pZipArchive, filename.toUtf8().data(), pSourceFile);
    }

    zip_close(pZipArchive);

    for (int i = 0; i < filenameInZip.size(); ++i)
    {
        QString filename = filenameInZip[i];
        tempFileInZip = logDir.absolutePath() + "/" + filename;
        bool resFlag = QFile::remove(tempFileInZip);
        HLogManager::GetCommonLog()->Debug(HCODE_LOCATION, "Remove %s %s", tempFileInZip.toUtf8().data(), resFlag ? "successfully" : "failed");
    }
}

void HLogCleaner::run()
{
    HLogManager::GetCommonLog()->Info(HCODE_LOCATION, "------------------------ Log clean up begin ------------------------");
    QDir logDir("./logs");
    QStringList logFiles = logDir.entryList(logDir.filter() | QDir::NoDotAndDotDot);

    for (int i = 0; i < logFiles.size(); ++i)
    {
        QString filename = logFiles[i];
        if (m_runningFlag)
        {
            if (filename.endsWith(".log"))
            {
                //HLogManager::GetCommonLog()->Debug(HCODE_LOCATION, "log file : %s", filename.toUtf8().data());
                this->CleanLogFiles(filename);
            }
            else if (filename.endsWith(".zip"))
            {
                HLogManager::GetCommonLog()->Debug(HCODE_LOCATION, "zip file : %s", filename.toUtf8().data());
                this->CleanZipFiles(filename);
            }
        }
        else
        {
            break;
        }
    }

    QMap<QString, QList<QString>>::const_iterator tempIt = m_mapZipFilename.constBegin();
    QMap<QString, QList<QString>>::const_iterator endIt = m_mapZipFilename.constEnd();
    while (tempIt != endIt)
    {
        if (m_runningFlag)
        {

            this->MakeLogZipFiles(tempIt.key(), tempIt.value());
        }
        else
        {
            break;
        }

        ++tempIt;
    }

    HLogManager::GetCommonLog()->Info(HCODE_LOCATION, "------------------------ Log clean up end ------------------------");
}
