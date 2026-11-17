
#include "timetable/BacktrackingAllocator.h"
#include <stdexcept>

bool BacktrackingAllocator::canAssign(
    const Course& course,
    const Room& room,
    const TimeSlot& slot,
    const std::vector<TimetableEntry>& timetable,
    const std::vector<TimeSlot>& slots)
{
    if (room.capacity < course.students)
        return false;

    if (course.requiresLab && !room.isLab)
        return false;

    for (const TimetableEntry& entry : timetable)
    {
        const TimeSlot* previous = nullptr;

        for (const TimeSlot& t : slots)
        {
            if (t.id == entry.slotId)
            {
                previous = &t;
                break;
            }
        }

        if (previous == nullptr)
            return false;

        bool sameDay = previous->day == slot.day;

        // One lecture per course offering per day
        if (entry.courseId == course.id && sameDay)
            return false;

        bool overlap =
            sameDay &&
            previous->startHour < slot.endHour &&
            slot.startHour < previous->endHour;

        if (overlap)
        {
            if (entry.facultyId == course.facultyId ||
                entry.sectionId == course.sectionId ||
                entry.roomId == room.id)
            {
                return false;
            }
        }
    }

    return true;
}

bool BacktrackingAllocator::solve(
    int index,
    const std::vector<const Course*>& lectures,
    const std::vector<Room>& rooms,
    const std::vector<TimeSlot>& slots,
    std::vector<TimetableEntry>& timetable,
    AlgorithmStats& stats,
    long long& nodes,
    long long maxNodes,
    bool& limitReached)
{
    // All lectures assigned
    if (index == static_cast<int>(lectures.size()))
        return true;

    if (nodes >= maxNodes)
    {
        limitReached = true;
        return false;
    }

    const Course& course = *lectures[index];

    for (const TimeSlot& slot : slots)
    {
        for (const Room& room : rooms)
        {
            if (nodes >= maxNodes)
            {
                limitReached = true;
                return false;
            }

            nodes++;
            stats.comparisons++;

            if (!canAssign(course, room, slot, timetable, slots))
                continue;

            TimetableEntry entry{
                course.id,
                course.facultyId,
                course.sectionId,
                room.id,
                slot.id
            };

            // Choose
            timetable.push_back(entry);
            stats.operations++;

            // Explore
            if (solve(
                index + 1,
                lectures,
                rooms,
                slots,
                timetable,
                stats,
                nodes,
                maxNodes,
                limitReached))
            {
                return true;
            }

            // Undo choice (backtrack)
            timetable.pop_back();
            stats.operations++;

            if (limitReached)
                return false;
        }
    }

    return false;
}

BacktrackingResult BacktrackingAllocator::generate(
    const std::vector<Course>& courses,
    const std::vector<Room>& rooms,
    const std::vector<TimeSlot>& slots,
    AlgorithmStats& stats,
    long long maxNodes)
{
    if (maxNodes <= 0)
        throw std::invalid_argument("Invalid search limit");

    std::vector<const Course*> lectures;

    for (const Course& course : courses)
    {
        if (course.lecturesPerWeek < 0)
            throw std::invalid_argument("Invalid lecture count");

        for (int i = 0; i < course.lecturesPerWeek; i++)
            lectures.push_back(&course);
    }

    BacktrackingResult result;

    long long nodes = 0;
    bool limitReached = false;

    result.complete = solve(
        0,
        lectures,
        rooms,
        slots,
        result.timetable,
        stats,
        nodes,
        maxNodes,
        limitReached
    );

    result.searchLimitReached = limitReached;

    // Do not return an incomplete partial schedule
    if (!result.complete)
        result.timetable.clear();

    return result;
}
