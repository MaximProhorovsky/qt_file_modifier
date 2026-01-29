#ifndef TEXT_INPUT_WIDGET_H
#define TEXT_INPUT_WIDGET_H

#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class TextInputWidget : public QWidget
{
    Q_OBJECT
protected:
    TextInputWidget(const QString &label, QWidget *inputWidget, QWidget *parent = nullptr);
public:
    explicit TextInputWidget(const QString &label, QLineEdit *inputWidget, QWidget *parent = nullptr);
    explicit TextInputWidget(const QString &label, QSpinBox *inputWidget, QWidget *parent = nullptr);

signals:
    void textChanged(const QString &text);
private slots:
    void onEditBtnClicked();
private:
    bool isEditingEnabled = false;
    QWidget *inputWidget;
    QPushButton *editBtn;
};

#endif // TEXT_INPUT_WIDGET_H
