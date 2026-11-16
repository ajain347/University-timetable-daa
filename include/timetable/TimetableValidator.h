
#ifndef TIMETABLE_VALIDATOR_H
#define TIMETABLE_VALIDATOR_H

#include <vector>
#include "models/UniversityModels.h"

class TimetableValidator
{
public:
    static bool validate(
        const std::vector<TimetableEntry>& timetable,
        const std::vector<Course>& courses,
        const std::vector<Room>& rooms,
        const std::vector<TimeSlot>& timeSlots
    );
};

#endif
