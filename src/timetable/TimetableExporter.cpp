
#include "timetable/TimetableExporter.h"
#include <fstream>

bool TimetableExporter::exportCSV(
    const std::string& filename,
    const std::vector<TimetableEntry>& timetable,
    const std::vector<Course>& courses,
    const std::vector<Faculty>& faculty,
    const std::vector<Section>& sections,
    const std::vector<Room>& rooms,
    const std::vector<TimeSlot>& timeSlots)
{
    std::ofstream file(filename);

    if (!file.is_open())
        return false;

    file << "Day,StartHour,EndHour,Course,Faculty,Batch,Room\n";

    for (const TimetableEntry& entry : timetable)
    {
        std::string courseName, facultyName, batchName, roomName;
        std::string day;
        int startHour = 0, endHour = 0;

        for (const Course& c : courses)
            if (c.id == entry.courseId)
            {
                courseName = c.name;
                break;
            }

        for (const Faculty& f : faculty)
            if (f.id == entry.facultyId)
            {
                facultyName = f.name;
                break;
            }

        for (const Section& s : sections)
            if (s.id == entry.sectionId)
            {
                batchName = s.name;
                break;
            }

        for (const Room& r : rooms)
            if (r.id == entry.roomId)
            {
                roomName = r.name;
                break;
            }

        for (const TimeSlot& t : timeSlots)
            if (t.id == entry.slotId)
            {
                day = t.day;
                startHour = t.startHour;
                endHour = t.endHour;
                break;
            }

        file << day << ","
             << startHour << ","
             << endHour << ","
             << courseName << ","
             << facultyName << ","
             << batchName << ","
             << roomName << "\n";
    }

    file.close();
    return file.good();
}
