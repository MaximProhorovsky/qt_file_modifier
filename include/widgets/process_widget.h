#ifndef FILE_PROCESS_WIDGET_H
#define FILE_PROCESS_WIDGET_H

#include "setting.h"
#include <QFileInfoList>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

class ProcessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessWidget(QWidget *parent = nullptr);

signals:
    void scanButtonClicked();
    void actionButtonClicked();
public slots:
    void onFileProcessingStarted();
    void onFileProcessed(const QString &fileName, bool isSucess);
    void onAllFilesProcessed();
    void onDirScanned(const QFileInfoList &files);
    void onRunWithTimerChanged(bool value);
private:
    QTableView *filesTable;
    QStandardItemModel *filesModel;
    QLabel *filesCountLabel;
    QPushButton *scanBtn;
    QPushButton *actionBtn;
    QAtomicInteger<qsizetype> filesProcessed{0};
    qsizetype totalFiles;
    bool runWithTimer = Setting::WITH_TIMER;
};

#endif // FILE_PROCESS_WIDGET_H
