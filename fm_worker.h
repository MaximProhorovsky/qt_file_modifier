#ifndef FM_WORKER_H
#define FM_WORKER_H

#include <QDir>
#include <QStringList>

class FileWorker : public QObject
{
Q_OBJECT
public:
    void processFiles(const QDir &inDir, const QDir &outDir, const QString &fileMask, qint64 value);
signals:
    void fileProcessUpdated(const QString &fileName, double percent);
    void fileProcessed(const QString &fileName, bool isSuccess);
    void allFilesProcessed();
public slots:
    void inputDirChange(QDir &&newDir){ this->inDir = qMove(newDir);}
    void outputDirChange(QDir &&newDir){ this->outDir = qMove(newDir);}
private:
    const qint64 PARTITION_SIZE = 1<<20;
    QDir inDir;
    QDir outDir;

    void processFile(QFile &inFile, QFile &outFile, qint64 value, bool overwrite);
    void readFile(const QDir &dir, const QString &fileName);
    bool writeFile(const QDir &dir, const QString &fileName, const QByteArray &data);
};

#endif // FM_WORKER_H
