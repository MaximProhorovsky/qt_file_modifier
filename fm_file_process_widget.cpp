#include "fm_file_process_widget.h"

#include <QFileInfoList>
#include <QHBoxLayout>
#include <QStandardItemModel>

ProcessWidget::ProcessWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    QWidget *controlWidget = new QWidget{this};
    QHBoxLayout *controlLayout = new QHBoxLayout{controlWidget};
    filesTable = new QTableView{this};
    filesModel = new QStandardItemModel();
    filesModel->setHorizontalHeaderLabels({"File name", "Status"});
    filesTable->setModel(filesModel);

    filesCountLabel = new QLabel{"Обработано файлов: 0/0"};
    scanBtn = new QPushButton{"Сканировать", controlWidget};
    actionBtn = new QPushButton{"Обработать", controlWidget};
    this->setLayout(mainLayout);
    controlWidget->setLayout(controlLayout);
    controlLayout->addWidget(scanBtn);
    controlLayout->addWidget(actionBtn);
    controlLayout->addWidget(filesCountLabel);
    mainLayout->addWidget(filesTable);
    mainLayout->addWidget(controlWidget);

    QObject::connect(scanBtn, &QPushButton::clicked, this, [&](){emit scanButtonClicked();});
}

void ProcessWidget::onFileProcessed()
{

}

void ProcessWidget::onAllFilesProcessed()
{

}

void ProcessWidget::onDirScanned(const QFileInfoList &files)
{
    filesModel->clear();
    for(QFileInfo info : files){
        QList<QStandardItem*> row;
        row << new QStandardItem{info.fileName()};
        row << new QStandardItem{"unprocessed"};
        filesModel->appendRow(row);
    }
    filesCountLabel->setText(QString{"Обработано файлов: 0/%1"}.arg(files.size()));
}

