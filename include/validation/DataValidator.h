#ifndef DATA_VALIDATOR_H
#define DATA_VALIDATOR_H

#include <vector>
#include "models/UniversityModels.h"

class DataValidator {
public:
    static bool validate(
        const std::vector<Course>& courses,
        const std::vector<Faculty>& faculty,
        const std::vector<Room>& rooms,
        const std::vector<Section>& sections,
        const std::vector<TimeSlot>& timeSlots
    );
};

#endif