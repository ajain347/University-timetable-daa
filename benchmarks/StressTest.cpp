
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

#include "models/UniversityModels.h"
#include "timetable/TimetableAllocator.h"
#include "timetable/TimetableValidator.h"
#include "analysis/AlgorithmStats.h"

using namespace std;
using namespace std::chrono;

// Generate synthetic university courses
vector<Course> generateCourses(int count)
{
    vector<Course> courses;

    for (int i = 0; i < count; i++)
    {
        Course c{};

        c.id = i + 1;
        c.code = "CSE" + to_string(i + 1);
        c.name = "Subject " + to_string(i + 1);

        c.facultyId = (i % 100) + 1;
        c.sectionId = (i % 100) + 1;

        c.students = 40 + (i % 21);
        c.lecturesPerWeek = 3;
        c.requiresLab = (i % 5 == 0);

        courses.push_back(c);
    }

    return courses;
}

// Generate rooms
vector<Room> generateRooms(int count)
{
    vector<Room> rooms;

    for (int i = 0; i < count; i++)
    {
        Room r{};

        r.id = i + 1;
        r.name = "Room-" + to_string(i + 1);
        r.capacity = 80;
        r.isLab = (i % 5 == 0);

        rooms.push_back(r);
    }

    return rooms;
}

// Generate 5 days x 8 periods
vector<TimeSlot> generateSlots()
{
    vector<TimeSlot> slots;

    string days[] = {
        "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday"
    };

    int id = 1;

    for (const string& day : days)
    {
        for (int hour = 9; hour < 17; hour++)
        {
            TimeSlot t{};

            t.id = id++;
            t.day = day;
            t.startHour = hour;
            t.endHour = hour + 1;

            slots.push_back(t);
        }
    }

    return slots;
}

void runStressTest(int courseCount, int roomCount)
{
    vector<Course> courses = generateCourses(courseCount);
    vector<Room> rooms = generateRooms(roomCount);
    vector<TimeSlot> slots = generateSlots();

    AlgorithmStats stats;

    auto start = steady_clock::now();

    vector<TimetableEntry> timetable =
        TimetableAllocator::generate(
            courses, rooms, slots, stats
        );

    auto end = steady_clock::now();

    double timeMs =
        duration<double, milli>(end - start).count();

    int required = 0;

    for (const Course& c : courses)
        required += c.lecturesPerWeek;

    cout << "\n---------------------------------\n";
    cout << "Courses: " << courseCount << "\n";
    cout << "Rooms: " << roomCount << "\n";
    cout << "Required lectures: " << required << "\n";
    cout << "Scheduled: " << timetable.size() << "\n";
    cout << "Unscheduled: "
         << required - (int)timetable.size() << "\n";
    cout << "Candidate checks: "
         << stats.comparisons << "\n";
    cout << "Execution time: "
         << timeMs << " ms\n";

    if (courseCount == 30)
    {
        bool valid = TimetableValidator::validate(
            timetable, courses, rooms, slots
        );

        cout << "Full timetable validation: "
             << (valid ? "PASS" : "FAIL") << "\n";
    }
}

int main()
{
    cout << "UNIVERSITY TIMETABLE STRESS TEST\n";

    runStressTest(30, 10);
    runStressTest(150, 30);
    runStressTest(300, 60);

    return 0;
}
