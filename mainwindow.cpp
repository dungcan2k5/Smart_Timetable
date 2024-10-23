#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timetable.h"
#include <QPropertyAnimation>
#include <QPushButton>
#include <QFont>
#include <QFontDatabase>
#include <QCheckBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QLabel *labelSubjectInfo = new QLabel(ui->frameConfig);

    connect(ui->toolButtonConfig, &QPushButton::clicked, this, &MainWindow::onToolButtonConfigClicked);

    // Chỉnh lại kích thước 2 cột tiêu đề dọc và ngang của thời khoá biểu
    ui->tableWidget->horizontalHeader()->setFixedHeight(50);
    ui->tableWidget->verticalHeader()->setFixedWidth(120);

    // Load timetable from JSON file
    TimeTable timeTable = loadJsonFile("E:\\CTDLGT - DSA\\BTL_DSA\\time.json");

    int curentY = 0;

    // Iterate through subjects and display information
    // for (auto &&subject : timeTable.getSubjects())
    // {
    //     // Create a checkable label for subject information
    //     QString subjectInfo = QString(
    //     "<span style=\"color: red; font-weight: bold; text-transform: uppercase;\">"
    //     + QString::fromStdString(subject.name) + " (" + QString::fromStdString(subject.code) + ")</span>");

    //     QLabel *labelSubjectInfo = new QLabel("Chào các cậu", ui->frameConfig);
    //     labelSubjectInfo->setStyleSheet(QString(
    //         "color: red;"
    //         "border: none;"
    //         "font-weight: bold;"
    //         "background: none;"
    //         ));

    //     // Add the checkable label to the layout
    //     labelSubjectInfo->setGeometry(0, curentY, 360, 40);
    //     labelSubjectInfo->setAlignment(Qt::AlignCenter);
    //     curentY += 40;

    //     // // Add classInformation checkboxes
    //     // for (auto &&classInfo : subject.classInformation)
    //     // {
    //     //     // QString classInfoText = QString("<font color='gray'><i>%1</i></font>").arg(classInfo.c_str());
    //     //     QString classInfoText = QString("Chào cậu nhé");
    //     //     QCheckBox *classCheckBox = new QCheckBox(classInfoText);
    //     //     classCheckBox->setStyleSheet("QCheckBox::indicator { width: 15px; height: 15px; }"); // Adjust checkbox size

    //     //     // Add the class checkbox to the layout
    //     //     layout->addWidget(classCheckBox);
    //     // }
    // }
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
        ui->frameConfig->setStyleSheet("border: none;");

        CONFIG_WINDOW_OPEN = false;
        ui->scrollArea->setMaximumSize(0, ui->scrollArea->height());

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
        ui->frameConfig->setStyleSheet("");

        CONFIG_WINDOW_OPEN = true;
        ui->scrollArea->setMaximumSize(360, ui->scrollArea->height());
    }
}
