#ifndef MAXIMUM_SUBARRAY_H
#define MAXIMUM_SUBARRAY_H

#include <vector>
#include "analysis/AlgorithmStats.h"

struct MaxSubarrayResult
{
    int left;
    int right;
    int sum;
};

class MaximumSubarray
{
public:
    static MaxSubarrayResult findMaximum(
        const std::vector<int>& values,
        AlgorithmStats& stats
    );

private:
    static MaxSubarrayResult findMaximumRecursive(
        const std::vector<int>& values,
        int low,
        int high,
        AlgorithmStats& stats
    );

    static MaxSubarrayResult findCrossing(
        const std::vector<int>& values,
        int low,
        int mid,
        int high,
        AlgorithmStats& stats
    );
};

#endif