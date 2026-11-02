#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include "models/UniversityModels.h"
#include "analysis/AlgorithmStats.h"

class MergeSort
{
public:
    static void sortCoursesById(
        std::vector<Course>& courses,
        AlgorithmStats& stats
    );

private:
    static void mergeSort(
        std::vector<Course>& courses,
        int left,
        int right,
        AlgorithmStats& stats
    );

    static void merge(
        std::vector<Course>& courses,
        int left,
        int mid,
        int right,
        AlgorithmStats& stats
    );
};

#endif