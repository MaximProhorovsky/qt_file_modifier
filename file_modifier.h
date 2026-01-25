#ifndef FILE_MODIFIER_H
#define FILE_MODIFIER_H
#include "fm_main_window.h"
#include "fm_worker.h"

class FileModifier
{
public:
    FileModifier();
    void show();
private:
    MainWindow *mainWindow;
    FileWorker *fileWorker;
};

#endif // FILE_MODIFIER_H
