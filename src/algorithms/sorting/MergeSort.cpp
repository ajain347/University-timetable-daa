#include "algorithms/sorting/MergeSort.h"

void MergeSort::sortCoursesById(
    std::vector<Course>& courses,
    AlgorithmStats& stats)
{
    if (courses.empty())
    {
        return;
    }
    mergeSort(courses,0,courses.size() - 1,stats);
}

void MergeSort::mergeSort(
    std::vector<Course>& courses,
    int left,
    int right,
    AlgorithmStats& stats)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;

    mergeSort(courses,left,mid,stats);
    mergeSort(courses,mid + 1,right,stats);
    merge(courses,left,mid,right,stats);
}

void MergeSort::merge(
    std::vector<Course>& courses,
    int left,
    int mid,
    int right,
    AlgorithmStats& stats)
{
    std::vector<Course> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        stats.comparisons++;
        if (courses[i].id <= courses[j].id)
        {
            temp.push_back(courses[i]);
            i++;
        }
        else
        {
            temp.push_back(courses[j]);
            j++;
        }
        stats.operations++;
    }

    while (i <= mid)
    {
        temp.push_back(courses[i]);
        i++;
        stats.operations++;
    }

    while (j <= right)
    {
        temp.push_back(courses[j]);
        j++;
        stats.operations++;
    }

    for (int k = 0; k < static_cast<int>(temp.size()); k++)
    {
        courses[left + k] = temp[k];
        stats.operations++;
    }
    stats.memoryBytes += temp.size() * sizeof(Course);
}