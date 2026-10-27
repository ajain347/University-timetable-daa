#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <vector>
#include "models/UniversityModels.h"
#include "analysis/AlgorithmStats.h"

class BinarySearch {
public:
    static int iterativeCourseSearch(
        const std::vector<Course>& courses,
        int targetId,
        AlgorithmStats& stats
    );

    static int recursiveCourseSearch(
    const std::vector<Course>& courses,
    int targetId,
    int left,
    int right,
    AlgorithmStats& stats
    );
};

#endif