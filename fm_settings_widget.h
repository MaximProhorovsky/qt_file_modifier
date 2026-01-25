#ifndef FM_SETTINGS_WIDGET_H
#define FM_SETTINGS_WIDGET_H

#include <QDir>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = nullptr);

signals:
    void inputDirChanged(const QDir &dir);
    void outputDirChanged(const QDir &dir);
private:
    QLabel *inDirLabel;
    QLabel *outDirLabel;
    QLineEdit *inDirEdit;
    QLineEdit *outDirEdit;
    QPushButton *inDirBtn;
    QPushButton *outDirBtn;
};

#endif // FM_SETTINGS_WIDGET_H
