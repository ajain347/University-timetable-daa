
#include "timetable/TimetableValidator.h"
#include <iostream>

bool TimetableValidator::validate(
    const std::vector<TimetableEntry>& timetable,
    const std::vector<Course>& courses,
    const std::vector<Room>& rooms,
    const std::vector<TimeSlot>& timeSlots)
{
    bool valid = true;

    // Check every scheduled lecture
    for (int i = 0; i < static_cast<int>(timetable.size()); i++)
    {
        const TimetableEntry& a = timetable[i];

        const Course* course = nullptr;
        const Room* room = nullptr;
        const TimeSlot* slot = nullptr;

        for (const Course& c : courses)
        {
            if (c.id == a.courseId)
            {
                course = &c;
                break;
            }
        }

        for (const Room& r : rooms)
        {
            if (r.id == a.roomId)
            {
                room = &r;
                break;
            }
        }

        for (const TimeSlot& t : timeSlots)
        {
            if (t.id == a.slotId)
            {
                slot = &t;
                break;
            }
        }

        if (course == nullptr || room == nullptr || slot == nullptr)
        {
            std::cerr << "Invalid course, room or slot reference.\n";
            valid = false;
            continue;
        }

        if (a.facultyId != course->facultyId ||
            a.sectionId != course->sectionId)
        {
            std::cerr << "Course assignment has incorrect faculty/batch.\n";
            valid = false;
        }

        if (room->capacity < course->students)
        {
            std::cerr << "Room capacity violation.\n";
            valid = false;
        }

        if (course->requiresLab && !room->isLab)
        {
            std::cerr << "Laboratory requirement violation.\n";
            valid = false;
        }

        // Compare with every later timetable entry
        for (int j = i + 1; j < static_cast<int>(timetable.size()); j++)
        {
            const TimetableEntry& b = timetable[j];

            const TimeSlot* otherSlot = nullptr;

            for (const TimeSlot& t : timeSlots)
            {
                if (t.id == b.slotId)
                {
                    otherSlot = &t;
                    break;
                }
            }

            if (otherSlot == nullptr)
                continue;

            bool sameDay = slot->day == otherSlot->day;

            bool overlap =
                slot->startHour < otherSlot->endHour &&
                otherSlot->startHour < slot->endHour;

            if (sameDay && overlap)
            {
                if (a.facultyId == b.facultyId ||
                    a.sectionId == b.sectionId ||
                    a.roomId == b.roomId)
                {
                    std::cerr << "Timetable clash detected.\n";
                    valid = false;
                }
            }

            // Same course offering cannot appear twice in one day
            if (sameDay && a.courseId == b.courseId)
            {
                std::cerr << "Repeated course on the same day.\n";
                valid = false;
            }
        }
    }

    // Check whether all required lectures were scheduled
    for (const Course& c : courses)
    {
        int count = 0;

        for (const TimetableEntry& entry : timetable)
        {
            if (entry.courseId == c.id)
                count++;
        }

        if (count != c.lecturesPerWeek)
        {
            std::cerr << "Course " << c.code
                      << " (ID " << c.id << ") requires "
                      << c.lecturesPerWeek
                      << " lectures, but has "
                      << count << ".\n";
            valid = false;
        }
    }

    return valid;
}
