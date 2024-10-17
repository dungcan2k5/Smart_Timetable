#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->toolButtonConfig, &QPushButton::clicked, this, &MainWindow::onToolButtonConfigClicked);

    // Chỉnh lại kích thước 2 cột tiêu đề dọc và ngang của thời khoá biểu
    ui->tableWidget->horizontalHeader()->setFixedHeight(50);
    ui->tableWidget->verticalHeader()->setFixedWidth(120);
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
        QPropertyAnimation *animation = new QPropertyAnimation(ui->configWindow, "minimumWidth");
        animation->setDuration(500);                                // Thời gian animation (ms)
        animation->setStartValue(ui->configWindow->maximumWidth()); // Giá trị bắt đầu
        animation->setEndValue(0);                                  // Giá trị kết thúc
        animation->setEasingCurve(QEasingCurve::InOutSine);
        animation->start(QAbstractAnimation::DeleteWhenStopped); // Tự động xóa khi kết thúc

        CONFIG_WINDOW_OPEN = false;
    }
    else
    {
        // Tạo animation cho thuộc tính "minimumWidth" của configWindow
        QPropertyAnimation *animation = new QPropertyAnimation(ui->configWindow, "minimumWidth");
        animation->setDuration(500);                              // Thời gian animation (ms)
        animation->setStartValue(0);                              // Giá trị bắt đầu
        animation->setEndValue(ui->configWindow->maximumWidth()); // Giá trị kết thúc
        animation->setEasingCurve(QEasingCurve::InOutSine);
        animation->start(QAbstractAnimation::DeleteWhenStopped); // Tự động xóa khi kết thúc

        CONFIG_WINDOW_OPEN = true;
    }
}
