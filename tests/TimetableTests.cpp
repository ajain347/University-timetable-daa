
#include <iostream>
#include <vector>
#include <cassert>

#include "models/UniversityModels.h"
#include "analysis/AlgorithmStats.h"
#include "timetable/TimetableAllocator.h"
#include "timetable/BacktrackingAllocator.h"
#include "timetable/TimetableValidator.h"
#include "algorithms/sorting/MergeSort.h"
#include "algorithms/sorting/QuickSort.h"
#include "algorithms/searching/BinarySearch.h"
#include "algorithms/string_matching/StringMatching.h"

using namespace std;

int main()
{
    // -------- SORTING TESTS --------

    vector<Course> courses(5);

    int ids[] = {5, 2, 4, 1, 3};

    for (int i = 0; i < 5; i++)
        courses[i].id = ids[i];

    vector<Course> mergeCourses = courses;
    vector<Course> quickCourses = courses;

    AlgorithmStats mergeStats;
    AlgorithmStats quickStats;

    MergeSort::sortCoursesById(mergeCourses, mergeStats);
    QuickSort::sortCoursesById(quickCourses, quickStats);

    for (int i = 0; i < 5; i++)
    {
        assert(mergeCourses[i].id == i + 1);
        assert(quickCourses[i].id == i + 1);
    }

    cout << "PASS: Merge Sort and Quick Sort\n";

    // -------- BINARY SEARCH --------

    AlgorithmStats binaryStats;

    int index = BinarySearch::iterativeCourseSearch(
        mergeCourses, 3, binaryStats
    );

    assert(index == 2);

    AlgorithmStats recursiveStats;

    int recursiveIndex =
        BinarySearch::recursiveCourseSearch(
            mergeCourses, 3, 0, 4, recursiveStats
        );

    assert(recursiveIndex == 2);

    cout << "PASS: Iterative and Recursive Binary Search\n";

    // -------- STRING MATCHING --------

    string text = "DAA OS DAA ML DAA";
    string pattern = "DAA";

    AlgorithmStats s1, s2, s3, s4;

    vector<int> expected = {0, 7, 14};

    assert(StringMatching::naive(
        text, pattern, s1) == expected);

    assert(StringMatching::rabinKarp(
        text, pattern, s2) == expected);

    assert(StringMatching::finiteAutomaton(
        text, pattern, s3) == expected);

    assert(StringMatching::kmp(
        text, pattern, s4) == expected);

    cout << "PASS: All four String Matching algorithms\n";

    // -------- TIMETABLE ALLOCATION --------

    Course c{};
    c.id = 1;
    c.facultyId = 1;
    c.sectionId = 1;
    c.students = 30;
    c.lecturesPerWeek = 2;
    c.requiresLab = false;

    vector<Course> testCourses = {c};

    Room r{};
    r.id = 1;
    r.capacity = 40;
    r.isLab = false;

    vector<Room> rooms = {r};

    TimeSlot monday{};
    monday.id = 1;
    monday.day = "Monday";
    monday.startHour = 9;
    monday.endHour = 10;

    TimeSlot tuesday{};
    tuesday.id = 2;
    tuesday.day = "Tuesday";
    tuesday.startHour = 9;
    tuesday.endHour = 10;

    vector<TimeSlot> slots = {monday, tuesday};

    AlgorithmStats greedyStats;

    auto greedy = TimetableAllocator::generate(
        testCourses, rooms, slots, greedyStats
    );

    assert(greedy.size() == 2);

    assert(TimetableValidator::validate(
        greedy, testCourses, rooms, slots
    ));

    cout << "PASS: Greedy Timetable Allocation\n";

    AlgorithmStats backtrackStats;

    auto backtracking = BacktrackingAllocator::generate(
        testCourses, rooms, slots, backtrackStats
    );

    assert(backtracking.complete);
    assert(backtracking.timetable.size() == 2);

    assert(TimetableValidator::validate(
        backtracking.timetable,
        testCourses, rooms, slots
    ));

    cout << "PASS: Backtracking Timetable Allocation\n";

    // -------- IMPOSSIBLE SCENARIO --------

    testCourses[0].students = 100;

    AlgorithmStats impossibleStats;

    auto impossible = TimetableAllocator::generate(
        testCourses, rooms, slots, impossibleStats
    );

    assert(impossible.empty());

    cout << "PASS: Insufficient Room Capacity\n";

    cout << "\nALL TIMETABLE TESTS PASSED\n";

    return 0;
}
