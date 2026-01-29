#ifndef DIR_INPUT_WIDGET_H
#define DIR_INPUT_WIDGET_H

#include <QDir>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class DirInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DirInputWidget(QWidget *parent = nullptr,
                            const QString &label = "Выбор директории:",
                            const QString &baseDir = "C:/");
signals:
    void dirChanged(const QDir &dir);
private slots:
    void onDirBtnCicked();
private:
    QString baseDir;
    QLineEdit *dirEdit;
    QPushButton *dirBtn;
};

#endif // DIR_INPUT_WIDGET_H
