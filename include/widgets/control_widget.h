#ifndef CONTROL_WIDGET_H
#define CONTROL_WIDGET_H

#include "dir_input_widget.h"
#include "text_input_widget.h"
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
    void fileMaskChanged(const QString &mask);
    void modifierValueChanged(qint64 value);
    void deleteInFilesCheckBoxChanged(bool value);
    void overwriteCheckBoxChanged(bool value);
    void runWithTimerCheckBoxChanged(bool value);
    void timerChanged(qint32 timeout);
private:
    DirInputWidget *inDirWidget;
    DirInputWidget *outDirWidget;
    TextInputWidget *fileMaskWidget;
    TextInputWidget *modifierWidget;
    TextInputWidget *timerWidget;
    QCheckBox *runWithTimerCheckBox;
    QCheckBox *deleteSrcFilesCheckBox;
    QCheckBox *overwriteCheckBox;
};

#endif // CONTROL_WIDGET_H
