#ifndef FILE_WORKER_H
#define FILE_WORKER_H

#include <QDir>
#include <QFuture>
#include <QStringList>
#include <QTimer>
#include "setting.h"

class FileWorker : public QObject
{
Q_OBJECT
public:
    FileWorker(QObject *parent = nullptr);
    void processFiles();
    QFileInfoList readFilesFromInDir();
signals:
    void fileProcessingStarted();
    void fileProcessed(const QString &fileName, bool isSuccess);
    void allFilesProcessed();
    void filesScanned(const QFileInfoList &files);
public slots:
    void onScanButtonClicked();
    void onTimerChanged(qint32 timeout);
    void onProcessingRequested();
    void onInDirChanged(const QDir &newDir){ this->inDir = newDir; }
    void onOutDirChanged(const QDir &newDir){ this->outDir = newDir; }
    void onFileMaskChanged(const QString &fileMask);
    void onOverwriteChanged(bool value) { this->overwrite = value; }
    void onDeleteSrcFilesChanged(bool value) { this->deleteSrcFiles = value; }
    void onRunWithTimerChanged(bool value);
    void onModifierValueChanged(qint64 value) { this->modifierValue = value; }
private:
    const qint64 PARTITION_SIZE = 1<<20;
    QMetaObject::Connection timerConnection;
    QTimer *timer;
    QFileInfoList fileInfoList;
    QList<QFuture<void>> futures;
    QList<QFutureWatcher<void>*> watchers;
    QStringList fileMasks{Setting::BASE_MASK};
    QDir inDir{Setting::BASE_DIR};
    QDir outDir{Setting::BASE_DIR};
    bool overwrite = Setting::OVERWRITE;
    bool deleteSrcFiles = Setting::DELETE_SRC_FILES;
    bool runWithTimer = Setting::WITH_TIMER;
    qint32 timeout = Setting::BASE_TIMEOUT;
    qint64 modifierValue = Setting::BASE_MODIFIER_VALUE;
    bool isFilesProcessing = false;

    void processFile(const QFileInfo &fileInfo, bool modifierValue, bool overwrite, bool deleteIn);
    QString generateUniqueFileName(const QFileInfo &fileInfo);
};

#endif // FILE_WORKER_H
