#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QHBoxLayout>
#include <QWidget>

#include <widgets/process_widget.h>

#include "widgets/control_widget.h"
#include "file_worker.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private:
    ControlWidget *controlWidget;
    ProcessWidget *processWidget;
    FileWorker *fileWorker;
};

#endif // MAIN_WINDOW_H
