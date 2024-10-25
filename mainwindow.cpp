#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QPushButton>
#include <QFont>
#include <QFontDatabase>
#include <QCheckBox>
#include <QVBoxLayout>

vector<int> extractNumbers(const string &rangeStr) {
    std::vector<int> numbers;
    std::istringstream iss(rangeStr);
    int number;
    char arrow;

    while (iss >> number) {
        numbers.push_back(number);
        iss >> arrow; // Đọc và bỏ qua ký tự "->"
    }

    return numbers;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->toolButtonConfig, &QPushButton::clicked, this, &MainWindow::toolButtonConfigClicked);

    // Chỉnh lại kích thước 2 cột tiêu đề dọc và ngang của thời khoá biểu
    ui->tableWidget->horizontalHeader()->setFixedHeight(50);
    ui->tableWidget->verticalHeader()->setFixedWidth(120);

    ui->scrollArea->setVisible(false);

    // Tải dữ liệu thời khoá biểu từ file
    TimeTable timeTable = loadJsonFile("E:/CTDLGT - DSA/BTL_DSA/time.json");

    // Tạo các checkBox môn học
    for (auto &&subject : timeTable.getSubjects())
    {
        QString subjectInfo = QString(
            QString::fromStdString(subject.name) + " (" + QString::fromStdString(subject.code) + ")");

        QCheckBox *checkBoxSubjectInfo = new QCheckBox(subjectInfo, ui->frameAllSchedule);
        checkBoxSubjectInfo->setStyleSheet(QString(
            "color: red;"
            "border: none;"
            "font-weight: bold;"
            "background: none;"));

        checkBoxSubjectInfo->adjustSize();
        int x = (400 - checkBoxSubjectInfo->width()) / 2;
        checkBoxSubjectInfo->move(x, curentCheckBoxY);
        checkBoxSubjectInfo->setMinimumHeight(40);
        // checkBoxSubjectInfo->setAlignment(Qt::AlignCenter);
        curentCheckBoxY = checkBoxSubjectInfo->y() + checkBoxSubjectInfo->height();

        // Căn chỉnh lại kích thước checkBox
        if (curentCheckBoxY > ui->frameAllSchedule->minimumHeight())
            ui->frameAllSchedule->setMinimumHeight(curentCheckBoxY);
        if (checkBoxSubjectInfo->width() > ui->frameAllSchedule->minimumWidth())
            ui->frameAllSchedule->setMinimumWidth(checkBoxSubjectInfo->width() + 10);

        connect(checkBoxSubjectInfo, &QCheckBox::checkStateChanged, this, [this, subject](int state)
                { this->checkBoxStateChanged(state, subject, vector<Schedule>(), "", ""); });

        // Tạo checkBox các lớp của môn học
        for (auto &&classInfo : subject.classInformation)
        {
            QString classInfoText = QString::fromStdString(classInfo.classId + " (");
            for (auto &&schedule : classInfo.schedules)
            {
                if (classInfoText[classInfoText.size() - 1] == ']')
                    classInfoText += ", ";
                classInfoText += schedule.day + " [" + schedule.time + "]";
            }
            classInfoText += ")";

            QCheckBox *checkBoxClass = new QCheckBox(classInfoText, ui->frameAllSchedule);
            checkBoxClass->setStyleSheet(QString(
                "color: #000;"
                "border: none;"
                "background: none;"));

            // Add the checkable label to the layout
            // classCheckBox->setGeometry(0, curentY, ui->frameAllSchedule->width(), 40);
            checkBoxClass->adjustSize();
            checkBoxClass->move(0, curentCheckBoxY);
            checkBoxClass->setMinimumHeight(40);
            // classCheckBox->setAlignment(Qt::AlignCenter);
            curentCheckBoxY = checkBoxClass->y() + checkBoxClass->height();
            if (curentCheckBoxY > ui->frameAllSchedule->minimumHeight())
                ui->frameAllSchedule->setMinimumHeight(curentCheckBoxY);
            if (checkBoxClass->width() > ui->frameAllSchedule->minimumWidth())
                ui->frameAllSchedule->setMinimumWidth(checkBoxClass->width() + 10);

            connect(checkBoxSubjectInfo, &QCheckBox::checkStateChanged, this, [this, schedules = classInfo.schedules, classId = classInfo.classId, subjectName = subject.name](int state)
                    { this->checkBoxStateChanged(state, Subject(), schedules, classId, subjectName); });
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkAvailable(const Subject &subject)
{
    bool vaild = false;
    for (auto &&classInfo : subject.classInformation)
        for (auto &&schedule : classInfo.schedules)
        {
            vector<int> _time = extractNumbers(schedule.time);
            for (int i = _time[0]; i < _time[1]; i++)
            {
                if (c[day_index->find(schedule.day)][i] == 1)
                {
                    vaild = false;
                    break;
                }
            }
            vaild = true;
            return vaild;
        }
    return vaild;
}

void MainWindow::showTimeTable()
{
    return;
}

void MainWindow::checkBoxStateChanged(int state, const Subject &subject = Subject(), const vector<Schedule> &schedule = vector<Schedule>(), const string &classId = "", const string &subjectName = "")
{
    if (state == Qt::Checked)
    {
        if (classId == "")
            checkBoxChecked(subject);
        else
            checkBoxChecked(schedule, classId, subjectName);
    }
    else
    {
        for (int i = 0; i < selectedSubject.size(); i++)
            if (selectedSubject[i].name == subject.name)
            {
                selectedSubject.erase(selectedSubject.begin() + i);
                return;
            }
    }
}

void MainWindow::checkBoxChecked(const Subject &subject)
{
    for (int i = 0; i < selectedSubject.size(); i++)
        if (selectedSubject[i].name == subject.name)
        {
            if (checkAvailable(subject))
            {
                selectedSubject[i] = subject;
                showTimeTable();
            }
            return;
        }
    if (checkAvailable(subject))
    {
        selectedSubject.push_back(subject);
        showTimeTable();
    }
}

void MainWindow::checkBoxChecked(const vector<Schedule> &schedule, const string &classId, const string &subjectName)
{
    for (int i = 0; i < selectedSubject.size(); i++)
        if (selectedSubject[i].name == subjectName)
        {
            for (int j = 0; j < selectedSubject[i].classInformation.size(); j++)
                if (selectedSubject[i].classInformation[j].classId == classId)
                    return;
            ClassInformation newClass = ClassInformation();
            newClass.classId = classId;
            newClass.schedules = schedule;
            selectedSubject[i].classInformation.push_back(newClass);
            return;
        }
    ClassInformation newClass = ClassInformation();
    newClass.classId = classId;
    newClass.schedules = schedule;
    Subject newSubject = Subject();
    newSubject.name = subjectName;
    newSubject.code = classId;
    newSubject.classInformation.push_back(newClass);

    if (checkAvailable(newSubject))
    {
        selectedSubject.push_back(newSubject);
        // showTimeTable();
    }
}

void MainWindow::toolButtonConfigClicked()
{
    if (CONFIG_WINDOW_OPEN == true)
    {
        // Tạo animation cho thuộc tính "minimumWidth" của configWindow
        QPropertyAnimation *animation = new QPropertyAnimation(ui->configWindow, "minimumWidth");
        animation->setDuration(500);                                // Thời gian animation (ms)
        animation->setStartValue(ui->configWindow->maximumWidth()); // Giá trị bắt đầu
        animation->setEndValue(0);                                  // Giá trị kết thúc
        animation->setEasingCurve(QEasingCurve::InOutSine);

        // Kết nối tín hiệu finished của animation với một slot tùy chỉnh
        connect(animation, &QPropertyAnimation::finished, this, [=]()
                { 
            ui->frameConfig->setStyleSheet("border: none;"); 
            CONFIG_WINDOW_OPEN = false; 
            ui->configWindow->setMinimumWidth(0); });

        animation->start(QAbstractAnimation::DeleteWhenStopped); // Tự động xóa khi kết thúc
        ui->scrollArea->setVisible(false);
    }
    else
    {
        // Tạo animation cho thuộc tính "minimumWidth" của configWindow
        QPropertyAnimation *animation = new QPropertyAnimation(ui->configWindow, "minimumWidth");
        animation->setDuration(500);                              // Thời gian animation (ms)
        animation->setStartValue(0);                              // Giá trị bắt đầu
        animation->setEndValue(ui->configWindow->maximumWidth()); // Giá trị kết thúc
        animation->setEasingCurve(QEasingCurve::InOutSine);

        // Kết nối tín hiệu finished của animation với một slot tùy chỉnh
        connect(animation, &QPropertyAnimation::finished, this, [=]()
                {
            CONFIG_WINDOW_OPEN = true;
            ui->scrollArea->setVisible(true); 
            ui->configWindow->setMinimumWidth(ui->configWindow->maximumWidth()); });

        animation->start(QAbstractAnimation::DeleteWhenStopped); // Tự động xóa khi kết thúc
        ui->frameConfig->setStyleSheet("");
    }
}
