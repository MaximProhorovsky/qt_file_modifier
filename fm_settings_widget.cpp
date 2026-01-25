#include "fm_settings_widget.h"

#include <QFileDialog>
#include <QVBoxLayout>

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setLayout(new QVBoxLayout{this});
    QWidget *inDirWidget = new QWidget{this};
    QWidget *outDirWidget = new QWidget{this};
    this->layout()->addWidget(inDirWidget);
    this->layout()->addWidget(outDirWidget);
    inDirWidget->setLayout(new QHBoxLayout{inDirWidget});
    outDirWidget->setLayout(new QHBoxLayout{outDirWidget});
    QLayout *inLayout = inDirWidget->layout();
    QLayout *outLayout = outDirWidget->layout();
    this->inDirLabel = new QLabel("Исходные файлы:", this);
    this->outDirLabel = new QLabel("Измененные файлы:", this);
    this->inDirEdit = new QLineEdit(this);
    this->outDirEdit = new QLineEdit(this);
    inDirEdit->setReadOnly(true);
    outDirEdit->setReadOnly(true);
    this->inDirBtn = new QPushButton{"Обзор", this};
    this->outDirBtn = new QPushButton{"Обзор", this};

    QObject::connect(inDirBtn, &QPushButton::clicked, [&](){
        QDir dir = QFileDialog::getExistingDirectory(
            this,
            "Выберите папку для входых файлов",
            "C:/",
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
        this->inDirEdit->setText(dir.absolutePath());
        emit inputDirChanged(dir);
    });
    QObject::connect(outDirBtn, &QPushButton::clicked, [&](){
        QDir dir = QFileDialog::getExistingDirectory(
            this,
            "Выберите папку для выходных файлов",
            "C:/",
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
            );
        this->outDirEdit->setText(dir.absolutePath());
        emit outputDirChanged(dir);
    });
    inLayout->addWidget(inDirLabel);
    inLayout->addWidget(inDirEdit);
    inLayout->addWidget(inDirBtn);
    outLayout->addWidget(outDirLabel);
    outLayout->addWidget(outDirEdit);
    outLayout->addWidget(outDirBtn);
}
