#include <iostream>

#include "models/UniversityModels.h"
#include "data/DataLoader.h"
#include "validation/DataValidator.h"

#include "algorithms/searching/BinarySearch.h"
#include "analysis/AlgorithmStats.h"

using namespace std;

int main()
{
    vector<Course> courses =
        DataLoader::loadCourses("../data/courses.csv");

    vector<Faculty> faculty =
        DataLoader::loadFaculty("../data/faculty.csv");

    vector<Room> rooms =
        DataLoader::loadRooms("../data/rooms.csv");

    vector<Section> sections =
        DataLoader::loadSections("../data/sections.csv");

    vector<TimeSlot> timeSlots =
        DataLoader::loadTimeSlots("../data/timeslots.csv");

    cout << "\nUniversity Data Loaded\n";
    cout << "----------------------\n";
    cout << "Courses:    " << courses.size() << "\n";
    cout << "Faculty:    " << faculty.size() << "\n";
    cout << "Rooms:      " << rooms.size() << "\n";
    cout << "Sections:   " << sections.size() << "\n";
    cout << "Time Slots: " << timeSlots.size() << "\n\n";

    cout << "\nValidating university data...\n";

    bool dataValid = DataValidator::validate(
        courses,
        faculty,
        rooms,
        sections,
        timeSlots
    );

    if (dataValid) {
        cout << "Validation successful: Dataset is valid.\n\n";
    }
    else {
        cout << "Validation failed: Please fix the dataset.\n";
        return 1;
    }

    AlgorithmStats binaryStats;

    int position = BinarySearch::iterativeCourseSearch(
        courses,
        5,
        binaryStats
    );

    if (position != -1)
    {
        cout << "\nBinary Search Test\n";
        cout << "Course found: " << courses[position].code << "\n";
        cout << "Course ID: " << courses[position].id << "\n";
        cout << "Comparisons: "
             << binaryStats.comparisons << "\n";
        cout << "Operations: "
             << binaryStats.operations << "\n";
    }
    else
    {
        cout << "\nCourse not found.\n";
    }


    AlgorithmStats recursiveStats;

int recursivePosition =
    BinarySearch::recursiveCourseSearch(
        courses,
        5,
        0,
        static_cast<int>(courses.size()) - 1,
        recursiveStats
    );

if (recursivePosition != -1)
{
    cout << "\nRecursive Binary Search Test\n";
    cout << "Course found: "
         << courses[recursivePosition].code << "\n";

    cout << "Course ID: "
         << courses[recursivePosition].id << "\n";

    cout << "Comparisons: "
         << recursiveStats.comparisons << "\n";

    cout << "Operations: "
         << recursiveStats.operations << "\n";
}

    cout << "=============================================\n";
    cout << " UNIVERSITY TIMETABLE & CLASSROOM ALLOCATION\n";
    cout << "                 ENGINE\n";
    cout << "=============================================\n\n";

    cout << "1. Load University Data\n";
    cout << "2. Generate Timetable\n";
    cout << "3. View Timetable\n";
    cout << "4. Search Timetable\n";
    cout << "5. Constraint Diagnostics\n";
    cout << "6. Algorithm Analysis\n";
    cout << "7. Run Benchmarks\n";
    cout << "0. Exit\n";

    return 0;
}