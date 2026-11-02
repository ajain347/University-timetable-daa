#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include "models/UniversityModels.h"
#include "analysis/AlgorithmStats.h"

class QuickSort
{
public:
    static void sortCoursesById(
        std::vector<Course>& courses,
        AlgorithmStats& stats
    );

private:
    static void quickSort(
        std::vector<Course>& courses,
        int low,
        int high,
        AlgorithmStats& stats
    );

    static int partition(
        std::vector<Course>& courses,
        int low,
        int high,
        AlgorithmStats& stats
    );

    static void swapCourses(
        Course& a,
        Course& b,
        AlgorithmStats& stats
    );
};

#endif