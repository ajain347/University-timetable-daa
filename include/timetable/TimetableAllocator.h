
#ifndef TIMETABLE_ALLOCATOR_H
#define TIMETABLE_ALLOCATOR_H

#include <vector>
#include "models/UniversityModels.h"
#include "analysis/AlgorithmStats.h"

class TimetableAllocator
{
public:
    static std::vector<TimetableEntry> generate(
        const std::vector<Course>& courses,
        const std::vector<Room>& rooms,
        const std::vector<TimeSlot>& timeSlots,
        AlgorithmStats& stats
    );

private:
    static bool isValidAssignment(
        const Course& course,
        const Room& room,
        const TimeSlot& slot,
        const std::vector<TimetableEntry>& timetable,
        const std::vector<TimeSlot>& timeSlots
    );
};

#endif
