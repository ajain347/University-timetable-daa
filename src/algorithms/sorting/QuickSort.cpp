#include "algorithms/sorting/QuickSort.h"

void QuickSort::sortCoursesById(
    std::vector<Course>& courses,
    AlgorithmStats& stats)
{
    if (courses.empty())
    {
        return;
    }

    quickSort(courses,0,static_cast<int>(courses.size()) - 1,stats);
}

void QuickSort::quickSort(
    std::vector<Course>& courses,
    int low,
    int high,
    AlgorithmStats& stats)
{
    if (low >= high)
    {
        return;
    }
    int pivotIndex = partition(courses,low,high,stats);
    quickSort(courses,low,pivotIndex - 1,stats);
    quickSort(courses,pivotIndex + 1,high,stats);
}

void QuickSort::swapCourses(
    Course& a,
    Course& b,
    AlgorithmStats& stats)
{
    Course temp = a;
    a = b;
    b = temp;
    stats.operations += 3;
}

int QuickSort::partition(
    std::vector<Course>& courses,
    int low,
    int high,
    AlgorithmStats& stats)
{
    int pivotId = courses[high].id;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        stats.comparisons++;
        if (courses[j].id <= pivotId)
        {
            i++;
            swapCourses(courses[i],courses[j],stats);
        }
    }
    swapCourses(courses[i + 1],courses[high],stats);
    return i + 1;
}