
#ifndef BACKTRACKING_ALLOCATOR_H
#define BACKTRACKING_ALLOCATOR_H

#include <vector>
#include "models/UniversityModels.h"
#include "analysis/AlgorithmStats.h"

struct BacktrackingResult
{
    std::vector<TimetableEntry> timetable;
    bool complete = false;
    bool searchLimitReached = false;
};

class BacktrackingAllocator
{
private:
    static bool canAssign(
        const Course& course,
        const Room& room,
        const TimeSlot& slot,
        const std::vector<TimetableEntry>& timetable,
        const std::vector<TimeSlot>& slots
    );

    static bool solve(
        int index,
        const std::vector<const Course*>& lectures,
        const std::vector<Room>& rooms,
        const std::vector<TimeSlot>& slots,
        std::vector<TimetableEntry>& timetable,
        AlgorithmStats& stats,
        long long& nodes,
        long long maxNodes,
        bool& limitReached
    );

public:
    static BacktrackingResult generate(
        const std::vector<Course>& courses,
        const std::vector<Room>& rooms,
        const std::vector<TimeSlot>& slots,
        AlgorithmStats& stats,
        long long maxNodes = 200000
    );
};

#endif
