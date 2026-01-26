#include "file_modifier.h"

#include <QFile>
#include <QDir>
#include <QString>
#include <QCoreApplication>
#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FileModifier fileModifier{};
    fileModifier.show();

    // QDir fileDir{""};
    // QDir resultDir{"C:/Users/maksi/qtSource/qt_file_modifier/results/"};
    // FileWorker fileprocessor{};
    // fileprocessor.processFiles(fileDir, resultDir, "*.txt", 1627712721LL);

    return app.exec();
}
