
#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "models/UniversityModels.h"
#include "data/DataLoader.h"
#include "validation/DataValidator.h"
#include "timetable/TimetableAllocator.h"
#include "timetable/TimetableValidator.h"
#include "timetable/TimetableExporter.h"
#include "analysis/AlgorithmStats.h"
#include "algorithms/sorting/MergeSort.h"
#include "algorithms/searching/BinarySearch.h"
#include "timetable/BacktrackingAllocator.h"
#include <chrono>
#include "algorithms/string_matching/StringMatching.h"

using namespace std;

int main()
{
    vector<Course> courses;
    vector<Faculty> faculty;
    vector<Room> rooms;
    vector<Section> sections;
    vector<TimeSlot> timeSlots;
    vector<TimetableEntry> timetable;

    AlgorithmStats allocationStats;

    bool dataLoaded = false;
    bool timetableGenerated = false;

    int choice = -1;

    while (choice != 0)
    {
        cout << "\n========================================\n";
        cout << " UNIVERSITY TIMETABLE ALLOCATION ENGINE\n";
        cout << "========================================\n";

        cout << "1. Load University Data\n";
        cout << "2. Generate Timetable\n";
        cout << "3. View Timetable\n";
        cout << "4. Search Timetable\n";
        cout << "5. Constraint Diagnostics\n";
        cout << "6. Algorithm Information\n";
        cout << "7. Allocation Statistics\n";
        cout << "0. Exit\n";

        cout << "\nEnter choice: ";

        if (!(cin >> choice))
        {
            if (cin.eof()) break;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            // Load into temporary vectors first
            auto newCourses =
                DataLoader::loadCourses("../data/courses.csv");

            auto newFaculty =
                DataLoader::loadFaculty("../data/faculty.csv");

            auto newRooms =
                DataLoader::loadRooms("../data/rooms.csv");

            auto newSections =
                DataLoader::loadSections("../data/sections.csv");

            auto newSlots =
                DataLoader::loadTimeSlots("../data/timeslots.csv");

            if (newCourses.empty() || newFaculty.empty() ||
                newRooms.empty() || newSections.empty() ||
                newSlots.empty())
            {
                cout << "Failed to load complete university data.\n";
                break;
            }

            if (!DataValidator::validate(
                    newCourses, newFaculty, newRooms,
                    newSections, newSlots))
            {
                cout << "Data validation failed.\n";
                break;
            }

            courses = newCourses;
            faculty = newFaculty;
            rooms = newRooms;
            sections = newSections;
            timeSlots = newSlots;

            dataLoaded = true;
            timetableGenerated = false;
            timetable.clear();
            allocationStats.reset();

            cout << "\nUniversity data loaded successfully!\n";
            cout << "Courses: " << courses.size() << "\n";
            cout << "Faculty: " << faculty.size() << "\n";
            cout << "Rooms: " << rooms.size() << "\n";
            cout << "Batches: " << sections.size() << "\n";
            cout << "Time Slots: " << timeSlots.size() << "\n";

            break;
        }

        case 2:
        {
            if (!dataLoaded)
            {
                cout << "Load university data first (Option 1).\n";
                break;
            }

            allocationStats.reset();

            timetable = TimetableAllocator::generate(
                courses, rooms, timeSlots, allocationStats);

            int required = 0;

            for (const Course& c : courses)
                required += c.lecturesPerWeek;

            cout << "\nTimetable generation completed.\n";
            cout << "Required lectures: " << required << "\n";
            cout << "Scheduled lectures: " << timetable.size() << "\n";
            cout << "Unscheduled lectures: "
                 << required - (int)timetable.size() << "\n";

            timetableGenerated = true;

            bool valid = TimetableValidator::validate(
                timetable, courses, rooms, timeSlots);

            cout << "Validation: "
                 << (valid ? "PASS" : "FAIL") << "\n";

            if (valid)
            {
                bool exported = TimetableExporter::exportCSV(
                    "../data/generated_timetable.csv",
                    timetable, courses, faculty,
                    sections, rooms, timeSlots);

                cout << "CSV export: "
                     << (exported ? "SUCCESS" : "FAILED")
                     << "\n";
            }

            break;
        }

        case 3:
        {
            if (!timetableGenerated)
            {
                cout << "Generate a timetable first.\n";
                break;
            }

            cout << "\n========== GENERATED TIMETABLE ==========\n";

            for (const TimetableEntry& entry : timetable)
            {
                string courseName, facultyName, batchName, roomName;
                string day;
                int start = 0, end = 0;

                for (const Course& c : courses)
                    if (c.id == entry.courseId)
                        courseName = c.name;

                for (const Faculty& f : faculty)
                    if (f.id == entry.facultyId)
                        facultyName = f.name;

                for (const Section& s : sections)
                    if (s.id == entry.sectionId)
                        batchName = s.name;

                for (const Room& r : rooms)
                    if (r.id == entry.roomId)
                        roomName = r.name;

                for (const TimeSlot& t : timeSlots)
                    if (t.id == entry.slotId)
                    {
                        day = t.day;
                        start = t.startHour;
                        end = t.endHour;
                    }

                cout << day << " " << start << ":00-"
                     << end << ":00 | "
                     << courseName << " | "
                     << facultyName << " | "
                     << batchName << " | "
                     << roomName << "\n";
            }

            break;
        }

        case 4:
        {
            if (!timetableGenerated)
            {
                cout << "Generate a timetable first.\n";
                break;
            }

            cout << "\nSearch by:\n";
            cout << "1. Course ID\n";
            cout << "2. Faculty Name\n";
            cout << "3. Batch Name\n";
            cout << "Choice: ";

            int searchChoice;

            if (!(cin >> searchChoice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid search choice.\n";
                break;
            }

            int targetId = -1;
            string query;

            if (searchChoice == 1)
            {
                cout << "Enter Course ID: ";
                if (!(cin >> targetId))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid course ID.\n";
                    break;
                }
            }
            else if (searchChoice == 2 || searchChoice == 3)
            {
                cout << "Enter name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, query);
            }
            else
            {
                cout << "Invalid search choice.\n";
                break;
            }

            bool found = false;

            for (const TimetableEntry& entry : timetable)
            {
                string courseName, facultyName, batchName, roomName;
                string day;
                int start = 0, end = 0;

                for (const Course& c : courses)
                    if (c.id == entry.courseId)
                        courseName = c.name;

                for (const Faculty& f : faculty)
                    if (f.id == entry.facultyId)
                        facultyName = f.name;

                for (const Section& s : sections)
                    if (s.id == entry.sectionId)
                        batchName = s.name;

                for (const Room& r : rooms)
                    if (r.id == entry.roomId)
                        roomName = r.name;

                for (const TimeSlot& t : timeSlots)
                    if (t.id == entry.slotId)
                    {
                        day = t.day;
                        start = t.startHour;
                        end = t.endHour;
                    }

                bool match =
                    (searchChoice == 1 && entry.courseId == targetId) ||
                    (searchChoice == 2 && facultyName == query) ||
                    (searchChoice == 3 && batchName == query);

                if (match)
                {
                    found = true;

                    cout << day << " " << start << ":00-"
                         << end << ":00 | "
                         << courseName << " | "
                         << facultyName << " | "
                         << batchName << " | "
                         << roomName << "\n";
                }
            }

            if (!found)
                cout << "No matching timetable entries found.\n";

            break;
        }

        case 5:
        {
            if (!timetableGenerated)
            {
                cout << "Generate a timetable first.\n";
                break;
            }

            bool valid = TimetableValidator::validate(
                timetable, courses, rooms, timeSlots);

            cout << "\nConstraint Diagnostics: "
                 << (valid ? "PASS" : "FAIL") << "\n";

            break;
        }

        
case 6:
{
    if (!dataLoaded)
    {
        cout << "Load university data first.\n";
        break;
    }

    cout << "\n===== STRING MATCHING ANALYSIS =====\n";

    string query;

    cout << "Enter subject/faculty/batch keyword: ";
    cin >> ws;
    getline(cin, query);

    if (query.empty())
    {
        cout << "Empty search query.\n";
        break;
    }

    // Build searchable text from actual university records.
    string searchableText;

    for (const Course& c : courses)
        searchableText += c.code + " " + c.name + "\n";

    for (const Faculty& f : faculty)
        searchableText += f.name + "\n";

    for (const Section& s : sections)
        searchableText += s.name + "\n";

    AlgorithmStats naiveStats;
    AlgorithmStats rkStats;
    AlgorithmStats faStats;
    AlgorithmStats kmpStats;

    using Clock = chrono::steady_clock;

    auto start = Clock::now();
    auto naiveMatches = StringMatching::naive(
        searchableText, query, naiveStats);
    auto end = Clock::now();

    double naiveMs =
        chrono::duration<double, milli>(end - start).count();

    start = Clock::now();
    auto rkMatches = StringMatching::rabinKarp(
        searchableText, query, rkStats);
    end = Clock::now();

    double rkMs =
        chrono::duration<double, milli>(end - start).count();

    start = Clock::now();
    auto faMatches = StringMatching::finiteAutomaton(
        searchableText, query, faStats);
    end = Clock::now();

    double faMs =
        chrono::duration<double, milli>(end - start).count();

    start = Clock::now();
    auto kmpMatches = StringMatching::kmp(
        searchableText, query, kmpStats);
    end = Clock::now();

    double kmpMs =
        chrono::duration<double, milli>(end - start).count();

    cout << "\nAlgorithm         Matches  Comparisons  Time(ms)\n";
    cout << "------------------------------------------------\n";

    cout << "Naive             "
         << naiveMatches.size() << "        "
         << naiveStats.comparisons << "       "
         << naiveMs << "\n";

    cout << "Rabin-Karp        "
         << rkMatches.size() << "        "
         << rkStats.comparisons << "       "
         << rkMs << "\n";

    cout << "Finite Automaton  "
         << faMatches.size() << "        "
         << faStats.comparisons << "       "
         << faMs << "\n";

    cout << "KMP               "
         << kmpMatches.size() << "        "
         << kmpStats.comparisons << "       "
         << kmpMs << "\n";

    bool sameResults =
        naiveMatches == rkMatches &&
        naiveMatches == faMatches &&
        naiveMatches == kmpMatches;

    cout << "\nCorrectness agreement: "
         << (sameResults ? "PASS" : "FAIL") << "\n";

    cout << "Note: Search is case-sensitive.\n";

    break;
}


        
case 7:
{
    if (!timetableGenerated)
    {
        cout << "Generate a timetable first.\n";
        break;
    }

    cout << "\n========== ALGORITHM COMPARISON ==========\n";

    AlgorithmStats greedyStats;
    AlgorithmStats backtrackStats;

    // -------- GREEDY --------

    auto greedyStart = chrono::steady_clock::now();

    auto greedySchedule = TimetableAllocator::generate(
        courses, rooms, timeSlots, greedyStats
    );

    auto greedyEnd = chrono::steady_clock::now();

    double greedyMs =
        chrono::duration<double, milli>(
            greedyEnd - greedyStart
        ).count();

    bool greedyValid = TimetableValidator::validate(
        greedySchedule, courses, rooms, timeSlots
    );

    cout << "\nGREEDY ALGORITHM\n";
    cout << "Scheduled lectures: "
         << greedySchedule.size() << "\n";
    cout << "Valid timetable: "
         << (greedyValid ? "YES" : "NO") << "\n";
    cout << "Candidate checks: "
         << greedyStats.comparisons << "\n";
    cout << "Execution time: "
         << greedyMs << " ms\n";


    // -------- BACKTRACKING --------

    auto backtrackStart = chrono::steady_clock::now();

    auto backtrackResult = BacktrackingAllocator::generate(
        courses, rooms, timeSlots, backtrackStats
    );

    auto backtrackEnd = chrono::steady_clock::now();

    double backtrackMs =
        chrono::duration<double, milli>(
            backtrackEnd - backtrackStart
        ).count();

    cout << "\nBACKTRACKING ALGORITHM\n";

    cout << "Complete timetable: "
         << (backtrackResult.complete ? "YES" : "NO") << "\n";

    cout << "Candidate checks: "
         << backtrackStats.comparisons << "\n";

    cout << "Execution time: "
         << backtrackMs << " ms\n";

    if (backtrackResult.complete)
    {
        bool backtrackValid = TimetableValidator::validate(
            backtrackResult.timetable,
            courses,
            rooms,
            timeSlots
        );

        cout << "Scheduled lectures: "
             << backtrackResult.timetable.size() << "\n";

        cout << "Valid timetable: "
             << (backtrackValid ? "YES" : "NO") << "\n";
    }
    else if (backtrackResult.searchLimitReached)
    {
        cout << "Search limit reached: result inconclusive.\n";
    }
    else
    {
        cout << "No complete timetable found.\n";
    }


    // ---------- CONSTRAINT SHOCK TEST ----------

    cout << "\n========== CONSTRAINT SHOCK ==========\n";

    vector<Room> shockRooms;

    // One normal classroom and one laboratory
    shockRooms.push_back(rooms[1]); // Room-201, capacity 60
    shockRooms.push_back(rooms[3]); // Lab-1, capacity 70

    AlgorithmStats shockGreedyStats;
    AlgorithmStats shockBacktrackStats;

    auto shockGreedyStart = chrono::steady_clock::now();

    auto shockGreedy = TimetableAllocator::generate(
        courses, shockRooms, timeSlots, shockGreedyStats
    );

    auto shockGreedyEnd = chrono::steady_clock::now();

    double shockGreedyMs =
        chrono::duration<double, milli>(
            shockGreedyEnd - shockGreedyStart
        ).count();

    auto shockBacktrackStart = chrono::steady_clock::now();

    auto shockBacktrack = BacktrackingAllocator::generate(
        courses, shockRooms, timeSlots, shockBacktrackStats
    );

    auto shockBacktrackEnd = chrono::steady_clock::now();

    double shockBacktrackMs =
        chrono::duration<double, milli>(
            shockBacktrackEnd - shockBacktrackStart
        ).count();

    cout << "\nGREEDY (Reduced Rooms)\n";
    cout << "Scheduled: " << shockGreedy.size() << "/24\n";
    cout << "Candidate checks: "
         << shockGreedyStats.comparisons << "\n";
    cout << "Time: " << shockGreedyMs << " ms\n";

    cout << "\nBACKTRACKING (Reduced Rooms)\n";
    cout << "Complete: "
         << (shockBacktrack.complete ? "YES" : "NO") << "\n";

    cout << "Candidate checks: "
         << shockBacktrackStats.comparisons << "\n";

    cout << "Time: " << shockBacktrackMs << " ms\n";

    if (shockBacktrack.searchLimitReached)
        cout << "Search limit reached.\n";

    cout << "======================================\n";

    cout << "\n==========================================\n";

    break;
}


        case 0:
            cout << "Exiting application.\n";
            break;

        default:
            cout << "Invalid menu option.\n";
        }
    }

    return 0;
}
