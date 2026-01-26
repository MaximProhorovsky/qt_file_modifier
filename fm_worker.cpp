#include "fm_worker.h"

#include <QDir>
#include <QMutex>
#include <QStringList>
#include <QtConcurrent/QtConcurrent>

FileWorker::FileWorker(QObject *parent) : QObject(parent)
{}

QFileInfoList FileWorker::readFilesFromInDir()
{
    return inDir.entryInfoList(QStringList{fileMask}, QDir::Files);
}

void FileWorker::onScanButtonClicked()
{
    QFileInfoList files = readFilesFromInDir();
    emit filesScanned(files);
}

void FileWorker::processFiles(qint64 value)
{
    QFileInfoList files = readFilesFromInDir();
    for (const QFileInfo &fileInfo : files) {
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>;
        connect(watcher, &QFutureWatcherBase::finished, this, [=](){
            qDebug() << "Завершен файл: " << fileInfo.fileName();
            watcher->deleteLater();
            watchers.removeOne(watcher);
            if(watchers.isEmpty()){
                emit allFilesProcessed();
                qDebug() << "Все файлы обработаны";
            }
        });
        qDebug() << "Старт обработки файла: " << fileInfo.fileName();
        QFuture<void> future = QtConcurrent::run([&](){
            this->processFile(fileInfo, value, true);
        });
        watcher->setFuture(future);
        watchers.append(watcher);
    }
}

void FileWorker::processFile(const QFileInfo &fileInfo, qint64 value, bool overwrite)
{
    const QString &fileName = fileInfo.fileName();
    QFile inFile{fileInfo.absoluteFilePath()};
    QFile outFile{this->outDir.absoluteFilePath(fileName)};
    if (!inFile.exists()) {
        qWarning() << "Входной файл не найден:" << fileName;
        emit fileProcessed(fileName, false);
        return;
    }
    if (!inFile.open(QIODevice::ReadWrite)) {
        qWarning() << "Не удалось открыть исходный файл:" << fileName;
        emit fileProcessed(fileName, false);
        return;
    }

    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Не удалось создать выходной файл:" << fileName;
        emit fileProcessed(fileName, false);
        return;
    }

    qint64 totalSize = inFile.size();
    qint64 processedBytes = 0;

    while (processedBytes < totalSize) {
        emit fileProcessUpdated(fileName, processedBytes/totalSize);
        qint64 chunkSize = qMin(PARTITION_SIZE, totalSize - processedBytes);
        if (!inFile.seek(processedBytes)) {
            qWarning() << "Не удалось перейти к позиции" << processedBytes << "в файле" << fileName;
            emit fileProcessed(fileName, false);
            return;
        }
        QByteArray buffer = inFile.read(chunkSize);
        if (buffer.isEmpty() && chunkSize > 0) {
            qWarning() << "Ошибка чтения файла" << fileName;
            emit fileProcessed(fileName, false);
            return;
        }

        for (int i = 0; i < buffer.size(); ++i) {
            buffer[i] = buffer[i] ^ value;
        }

        if (!inFile.seek(processedBytes)) {
            qWarning() << "Не удалось вернуться к позиции" << processedBytes << "в файле" << fileName;
            emit fileProcessed(fileName, false);
            return;
        }
        qint64 written = outFile.write(buffer);
        if (written != buffer.size()) {
            qWarning() << "Ошибка записи файла" << fileName;
            emit fileProcessed(fileName, false);
            return;
        }
        processedBytes += chunkSize;
    }
    emit fileProcessed(fileName, true);
    inFile.close();
    outFile.close();
}

