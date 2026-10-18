#include <vector>

struct Course {
    std::string code;
    std::string name;
    int facultId;
    int sectionId;
    int students;
    int lecturePerWeek;
    bool requiresLab;
};

struct Faculty {
    int id;
    std::string name;
    std::vector<int> availableSlots;
};

struct Room {
    int id;
    std::string name;
    int capacity;
    bool isLab;
};

struct Section {
    int id;
    std::string name;
    int studentCount;
};

struct TimeSlot {
    int id;
    std::string day;
    int startHour; 
    int endHour;
};

struct TimetableEntry {
    int courseId;
    int facultyId;
    int sectionId;
    int roomId;
    int slotId;
};
