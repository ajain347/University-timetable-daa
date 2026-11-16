
#include "timetable/TimetableAllocator.h"

bool TimetableAllocator::isValidAssignment(
    const Course& course,
    const Room& room,
    const TimeSlot& slot,
    const std::vector<TimetableEntry>& timetable,
    const std::vector<TimeSlot>& timeSlots)
{
    // Check room capacity
    if (room.capacity < course.students)
        return false;

    // Check laboratory requirement
    if (course.requiresLab && !room.isLab)
        return false;

    // Prevent the same course from having
    // more than one lecture per day
    for (const TimetableEntry& entry : timetable)
    {
        if (entry.courseId == course.id)
        {
            for (const TimeSlot& existingSlot : timeSlots)
            {
                if (existingSlot.id == entry.slotId &&
                    existingSlot.day == slot.day)
                {
                    return false;
                }
            }
        }
    }

    // Check timetable clashes
    for (const TimetableEntry& entry : timetable)
    {
        if (entry.slotId != slot.id)
            continue;

        // Same faculty cannot teach two classes
        if (entry.facultyId == course.facultyId)
            return false;

        // Same section cannot attend two classes
        if (entry.sectionId == course.sectionId)
            return false;

        // Same room cannot host two classes
        if (entry.roomId == room.id)
            return false;
    }

    return true;
}

std::vector<TimetableEntry> TimetableAllocator::generate(
    const std::vector<Course>& courses,
    const std::vector<Room>& rooms,
    const std::vector<TimeSlot>& timeSlots,
    AlgorithmStats& stats)
{
    std::vector<TimetableEntry> timetable;

    for (const Course& course : courses)
    {
        // Schedule every required weekly lecture
        for (int lecture = 0;
             lecture < course.lecturesPerWeek;
             lecture++)
        {
            bool allocated = false;

            for (const TimeSlot& slot : timeSlots)
            {
                for (const Room& room : rooms)
                {
                    stats.comparisons++;

                    if (isValidAssignment(
                            course, room, slot, timetable, timeSlots))
                    {
                        TimetableEntry entry{};

                        entry.courseId = course.id;
                        entry.facultyId = course.facultyId;
                        entry.sectionId = course.sectionId;
                        entry.roomId = room.id;
                        entry.slotId = slot.id;

                        timetable.push_back(entry);
                        stats.operations++;

                        allocated = true;
                        break;
                    }
                }

                if (allocated)
                    break;
            }

            if (!allocated)
            {
                // This lecture remains unscheduled.
                stats.operations++;
            }
        }
    }

    return timetable;
}
