#include <QFileDialog>
#include <QVBoxLayout>

#include "widgets/control_widget.h"
#include "setting.h"

ControlWidget::ControlWidget(QWidget *parent)
    : QWidget{parent}
{

    inDirWidget = new DirInputWidget{this, "Исходные файлы:"};
    outDirWidget = new DirInputWidget{this, "Измененные файлы:"};

    fileMaskWidget = new TextInputWidget{"Введите маску:", new QLineEdit{Setting::BASE_MASK, this}, this};

    QSpinBox *timerSpinBox = new QSpinBox{this};
    timerSpinBox->setRange(0, INT32_MAX);
    timerSpinBox->setSingleStep(100);
    timerSpinBox->setValue(Setting::BASE_TIMEOUT);
    timerWidget = new TextInputWidget{"Периодичность опроса(мс):", timerSpinBox, this};

    QLineEdit *modifierEdit = new QLineEdit{QString::number(Setting::BASE_MODIFIER_VALUE), this};
    modifierEdit->setMaxLength(16);
    QRegularExpressionValidator *modifierValueValidator = new QRegularExpressionValidator{QRegularExpression{"[0-9A-Fa-f]*"}, modifierEdit};
    modifierEdit->setValidator(modifierValueValidator);
    modifierWidget = new TextInputWidget{"Модифицирующее значение:", modifierEdit, this};

    deleteSrcFilesCheckBox = new QCheckBox{"Удалять исходные файлы", this};
    deleteSrcFilesCheckBox->setChecked(Setting::DELETE_SRC_FILES);
    overwriteCheckBox = new QCheckBox{"Заменять повторяющиеся", this};
    overwriteCheckBox->setChecked(Setting::OVERWRITE);
    runWithTimerCheckBox = new QCheckBox{"Запускать по таймеру", this};
    overwriteCheckBox->setChecked(Setting::WITH_TIMER);

    QObject::connect(inDirWidget, &DirInputWidget::dirChanged, this, [&](const QDir &dir){ emit inputDirChanged(dir);});
    QObject::connect(outDirWidget, &DirInputWidget::dirChanged, this, [&](const QDir &dir){ emit outputDirChanged(dir);});
    QObject::connect(fileMaskWidget, &TextInputWidget::textChanged, this, [&](const QString &mask){ emit fileMaskChanged(mask);});
    QObject::connect(timerWidget, &TextInputWidget::textChanged, this, [&](const QString &timeout){ emit timerChanged(timeout.toInt());});
    QObject::connect(modifierWidget, &TextInputWidget::textChanged, this, [&](const QString &value){ emit modifierValueChanged(value.toLongLong(nullptr,16));});
    QObject::connect(overwriteCheckBox, &QCheckBox::checkStateChanged, this, [&](){
        emit overwriteCheckBoxChanged(overwriteCheckBox->checkState());
    });
    QObject::connect(deleteSrcFilesCheckBox, &QCheckBox::checkStateChanged, this, [&](){
        emit deleteInFilesCheckBoxChanged(deleteSrcFilesCheckBox->checkState());
    });
    QObject::connect(runWithTimerCheckBox, &QCheckBox::checkStateChanged, this, [&](){
        emit runWithTimerCheckBoxChanged(runWithTimerCheckBox->checkState());
    });

    QLayout *mainLayout = new QVBoxLayout{this};
    this->setLayout(mainLayout);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(inDirWidget);
    mainLayout->addWidget(outDirWidget);
    mainLayout->addWidget(fileMaskWidget);
    mainLayout->addWidget(modifierWidget);
    mainLayout->addWidget(runWithTimerCheckBox);
    mainLayout->addWidget(timerWidget);
    mainLayout->addWidget(deleteSrcFilesCheckBox);
    mainLayout->addWidget(overwriteCheckBox);
}

