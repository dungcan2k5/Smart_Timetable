#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->toolButtonConfig, &QPushButton::clicked, this, &MainWindow::onToolButtonConfigClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onToolButtonConfigClicked()
{
    if (CONFIG_WINDOW_OPEN == true)
    {
        // Tạo animation cho thuộc tính "minimumWidth" của configWindow
        QPropertyAnimation *animation1 = new QPropertyAnimation(ui->configWindow, "minimumWidth");
        animation1->setDuration(1000);                               // Thời gian animation (ms)
        animation1->setStartValue(ui->configWindow->maximumWidth()); // Giá trị bắt đầu
        animation1->setEndValue(0);                                  // Giá trị kết thúc
        animation1->setEasingCurve(QEasingCurve::InOutQuart);
        animation1->start(QAbstractAnimation::DeleteWhenStopped); // Tự động xóa khi kết thúc

        CONFIG_WINDOW_OPEN = false;
    }
    else
    {
        // Tạo animation cho thuộc tính "minimumWidth" của configWindow
        QPropertyAnimation *animation1 = new QPropertyAnimation(ui->configWindow, "minimumWidth");
        animation1->setDuration(1000);                               // Thời gian animation (ms)
        animation1->setStartValue(0); // Giá trị bắt đầu
        animation1->setEndValue(ui->configWindow->maximumWidth());                                  // Giá trị kết thúc
        animation1->setEasingCurve(QEasingCurve::InOutQuart);
        animation1->start(QAbstractAnimation::DeleteWhenStopped); // Tự động xóa khi kết thúc

        CONFIG_WINDOW_OPEN = true;
    }
}
