#include <QHBoxLayout>
#include <QLabel>

#include <widgets/text_input_widget.h>

TextInputWidget::TextInputWidget(const QString &label, QWidget *inputWidget, QWidget *parent)
    : QWidget{parent}
{
    this->inputWidget = inputWidget;
    QLabel *textLabel = new QLabel{label, this};
    this->inputWidget->setFixedWidth(200);
    this->inputWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->inputWidget->setEnabled(false);
    editBtn = new QPushButton{"Изменить", this};

    QHBoxLayout *layout = new QHBoxLayout{this};
    this->setLayout(layout);
    layout->addWidget(textLabel, Qt::AlignLeft);
    layout->addWidget(this->inputWidget);
    layout->addWidget(editBtn);

    QObject::connect(editBtn, &QPushButton::clicked, this, &TextInputWidget::onEditBtnClicked);
}

TextInputWidget::TextInputWidget(const QString &label, QLineEdit *inputWidget, QWidget *parent)
    : TextInputWidget{label, static_cast<QWidget*>(inputWidget), parent}
{}

TextInputWidget::TextInputWidget(const QString &label, QSpinBox *inputWidget, QWidget *parent)
    : TextInputWidget{label, static_cast<QWidget*>(inputWidget), parent}
{}

void TextInputWidget::onEditBtnClicked()
{
    if(isEditingEnabled){
        inputWidget->setEnabled(false);
        editBtn->setText("Изменить");
        QString text;
        if(QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(inputWidget)){
            text = lineEdit->text();
        }else if (QSpinBox *spinBox = dynamic_cast<QSpinBox*>(inputWidget)){
            text = QString::number(spinBox->value());
        }
        emit textChanged(text);
    }else{
        inputWidget->setEnabled(true);
        editBtn->setText("Сохранить");
    }
    isEditingEnabled = !isEditingEnabled;
}

