#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timetable.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool checkAvailable(const Subject &subject);
    void showTimeTable();

private slots:
    void toolButtonConfigClicked();
    void checkBoxStateChanged(int state, const Subject &subject, const vector<Schedule> &schedule, const string &classId, const string &subjectName);
    void checkBoxChecked(const Subject &subject);
    void checkBoxChecked(const vector<Schedule> &schedule, const string &classId, const string &subjectName);
private:
    Ui::MainWindow *ui;
    bool CONFIG_WINDOW_OPEN = false; // Trạng thái mở của cửa sổ config
    int curentCheckBoxY = 0; // Toạ độ `y` hiện tại của các checkBox
    vector<Subject> selectedSubject;
    int c[12][7] = {0};
    string day_index[7] = {u8"Thứ Hai", u8"Thứ Ba", u8"Thứ Tư", u8"Thứ Năm", u8"Thứ Sáu", u8"Thứ Bảy", u8"Chủ Nhật"};
};
#endif // MAINWINDOW_H
