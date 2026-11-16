
#ifndef TIMETABLE_EXPORTER_H
#define TIMETABLE_EXPORTER_H

#include <string>
#include <vector>
#include "models/UniversityModels.h"

class TimetableExporter
{
public:
    static bool exportCSV(
        const std::string& filename,
        const std::vector<TimetableEntry>& timetable,
        const std::vector<Course>& courses,
        const std::vector<Faculty>& faculty,
        const std::vector<Section>& sections,
        const std::vector<Room>& rooms,
        const std::vector<TimeSlot>& timeSlots
    );
};

#endif
