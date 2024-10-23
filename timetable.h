#ifndef TIMETABLE_H
#define TIMETABLE_H

#endif // TIMETABLE_H

#include <bits/stdc++.h>
#include "json.hpp" // Hỗ trợ JSON cho C++

using namespace std;
using json = nlohmann::json;


/// @brief Thông tin về lịch học
/// @param day Ngày học
/// @param time Giờ học
/// @param room Phòng học
struct Schedule
{
    string day;
    string time;
    string room;
};

/// @brief Thông tin về các lớp học của học phần
/// @param classID Tên lớp
/// @param schedules vector chứa lịch học của lớp
struct ClassInformation
{
    string classId;
    vector<Schedule> schedules;
};

/// @brief Thông tin về học phần
/// @param name Tên môn phần
/// @param code Mã học phần
/// @param classInformation Vector đối tượng `ClassInformation`
struct Subject
{
    string name;
    string code;
    vector<ClassInformation> classInformation;
};

class TimeTable
{
private:
    vector<Subject> subjects;

public:
    void addSubject(Subject &subject);
    vector<Subject> getSubjects();
    // Subject getSubject(string code);
};

/// @brief Đọc JSON từ `filePath`
/// @param filePath Đường dẫn tới file
/// @return Trả về 1 đối tượng `TimeTable`
TimeTable loadJsonFile(const string &filePath);
