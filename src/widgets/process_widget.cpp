#include <QCoreApplication>
#include <QFileInfoList>
#include <QHBoxLayout>
#include <QStandardItemModel>

#include <widgets/process_widget.h>

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
    QObject::connect(actionBtn, &QPushButton::clicked, this, [&](){emit actionButtonClicked();});
}

void ProcessWidget::onFileProcessingStarted()
{
    scanBtn->setEnabled(false);
    actionBtn->setEnabled(false);    
}

void ProcessWidget::onFileProcessed(const QString &fileName, bool isSucess)
{
    ++filesProcessed;
    for(int row = 0; row < filesModel->rowCount(); ++row){
        QStandardItem *item = filesModel->item(row, 0);
        if(item && item->text() == fileName){
            filesModel->item(row, 1)->setText(isSucess ? "success" : "error");
            break;
        }
    }
    QString label = QString("Обработано файлов: %1/%2")
                        .arg(QString::number(filesProcessed.loadRelaxed()),
                             QString::number(totalFiles));
    filesCountLabel->setText(label);
}

void ProcessWidget::onAllFilesProcessed()
{
    scanBtn->setEnabled(true);
    actionBtn->setEnabled(!runWithTimer);
}

void ProcessWidget::onDirScanned(const QFileInfoList &files)
{
    filesModel->clear();
    filesModel->setHorizontalHeaderLabels({"File name", "Status"});
    for(const QFileInfo &info : std::as_const(files)){
        QList<QStandardItem*> row;
        row << new QStandardItem{info.fileName()};
        row << new QStandardItem{"unprocessed"};
        filesModel->appendRow(row);
    }
    filesProcessed.fetchAndStoreAcquire(0);
    totalFiles = files.size();
    filesCountLabel->setText(QString{"Обработано файлов: 0/%1"}.arg(files.size()));
}

void ProcessWidget::onRunWithTimerChanged(bool value)
{
    runWithTimer = value;
    if(scanBtn->isEnabled()) actionBtn->setEnabled(!value);
}

