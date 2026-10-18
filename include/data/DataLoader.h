#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <string>
#include <vector>
#include "models/UniversityModels.h"

class DataLoader {
public:
    static std::vector<Course> loadCourses(const std::string& filename);

    static std::vector<Faculty> loadFaculty(const std::string& filename);

    static std::vector<Room> loadRooms(const std::string& filename);

    static std::vector<Section> loadSections(const std::string& filename);

    static std::vector<TimeSlot> loadTimeSlots(const std::string& filename);
};

#endif // DATA_LOADER_H