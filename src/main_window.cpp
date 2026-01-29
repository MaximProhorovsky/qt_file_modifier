#include <QListWidget>
#include <QStandardItemModel>
#include <QTableView>

#include <main_window.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    controlWidget = new ControlWidget{this};
    processWidget = new ProcessWidget{this};
    fileWorker = new FileWorker{this};
    this->setMaximumHeight(500);
    this->setMaximumWidth(1000);
    this->setMinimumHeight(500);
    this->setMinimumWidth(1000);

    QHBoxLayout *mainLayout = new QHBoxLayout{this};
    this->setLayout(mainLayout);
    mainLayout->addWidget(controlWidget, Qt::AlignTop);
    mainLayout->addWidget(processWidget, Qt::AlignTop);

    QObject::connect(processWidget, &ProcessWidget::scanButtonClicked, fileWorker, &FileWorker::onScanButtonClicked);
    QObject::connect(processWidget, &ProcessWidget::actionButtonClicked, fileWorker, &FileWorker::onProcessingRequested);
    QObject::connect(fileWorker, &FileWorker::filesScanned, processWidget, &ProcessWidget::onDirScanned);
    QObject::connect(controlWidget, &ControlWidget::inputDirChanged, fileWorker, &FileWorker::onInDirChanged);
    QObject::connect(controlWidget, &ControlWidget::outputDirChanged, fileWorker, &FileWorker::onOutDirChanged);
    QObject::connect(controlWidget, &ControlWidget::overwriteCheckBoxChanged, fileWorker, &FileWorker::onOverwriteChanged);
    QObject::connect(controlWidget, &ControlWidget::deleteInFilesCheckBoxChanged, fileWorker, &FileWorker::onDeleteSrcFilesChanged);
    QObject::connect(controlWidget, &ControlWidget::fileMaskChanged, fileWorker, &FileWorker::onFileMaskChanged);
    QObject::connect(controlWidget, &ControlWidget::modifierValueChanged, fileWorker, &FileWorker::onModifierValueChanged);
    QObject::connect(fileWorker, &FileWorker::fileProcessingStarted, processWidget, &ProcessWidget::onFileProcessingStarted);
    QObject::connect(fileWorker, &FileWorker::allFilesProcessed, processWidget, &ProcessWidget::onAllFilesProcessed);
    QObject::connect(controlWidget, &ControlWidget::timerChanged, fileWorker, &FileWorker::onTimerChanged);
    QObject::connect(fileWorker, &FileWorker::fileProcessed, processWidget, &ProcessWidget::onFileProcessed);
    QObject::connect(controlWidget, &ControlWidget::runWithTimerCheckBoxChanged, fileWorker, &FileWorker::onRunWithTimerChanged);
    QObject::connect(controlWidget, &ControlWidget::runWithTimerCheckBoxChanged, processWidget, &ProcessWidget::onRunWithTimerChanged);
}
