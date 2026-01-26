#ifndef FM_CONTROL_WIDGET_H
#define FM_CONTROL_WIDGET_H

#include <QCheckBox>
#include <QComboBox>
#include <QDir>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = nullptr);

signals:
    void inputDirChanged(const QDir &dir);
    void outputDirChanged(const QDir &dir);
    void maskChanged(const QString &mask);
    void removeCheckBoxChanged(bool value);
    void replaceCheckBoxChanged(bool value);
    void modifierValueBoxChanged(bool value);
private slots:
    void onMaskBtnClicked();
    void onInDirBtnCicked();
    void onOutDirBtnCicked();
private:
    QLineEdit *inDirEdit;
    QLineEdit *outDirEdit;
    QLineEdit *fileMaskEdit;
    QPushButton *inDirBtn;
    QPushButton *outDirBtn;
    QPushButton *fileMaskBtn;
    QCheckBox *removeInputCheckBox;
    QCheckBox *replaceCheckBox;
    QSpinBox *modifierValueBox;
    bool maskChanging = false;
};

#endif // FM_CONTROL_WIDGET_H
