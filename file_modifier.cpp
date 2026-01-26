#include "file_modifier.h"


#include <QListWidget>
#include <QStandardItemModel>
#include <QTableView>

FileModifier::FileModifier(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout{this};

    controlWidget = new ControlWidget{this};
    processWidget = new ProcessWidget{this};
    fileWorker = new FileWorker{this};

    this->setLayout(mainLayout);
    mainLayout->addWidget(controlWidget);
    mainLayout->addWidget(processWidget);
    QObject::connect(processWidget, &ProcessWidget::scanButtonClicked, fileWorker, &FileWorker::onScanButtonClicked);
    QObject::connect(fileWorker, &FileWorker::filesScanned, processWidget, &ProcessWidget::onDirScanned);
}
