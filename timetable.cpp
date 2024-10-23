#include "timetable.h"

void TimeTable::addSubject(Subject &subject)
{
    subjects.push_back(subject);
}

vector<Subject> TimeTable::getSubjects()
{
    return subjects;
}

TimeTable loadJsonFile(const string &filePath)
{
    TimeTable timeTable;

    ifstream jsonFile(filePath);
    json j = json::parse(jsonFile);
    // cout << j << endl;

    // Lặp qua từng học phần
    for (const auto &subjectJson : j.items())
    {
        Subject subject;
        // Lấy tên học phần
        subject.name = subjectJson.key();
        // Lấy mã học phần
        subject.code = subjectJson.value()["code"];
        // Lấy thông tin các lớp của học phần
        json classesInformation = subjectJson.value()["class_information"];

        // Lặp qua từng lớp của học phần
        for (const json &classInformation : classesInformation)
        {
            ClassInformation classInfo;
            // Lấy tên lớp
            classInfo.classId = classInformation["class_id"];
            // Lặp qua từng lịch học của lớp
            for (const json &scheduleJson : classInformation["schedule"])
            {
                Schedule schedule;
                // Lấy ngày, thời gian, và phòng học
                schedule.day = scheduleJson["day"];
                schedule.time = scheduleJson["time"];
                schedule.room = scheduleJson["room"];
                // Thêm lịch học vào lớp
                classInfo.schedules.push_back(schedule);
            }
            // Thêm lớp vào học phần
            subject.classInformation.push_back(classInfo);
        }
        timeTable.addSubject(subject);
    }
    return timeTable;
}
