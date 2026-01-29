#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>

#include <widgets/dir_input_widget.h>


DirInputWidget::DirInputWidget(QWidget *parent, const QString &label, const QString &baseDir)
    : QWidget{parent}, baseDir{baseDir}
{
    QLabel *dirLabel = new QLabel{label, this};

    dirEdit = new QLineEdit{baseDir, this};
    dirEdit->setFixedWidth(200);
    dirEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dirEdit->setReadOnly(true);

    dirBtn = new QPushButton{"Обзор", this};

    QHBoxLayout *layout = new QHBoxLayout{this};
    this->setLayout(layout);
    layout->addWidget(dirLabel, Qt::AlignLeft);
    layout->addWidget(dirEdit);
    layout->addWidget(dirBtn);

    QObject::connect(dirBtn, &QPushButton::clicked, this, &DirInputWidget::onDirBtnCicked);
}

void DirInputWidget::onDirBtnCicked()
{
    QDir dir = QFileDialog::getExistingDirectory(
        this,
        "Выберите папку",
        this->baseDir,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
    this->dirEdit->setText(dir.absolutePath());
    emit dirChanged(dir);
}
