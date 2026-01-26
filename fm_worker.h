#ifndef FM_WORKER_H
#define FM_WORKER_H

#include <QDir>
#include <QFuture>
#include <QStringList>

class FileWorker : public QObject
{
Q_OBJECT
public:
    FileWorker(QObject *parent = nullptr);
    void processFiles(qint64 value);
    QFileInfoList readFilesFromInDir();
signals:
    void fileProcessUpdated(const QString &fileName, double percent);
    void fileProcessed(const QString &fileName, bool isSuccess);
    void allFilesProcessed();
    void filesScanned(const QFileInfoList &files);
public slots:
    void onScanButtonClicked();
    void inDirChange(QDir &newDir){ this->inDir = newDir; }
    void outDirChange(QDir &newDir){ this->outDir = newDir; }
private:
    const qint64 PARTITION_SIZE = 1<<20;

    QList<QFuture<void>> futures;
    QList<QFutureWatcher<void>*> watchers;
    QString fileMask{"*.txt"};
    QDir inDir{"C:/Users/maksi/qtSource/qt_file_modifier/files/"};
    QDir outDir{"C:/Users/maksi/qtSource/qt_file_modifier/results/"};

    void processFile(const QFileInfo &fileInfo, qint64 value, bool overwrite);
    void readFile(const QDir &dir, const QString &fileName);
    bool writeFile(const QDir &dir, const QString &fileName, const QByteArray &data);
};

#endif // FM_WORKER_H
