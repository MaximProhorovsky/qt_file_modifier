#include "fm_control_widget.h"

#include <QFileDialog>
#include <QVBoxLayout>

ControlWidget::ControlWidget(QWidget *parent)
    : QWidget{parent}
{
    QWidget *inputWidget = new QWidget{this};

    QLabel *inDirLabel = new QLabel("Исходные файлы:", inputWidget);
    QLabel *outDirLabel = new QLabel("Измененные файлы:", inputWidget);

    inDirEdit = new QLineEdit("C:/", inputWidget);
    inDirEdit->setFixedWidth(200);
    inDirEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    inDirEdit->setReadOnly(true);

    outDirEdit = new QLineEdit("C:/", inputWidget);
    outDirEdit->setFixedWidth(200);
    outDirEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    outDirEdit->setReadOnly(true);

    inDirBtn = new QPushButton{"Обзор", this};
    outDirBtn = new QPushButton{"Обзор", this};

    QLabel *maskLabel = new QLabel{"Маска входных файлов:", inputWidget};
    fileMaskEdit = new QLineEdit("*.txt", inputWidget);
    fileMaskEdit->setFixedWidth(200);
    fileMaskEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    fileMaskEdit->setEnabled(false);

    fileMaskBtn = new QPushButton{"Изменить", inputWidget};

    removeInputCheckBox = new QCheckBox("Удалять исходные файлы", this);
    replaceCheckBox = new QCheckBox("Заменять повторяющиеся", this);

    QObject::connect(fileMaskBtn, &QPushButton::clicked, this, &ControlWidget::onMaskBtnClicked);
    QObject::connect(inDirBtn, &QPushButton::clicked, this, &ControlWidget::onInDirBtnCicked);
    QObject::connect(outDirBtn, &QPushButton::clicked, this, &ControlWidget::onOutDirBtnCicked);

    QGridLayout *inputLayout = new QGridLayout{inputWidget};

    inputWidget->setLayout(inputLayout);
    inputLayout->addWidget(inDirLabel, 1, 0, Qt::AlignLeft);
    inputLayout->addWidget(inDirEdit, 1, 1);
    inputLayout->addWidget(inDirBtn, 1, 2);
    inputLayout->addWidget(outDirLabel, 2, 0, Qt::AlignLeft);
    inputLayout->addWidget(outDirEdit, 2, 1);
    inputLayout->addWidget(outDirBtn, 2, 2);

    inputLayout->addWidget(maskLabel);
    inputLayout->addWidget(fileMaskEdit);
    inputLayout->addWidget(fileMaskBtn);

    QLayout *mainLayout = new QVBoxLayout{this};
    this->setLayout(mainLayout);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->addWidget(inputWidget);
    mainLayout->addWidget(removeInputCheckBox);
    mainLayout->addWidget(replaceCheckBox);
}

void ControlWidget::onMaskBtnClicked()
{
    if(maskChanging){
        fileMaskEdit->setEnabled(false);
        fileMaskBtn->setText("Изменить");
        emit maskChanged(fileMaskEdit->text());
    }else{
        fileMaskEdit->setEnabled(true);
        fileMaskBtn->setText("Сохранить");
    }
    maskChanging = !maskChanging;
}

void ControlWidget::onInDirBtnCicked()
{
    QDir dir = QFileDialog::getExistingDirectory(
        this,
        "Выберите папку для выходных файлов",
        "C:/",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
    this->inDirEdit->setText(dir.absolutePath());
    emit inputDirChanged(dir);
}

void ControlWidget::onOutDirBtnCicked()
{
    QDir dir = QFileDialog::getExistingDirectory(
        this,
        "Выберите папку для выходных файлов",
        "C:/",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
    this->outDirEdit->setText(dir.absolutePath());
    emit outputDirChanged(dir);
}
