#include "file_worker.h"

#include <QDir>
#include <QMutex>
#include <QStringList>
#include <QtConcurrent/QtConcurrent>

FileWorker::FileWorker(QObject *parent) : QObject(parent)
{
    timer = new QTimer{this};
    timer->setInterval(this->timeout);
    if(runWithTimer){
        timerConnection = QObject::connect(timer, &QTimer::timeout, this, &FileWorker::onProcessingRequested);
        timer->start();
    }
}

void FileWorker::processFiles()
{
    if(fileInfoList.isEmpty()) return;
    emit fileProcessingStarted();
    qint64 localValue = this->modifierValue;
    bool localOverwrite = this->overwrite;
    bool localDeleteIn = this->deleteSrcFiles;
    this->isFilesProcessing = true;
    for (const QFileInfo &fileInfo : std::as_const(fileInfoList)) {
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>;
        qDebug() << "Старт обработки файла: " << fileInfo.fileName();
        QFuture<void> future = QtConcurrent::run([=](){
            this->processFile(fileInfo, localValue, localOverwrite, localDeleteIn);
        });
        connect(watcher, &QFutureWatcherBase::finished, this, [=](){
            qDebug() << "Завершен файл: " << fileInfo.fileName();
            watcher->deleteLater();
            watchers.removeOne(watcher);
            if(watchers.isEmpty()){
                qDeleteAll(watchers);
                watchers.clear();
                fileInfoList.clear();
                emit allFilesProcessed();
                qDebug() << "Все файлы обработаны";
                if(runWithTimer){
                    timer->start();
                }
                this->isFilesProcessing = false;
            }
        });
        watcher->setFuture(future);
        watchers.append(watcher);
    }
}

QFileInfoList FileWorker::readFilesFromInDir(){
    return inDir.entryInfoList(fileMasks, QDir::Files);
}

void FileWorker::onScanButtonClicked() {
    fileInfoList.clear();
    fileInfoList = readFilesFromInDir();
    emit filesScanned(fileInfoList);
}

void FileWorker::onTimerChanged(qint32 timeout){
    this->timeout = timeout;
    timer->setInterval(timeout);
}

void FileWorker::onProcessingRequested() {
    timer->stop();
    if(fileInfoList.isEmpty() || runWithTimer){
        fileInfoList = readFilesFromInDir();
        emit filesScanned(fileInfoList);
    }
    processFiles();
}

void FileWorker::onFileMaskChanged(const QString &fileMask) {
    this->fileMasks = fileMask.split(Setting::MASK_DELIMITER);
    std::transform(fileMasks.begin(), fileMasks.end(), fileMasks.begin(), [](QString &s){return s.trimmed();});
}

void FileWorker::onRunWithTimerChanged(bool value) {
    this->runWithTimer = value;
    if(value){
        if(!timerConnection){
            timerConnection = QObject::connect(timer, &QTimer::timeout, this, &FileWorker::onProcessingRequested);
            if(!isFilesProcessing) timer->start();
        }
    }else{
        if(timerConnection){
            timer->stop();
            QObject::disconnect(timerConnection);
        }
    }
}

void FileWorker::processFile(const QFileInfo &fileInfo, bool modifierValue, bool overwrite, bool deleteIn)
{
    const QString &fileName = fileInfo.fileName();
    QString outFileName = overwrite ? fileName : this->generateUniqueFileName(fileInfo);
    QFile inFile{fileInfo.absoluteFilePath()};
    QFile outFile{this->outDir.absoluteFilePath(outFileName)};
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
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Не удалось открыть выходной файл:" << fileName;
        emit fileProcessed(fileName, false);
        return;
    }

    qint64 totalSize = inFile.size();
    qint64 processedBytes = 0;

    bool isSuccess = true;
    while (processedBytes < totalSize) {
        QByteArray buffer = inFile.read(PARTITION_SIZE);
        for (int i = 0; i < buffer.size(); ++i) {
            buffer[i] = buffer[i] ^ modifierValue;
        }

        qint64 written = outFile.write(buffer);
        if (written != buffer.size()) {
            qWarning() << "Ошибка записи файла" << fileName;
            isSuccess = false;
            break;
        }
        processedBytes += buffer.size();
    }
    inFile.close();
    outFile.close();
    if(isSuccess && this->deleteSrcFiles && !inFile.remove()){
        qWarning() << "Не удалось удалить файл:" << fileName;
        isSuccess = false;
    }
    emit fileProcessed(fileName, isSuccess);
}

QString FileWorker::generateUniqueFileName(const QFileInfo &fileInfo)
{
    QString name = fileInfo.completeBaseName();
    QString extension = fileInfo.suffix();

    uint counter = 1;
    QString newName = fileInfo.fileName();
    QFileInfo newFileInfo{this->outDir, newName};
    while(newFileInfo.exists()){
        newName = QString{"%1_%2.%3"}.arg(name).arg(counter).arg(extension);
        ++counter;
        newFileInfo.setFile(this->outDir, newName);
    }
    return newName;
}

