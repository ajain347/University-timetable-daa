#include "data/DataLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>

// --------------------------------------------------
// LOAD COURSES
// --------------------------------------------------

std::vector<Course> DataLoader::loadCourses(const std::string& filename) {

    std::vector<Course> courses;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return courses;
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string value;

        Course course{};

        try {
            std::getline(ss, value, ',');
            course.id = std::stoi(value);

            std::getline(ss, course.code, ',');
            std::getline(ss, course.name, ',');

            std::getline(ss, value, ',');
            course.facultyId = std::stoi(value);

            std::getline(ss, value, ',');
            course.sectionId = std::stoi(value);

            std::getline(ss, value, ',');
            course.students = std::stoi(value);

            std::getline(ss, value, ',');
            course.lecturesPerWeek = std::stoi(value);

            std::getline(ss, value, ',');
            course.requiresLab = (std::stoi(value) != 0);

            courses.push_back(course);

        } catch (...) {
            std::cerr << "Warning: Invalid course record skipped: "
                      << line << "\n";
        }
    }

    return courses;
}


// --------------------------------------------------
// LOAD FACULTY
// --------------------------------------------------

std::vector<Faculty> DataLoader::loadFaculty(const std::string& filename) {

    std::vector<Faculty> facultyList;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return facultyList;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string value;

        Faculty faculty{};

        try {
            std::getline(ss, value, ',');
            faculty.id = std::stoi(value);

            std::getline(ss, faculty.name, ',');

            facultyList.push_back(faculty);

        } catch (...) {
            std::cerr << "Warning: Invalid faculty record skipped: "
                      << line << "\n";
        }
    }

    return facultyList;
}


// --------------------------------------------------
// LOAD ROOMS
// --------------------------------------------------

std::vector<Room> DataLoader::loadRooms(const std::string& filename) {

    std::vector<Room> rooms;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return rooms;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string value;

        Room room{};

        try {
            std::getline(ss, value, ',');
            room.id = std::stoi(value);

            std::getline(ss, room.name, ',');

            std::getline(ss, value, ',');
            room.capacity = std::stoi(value);

            std::getline(ss, value, ',');
            room.isLab = (std::stoi(value) != 0);

            rooms.push_back(room);

        } catch (...) {
            std::cerr << "Warning: Invalid room record skipped: "
                      << line << "\n";
        }
    }

    return rooms;
}


// --------------------------------------------------
// LOAD SECTIONS
// --------------------------------------------------

std::vector<Section> DataLoader::loadSections(const std::string& filename) {

    std::vector<Section> sections;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return sections;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string value;

        Section section{};

        try {
            std::getline(ss, value, ',');
            section.id = std::stoi(value);

            std::getline(ss, section.name, ',');

            std::getline(ss, value, ',');
            section.studentCount = std::stoi(value);

            sections.push_back(section);

        } catch (...) {
            std::cerr << "Warning: Invalid section record skipped: "
                      << line << "\n";
        }
    }

    return sections;
}


// --------------------------------------------------
// LOAD TIME SLOTS
// --------------------------------------------------

std::vector<TimeSlot> DataLoader::loadTimeSlots(const std::string& filename) {

    std::vector<TimeSlot> timeSlots;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return timeSlots;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string value;

        TimeSlot slot{};

        try {
            std::getline(ss, value, ',');
            slot.id = std::stoi(value);

            std::getline(ss, slot.day, ',');

            std::getline(ss, value, ',');
            slot.startHour = std::stoi(value);

            std::getline(ss, value, ',');
            slot.endHour = std::stoi(value);

            timeSlots.push_back(slot);

        } catch (...) {
            std::cerr << "Warning: Invalid time slot record skipped: "
                      << line << "\n";
        }
    }

    return timeSlots;
}