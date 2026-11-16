#include <iostream>

#include "models/UniversityModels.h"
#include "data/DataLoader.h"
#include "validation/DataValidator.h"

#include "algorithms/searching/BinarySearch.h"
#include "analysis/AlgorithmStats.h"
#include "algorithms/sorting/MergeSort.h"
#include "algorithms/sorting/QuickSort.h"
#include "algorithms/divide_conquer/MaximumSubarray.h"
#include "algorithms/divide_conquer/FastExponentiation.h"
#include "timetable/TimetableAllocator.h"
#include "timetable/TimetableValidator.h"
#include "timetable/TimetableExporter.h"

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

// ---------------- MERGE SORT TEST ----------------

vector<Course> mergeTestCourses;

mergeTestCourses.push_back(courses[7]); // ID 8
mergeTestCourses.push_back(courses[2]); // ID 3
mergeTestCourses.push_back(courses[5]); // ID 6
mergeTestCourses.push_back(courses[1]); // ID 2
mergeTestCourses.push_back(courses[6]); // ID 7
mergeTestCourses.push_back(courses[0]); // ID 1
mergeTestCourses.push_back(courses[4]); // ID 5
mergeTestCourses.push_back(courses[3]); // ID 4;

cout << "\nMerge Sort Test\n";

cout << "Before sorting: ";

for (const Course& c : mergeTestCourses)
{
    cout << c.id << " ";
}

AlgorithmStats mergeStats;

MergeSort::sortCoursesById(
    mergeTestCourses,
    mergeStats
);

cout << "\nAfter sorting:  ";

for (const Course& c : mergeTestCourses)
{
    cout << c.id << " ";
}

cout << "\nComparisons: "
     << mergeStats.comparisons;

cout << "\nOperations: "
     << mergeStats.operations;

cout << "\nMemory used: "
     << mergeStats.memoryBytes
     << " bytes\n";


// ---------------- QUICK SORT TEST ----------------
vector<Course> quickTestCourses;

quickTestCourses.push_back(courses[7]); // ID 8
quickTestCourses.push_back(courses[2]); // ID 3
quickTestCourses.push_back(courses[5]); // ID 6
quickTestCourses.push_back(courses[1]); // ID 2
quickTestCourses.push_back(courses[6]); // ID 7
quickTestCourses.push_back(courses[0]); // ID 1
quickTestCourses.push_back(courses[4]); // ID 5
quickTestCourses.push_back(courses[3]); // ID 4

cout << "\nQuick Sort Test\n";

cout << "Before sorting: ";

for (const Course& c : quickTestCourses)
{
    cout << c.id << " ";
}

AlgorithmStats quickStats;

QuickSort::sortCoursesById(
    quickTestCourses,
    quickStats
);

cout << "\nAfter sorting:  ";

for (const Course& c : quickTestCourses)
{
    cout << c.id << " ";
}

cout << "\nComparisons: "
     << quickStats.comparisons;

cout << "\nOperations: "
     << quickStats.operations;

cout << "\nMemory used: "
     << quickStats.memoryBytes
     << " bytes\n";

// ---------------- MAXIMUM SUBARRAY TEST ----------------

vector<int> workload = {-2, 4, -1, 3, -5, 2};

AlgorithmStats maxStats;

MaxSubarrayResult result =
    MaximumSubarray::findMaximum(workload, maxStats);

cout << "\nMaximum Subarray Test\n";

cout << "Maximum Sum: " << result.sum << "\n";
cout << "Start Index: " << result.left << "\n";
cout << "End Index: " << result.right << "\n";

cout << "Comparisons: " << maxStats.comparisons << "\n";
cout << "Operations: " << maxStats.operations << "\n";


    // -------- TIMETABLE GENERATION --------

    AlgorithmStats allocationStats;

    vector<TimetableEntry> timetable =
        TimetableAllocator::generate(
            courses,
            rooms,
            timeSlots,
            allocationStats
        );

    int requiredLectures = 0;

    for (const Course& course : courses)
    {
        requiredLectures += course.lecturesPerWeek;
    }

    cout << "\n========== TIMETABLE ALLOCATION ==========\n";

    cout << "Required lectures: "
         << requiredLectures << "\n";

    cout << "Scheduled lectures: "
         << timetable.size() << "\n";

    cout << "Unscheduled lectures: "
         << requiredLectures - timetable.size() << "\n";

    cout << "Allocation checks: "
         << allocationStats.comparisons << "\n";

    cout << "==========================================\n";

    if (static_cast<int>(timetable.size()) == requiredLectures)
    {
        cout << "All lectures scheduled successfully!\n";
    }
    else
    {
        cout << "Warning: Some lectures could not be scheduled.\n";
    }

    
cout << "\n========== GENERATED TIMETABLE ==========\n";

for (const TimetableEntry& entry : timetable)
{
    cout << "\n";

    // Find course name
    for (const Course& c : courses)
    {
        if (c.id == entry.courseId)
        {
            cout << "Subject: " << c.name << " | ";
            break;
        }
    }

    // Find faculty name
    for (const Faculty& f : faculty)
    {
        if (f.id == entry.facultyId)
        {
            cout << "Faculty: " << f.name << " | ";
            break;
        }
    }

    // Find batch name
    for (const Section& s : sections)
    {
        if (s.id == entry.sectionId)
        {
            cout << "Batch: " << s.name << " | ";
            break;
        }
    }

    // Find classroom
    for (const Room& r : rooms)
    {
        if (r.id == entry.roomId)
        {
            cout << "Room: " << r.name << " | ";
            break;
        }
    }

    // Find day and time
    for (const TimeSlot& t : timeSlots)
    {
        if (t.id == entry.slotId)
        {
            cout << "Day: " << t.day
                 << " | Time: "
                 << t.startHour << ":00-"
                 << t.endHour << ":00";
            break;
        }
    }

    cout << "\n";
}


cout << "\n========== TIMETABLE VALIDATION ==========\n";

bool timetableValid = TimetableValidator::validate(
    timetable, courses, rooms, timeSlots
);

if (timetableValid)
{
    cout << "PASS: All required lectures scheduled without clashes.\n";

    bool exported = TimetableExporter::exportCSV(
        "../data/generated_timetable.csv",
        timetable,
        courses,
        faculty,
        sections,
        rooms,
        timeSlots
    );

    if (exported)
        cout << "Timetable exported successfully.\n";
    else
        cout << "Error: Timetable export failed.\n";
}
else
{
    cout << "FAIL: Timetable contains violations or missing lectures.\n";
    cout << "Export skipped.\n";
}



// ---------------- FAST EXPONENTIATION TEST ----------------

AlgorithmStats powerStats;

long long answer = FastExponentiation::power(2,15,powerStats);

cout << "\nFast Exponentiation Test\n";
cout << "2^15 = " << answer << "\n";
cout << "Multiplications: "
     << powerStats.operations << "\n\n";

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