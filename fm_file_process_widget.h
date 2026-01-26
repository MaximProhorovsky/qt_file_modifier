#ifndef FM_FILE_PROCESS_WIDGET_H
#define FM_FILE_PROCESS_WIDGET_H

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
public slots:
    void onFileProcessed();
    void onAllFilesProcessed();
    void onDirScanned(const QFileInfoList &files);
private:
    QTableView *filesTable;
    QStandardItemModel *filesModel;
    QLabel *filesCountLabel;
    QPushButton *scanBtn;
    QPushButton *actionBtn;
    bool scanned = false;
};

#endif // FM_FILE_PROCESS_WIDGET_H
