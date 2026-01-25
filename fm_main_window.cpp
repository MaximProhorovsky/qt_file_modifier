#include "fm_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    this->centralLayout = new QHBoxLayout{this};
    QWidget *leftContainer = new QWidget{this};
    QWidget *rightContainer = new QWidget{this};
    this->leftLayout = new QVBoxLayout{leftContainer};
    this->rightLayout = new QVBoxLayout{rightContainer};
    leftContainer->setLayout(leftLayout);
    rightContainer->setLayout(rightLayout);
    centralLayout->addWidget(leftContainer);
    centralLayout->addWidget(rightContainer);
}

void MainWindow::addWidgetToRightLayout(QWidget *widget)
{
    rightLayout->addWidget(widget);
}

void MainWindow::addWidgetToLeftLayout(QWidget *widget)
{
    leftLayout->addWidget(widget);
}
