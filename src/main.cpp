#include <QApplication>

#include <main_window.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QThreadPool::globalInstance()->setMaxThreadCount(Setting::THREAD_COUNT);
    MainWindow fileModifier;
    fileModifier.show();
    return app.exec();
}
