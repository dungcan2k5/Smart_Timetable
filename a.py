import json

with open("time.txt", "r", encoding="utf-8") as f:
    data = f.read()

# Khởi tạo một dictionary để lưu kết quả
result = {}

# Chia dữ liệu thành các dòng
lines = data.strip().split('\n')

# Biến tạm để lưu tên môn học và mã môn học hiện tại
current_course_name = ""
current_course_code = ""

for line in lines:
    # Nếu dòng chứa thông tin tên và mã môn học
    if not line[0].isdigit():
        current_course_name, current_course_code = line.split(' (')
        current_course_code = current_course_code.rstrip(')')
        result[current_course_name] = {
            "code": current_course_code,
            "class_information": []
        }
    else:
        parts = line.split(';')
        class_id = parts[0]
        schedule = []

        for i in range(1, len(parts), 3):
            day, time, room = parts[i], parts[i + 1], parts[i + 2]
            schedule.append({
                "day": day,
                "time": time,
                "room": room
            })

        result[current_course_name]["class_information"].append({
            "class_id": class_id,
            "schedule": schedule
        })

# json_result = json.dumps(result, indent=4, ensure_ascii=False)
with open("time.json", "w", encoding="utf-8") as f:
    json.dump(result, f, indent=4, ensure_ascii=False)