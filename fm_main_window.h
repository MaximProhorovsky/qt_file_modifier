#ifndef FM_MAIN_WINDOW_H
#define FM_MAIN_WINDOW_H

#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addWidgetToLeftLayout(QWidget *widget);
    void addWidgetToRightLayout(QWidget *widget);
signals:

private:
    QHBoxLayout *centralLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
};

#endif // FM_MAIN_WINDOW_H
