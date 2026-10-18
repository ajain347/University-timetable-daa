#include "validation/DataValidator.h"

#include <iostream>
#include <set>

bool DataValidator::validate(
    const std::vector<Course>& courses,
    const std::vector<Faculty>& faculty,
    const std::vector<Room>& rooms,
    const std::vector<Section>& sections,
    const std::vector<TimeSlot>& timeSlots)
{
    bool valid = true;

    std::set<int> facultyIds;
    std::set<int> sectionIds;
    std::set<int> roomIds;
    std::set<int> timeSlotIds;
    std::set<int> courseIds;

    // ---------------- FACULTY ----------------

    for (const Faculty& f : faculty) {

        if (f.id <= 0) {
            std::cerr << "Validation Error: Faculty ID must be positive.\n";
            valid = false;
        }

        if (!facultyIds.insert(f.id).second) {
            std::cerr << "Validation Error: Duplicate faculty ID "
                      << f.id << ".\n";
            valid = false;
        }

        if (f.name.empty()) {
            std::cerr << "Validation Error: Faculty name cannot be empty.\n";
            valid = false;
        }
    }


    // ---------------- SECTIONS ----------------

    for (const Section& s : sections) {

        if (s.id <= 0) {
            std::cerr << "Validation Error: Section ID must be positive.\n";
            valid = false;
        }

        if (!sectionIds.insert(s.id).second) {
            std::cerr << "Validation Error: Duplicate section ID "
                      << s.id << ".\n";
            valid = false;
        }

        if (s.name.empty()) {
            std::cerr << "Validation Error: Section name cannot be empty.\n";
            valid = false;
        }

        if (s.studentCount <= 0) {
            std::cerr << "Validation Error: Invalid student count for section "
                      << s.name << ".\n";
            valid = false;
        }
    }


    // ---------------- ROOMS ----------------

    for (const Room& r : rooms) {

        if (r.id <= 0) {
            std::cerr << "Validation Error: Room ID must be positive.\n";
            valid = false;
        }

        if (!roomIds.insert(r.id).second) {
            std::cerr << "Validation Error: Duplicate room ID "
                      << r.id << ".\n";
            valid = false;
        }

        if (r.name.empty()) {
            std::cerr << "Validation Error: Room name cannot be empty.\n";
            valid = false;
        }

        if (r.capacity <= 0) {
            std::cerr << "Validation Error: Invalid capacity for room "
                      << r.name << ".\n";
            valid = false;
        }
    }


    // ---------------- TIME SLOTS ----------------

    for (const TimeSlot& t : timeSlots) {

        if (t.id <= 0) {
            std::cerr << "Validation Error: Time slot ID must be positive.\n";
            valid = false;
        }

        if (!timeSlotIds.insert(t.id).second) {
            std::cerr << "Validation Error: Duplicate time slot ID "
                      << t.id << ".\n";
            valid = false;
        }

        if (t.day.empty()) {
            std::cerr << "Validation Error: Time slot day cannot be empty.\n";
            valid = false;
        }

        if (t.startHour < 0 ||
            t.startHour > 23 ||
            t.endHour < 1 ||
            t.endHour > 24 ||
            t.startHour >= t.endHour) {

            std::cerr << "Validation Error: Invalid time range for slot "
                      << t.id << ".\n";

            valid = false;
        }
    }


    // ---------------- COURSES ----------------

    for (const Course& c : courses) {

        if (c.id <= 0) {
            std::cerr << "Validation Error: Course ID must be positive.\n";
            valid = false;
        }

        if (!courseIds.insert(c.id).second) {
            std::cerr << "Validation Error: Duplicate course ID "
                      << c.id << ".\n";
            valid = false;
        }

        if (c.code.empty() || c.name.empty()) {
            std::cerr << "Validation Error: Course code/name cannot be empty.\n";
            valid = false;
        }

        if (facultyIds.find(c.facultyId) == facultyIds.end()) {

            std::cerr << "Validation Error: Course "
                      << c.code
                      << " references missing faculty ID "
                      << c.facultyId << ".\n";

            valid = false;
        }

        if (sectionIds.find(c.sectionId) == sectionIds.end()) {

            std::cerr << "Validation Error: Course "
                      << c.code
                      << " references missing section ID "
                      << c.sectionId << ".\n";

            valid = false;
        }

        if (c.students <= 0) {

            std::cerr << "Validation Error: Invalid student count for course "
                      << c.code << ".\n";

            valid = false;
        }

        if (c.lecturesPerWeek <= 0) {

            std::cerr << "Validation Error: Invalid lectures/week for course "
                      << c.code << ".\n";

            valid = false;
        }


        // Check whether at least one suitable room exists.

        bool suitableRoomFound = false;

        for (const Room& r : rooms) {

            bool enoughCapacity = r.capacity >= c.students;

            bool correctType =
                !c.requiresLab || r.isLab;

            if (enoughCapacity && correctType) {
                suitableRoomFound = true;
                break;
            }
        }

        if (!suitableRoomFound) {

            std::cerr << "Validation Error: No suitable room exists for "
                      << c.code
                      << " (course ID "
                      << c.id << ").\n";

            valid = false;
        }
    }

    return valid;
}