#include "fm_worker.h"

#include <QDir>
#include <QMutex>
#include <QStringList>
#include <QtConcurrent/QtConcurrent>


QByteArray readFile(const QDir &dir, const QString &fileName)
{
    QFile file{dir.absoluteFilePath(fileName)};
    if(!file.open(QIODevice::WriteOnly)){
        qWarning() << "Не удалось открыть файл для чтения: " << file.fileName();
        return QByteArray();
    }
    QByteArray data = file.readLine();
    file.close();
    return data;
}

void FileWorker::processFiles(const QDir &inDir, const QDir &outDir, const QString &fileMask, qint64 value)
{
    QFileInfoList files = inDir.entryInfoList(QStringList{fileMask}, QDir::Files);
    int totalFiles = files.size();
    int *processedCount = new int(0);

    for (const QFileInfo &fileInfo : files) {
        QFile file{fileInfo.absoluteFilePath()};
        QFile outFile{outDir.absoluteFilePath(fileInfo.fileName())};
        auto test = QtConcurrent::run([=, &file, &outFile](){ this->processFile(file, outFile, value, true);});
        test.waitForFinished();
    }
    delete processedCount;
}

void FileWorker::processFile(QFile &inFile, QFile &outFile, qint64 value, bool overwrite)
{
    const QString &fileName = inFile.fileName();
    qInfo() << "Start Process file: " << fileName;
    if (!inFile.exists()) {
        qWarning() << "Входной файл не найден:" << fileName;
        emit fileProcessed(fileName, false);
        return;
    }
    if (!inFile.open(QIODevice::ReadWrite)) {
        qWarning() << "Не удалось открыть входной файл:" << fileName;
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
    qInfo() << "End Process file: " << fileName;
}
