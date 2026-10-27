#include "algorithms/searching/BinarySearch.h"

int BinarySearch::iterativeCourseSearch(
    const std::vector<Course>& courses,
    int targetId,
    AlgorithmStats& stats)
{
    int left = 0;
    int right = static_cast<int>(courses.size()) - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        stats.operations++;

        stats.comparisons++;

        if (courses[middle].id == targetId)
        {
            return middle;
        }

        stats.comparisons++;

        if (courses[middle].id < targetId)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}

int BinarySearch::recursiveCourseSearch(
    const std::vector<Course>& courses,
    int targetId,
    int left,
    int right,
    AlgorithmStats& stats)
{
    if (left > right)
    {
        return -1;
    }

    int middle = left + (right - left) / 2;

    stats.operations++;

    stats.comparisons++;

    if (courses[middle].id == targetId)
    {
        return middle;
    }

    stats.comparisons++;

    if (courses[middle].id < targetId)
    {
        return recursiveCourseSearch(
            courses,
            targetId,
            middle + 1,
            right,
            stats
        );
    }

    return recursiveCourseSearch(
        courses,
        targetId,
        left,
        middle - 1,
        stats
    );
}