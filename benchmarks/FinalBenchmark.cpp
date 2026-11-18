
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <stdexcept>

#include "models/UniversityModels.h"
#include "data/DataLoader.h"
#include "validation/DataValidator.h"
#include "timetable/TimetableAllocator.h"
#include "timetable/BacktrackingAllocator.h"
#include "timetable/TimetableValidator.h"
#include "analysis/AlgorithmStats.h"

using namespace std;
using Clock = chrono::steady_clock;

int main()
{
    // Run from the project root.
    auto courses = DataLoader::loadCourses("data/courses.csv");
    auto faculty = DataLoader::loadFaculty("data/faculty.csv");
    auto rooms = DataLoader::loadRooms("data/rooms.csv");
    auto sections = DataLoader::loadSections("data/sections.csv");
    auto slots = DataLoader::loadTimeSlots("data/timeslots.csv");

    if (courses.empty() || faculty.empty() ||
        rooms.empty() || sections.empty() || slots.empty())
    {
        cerr << "Error: Dataset is missing or incomplete.\n";
        return 1;
    }

    if (!DataValidator::validate(
        courses, faculty, rooms, sections, slots))
    {
        cerr << "Error: Invalid university data.\n";
        return 1;
    }

    int required = 0;
    for (const Course& c : courses)
        required += c.lecturesPerWeek;

    ofstream file("benchmarks/final_results.csv");

    if (!file)
    {
        cerr << "Cannot create benchmark CSV.\n";
        return 1;
    }

    file << "Scenario,Algorithm,Run,Required,Scheduled,"
         << "Complete,Valid,CandidateChecks,Operations,"
         << "ExecutionMs,SearchLimitReached\n";

    const int runs = 20;

    cout << fixed << setprecision(6);
    file << fixed << setprecision(6);

    for (int scenario = 0; scenario < 2; scenario++)
    {
        vector<Room> scenarioRooms = rooms;

        if (scenario == 1)
        {
            // Reduced-room scenario: room IDs 2 and 4.
            scenarioRooms.clear();

            for (const Room& r : rooms)
                if (r.id == 2 || r.id == 4)
                    scenarioRooms.push_back(r);

            if (scenarioRooms.size() != 2)
            {
                cerr << "Shock scenario requires room IDs 2 and 4.\n";
                return 1;
            }
        }

        string scenarioName =
            scenario == 0 ? "Normal" : "ReducedRooms";

        for (int run = 1; run <= runs; run++)
        {
            // ---------- GREEDY ----------

            AlgorithmStats gs;

            auto start = Clock::now();

            auto greedy = TimetableAllocator::generate(
                courses, scenarioRooms, slots, gs);

            auto end = Clock::now();

            double greedyMs =
                chrono::duration<double, milli>(
                    end - start).count();

            bool greedyComplete =
                (int)greedy.size() == required;

            bool greedyValid =
                TimetableValidator::validate(
                    greedy, courses, scenarioRooms, slots);

            file << scenarioName << ",Greedy," << run << ","
                 << required << "," << greedy.size() << ","
                 << greedyComplete << "," << greedyValid << ","
                 << gs.comparisons << "," << gs.operations << ","
                 << greedyMs << ",0\n";

            // ---------- BACKTRACKING ----------

            AlgorithmStats bs;

            start = Clock::now();

            auto backtracking = BacktrackingAllocator::generate(
                courses, scenarioRooms, slots, bs);

            end = Clock::now();

            double backtrackingMs =
                chrono::duration<double, milli>(
                    end - start).count();

            bool backtrackValid = false;

            if (backtracking.complete)
            {
                backtrackValid = TimetableValidator::validate(
                    backtracking.timetable,
                    courses, scenarioRooms, slots);
            }

            file << scenarioName << ",Backtracking," << run << ","
                 << required << ","
                 << backtracking.timetable.size() << ","
                 << backtracking.complete << ","
                 << backtrackValid << ","
                 << bs.comparisons << "," << bs.operations << ","
                 << backtrackingMs << ","
                 << backtracking.searchLimitReached << "\n";
        }

        cout << scenarioName << ": "
             << runs << " runs per algorithm completed.\n";
    }

    file.close();

    cout << "\nBenchmark saved to benchmarks/final_results.csv\n";
    cout << "Total measurements: " << 2 * 2 * runs << "\n";

    return 0;
}
