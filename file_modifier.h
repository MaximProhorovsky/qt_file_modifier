#ifndef FILE_MODIFIER_H
#define FILE_MODIFIER_H
#include "fm_control_widget.h"
#include "fm_file_process_widget.h"
#include "fm_worker.h"

#include <QHBoxLayout>
#include <QWidget>

class FileModifier : public QWidget
{
    Q_OBJECT
public:
    FileModifier(QWidget *parent = nullptr);

private:
    ControlWidget *controlWidget;
    ProcessWidget *processWidget;
    FileWorker *fileWorker;
};

#endif // FILE_MODIFIER_H
