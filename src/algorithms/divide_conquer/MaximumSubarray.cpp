#include "algorithms/divide_conquer/MaximumSubarray.h"

#include <climits>

MaxSubarrayResult MaximumSubarray::findCrossing(
    const std::vector<int>& values,
    int low,
    int mid,
    int high,
    AlgorithmStats& stats)
{
    int sum = 0;
    int leftSum = INT_MIN;
    int bestLeft = mid;

    for (int i = mid; i >= low; i--)
    {
        sum += values[i];
        stats.operations++;
        stats.comparisons++;
        if (sum > leftSum)
        {
            leftSum = sum;
            bestLeft = i;
        }
    }

    sum = 0;

    int rightSum = INT_MIN;
    int bestRight = mid + 1;

    for (int i = mid + 1; i <= high; i++)
    {
        sum += values[i];
        stats.operations++;

        stats.comparisons++;

        if (sum > rightSum)
        {
            rightSum = sum;
            bestRight = i;
        }
    }

    MaxSubarrayResult result;

    result.left = bestLeft;
    result.right = bestRight;
    result.sum = leftSum + rightSum;

    return result;
}

MaxSubarrayResult MaximumSubarray::findMaximumRecursive(
    const std::vector<int>& values,
    int low,
    int high,
    AlgorithmStats& stats)
{
    if (low == high)
    {
        return {low, high, values[low]};
    }

    int mid = low + (high - low) / 2;

    MaxSubarrayResult leftResult =
        findMaximumRecursive(values, low, mid, stats);

    MaxSubarrayResult rightResult =
        findMaximumRecursive(values, mid + 1, high, stats);

    MaxSubarrayResult crossResult =
        findCrossing(values, low, mid, high, stats);

    stats.comparisons++;

    if (leftResult.sum >= rightResult.sum &&
        leftResult.sum >= crossResult.sum)
    {
        stats.comparisons++;
        return leftResult;
    }
    stats.comparisons++;
    if (rightResult.sum >= crossResult.sum)
    {
        return rightResult;
    }
    return crossResult;
}

MaxSubarrayResult MaximumSubarray::findMaximum(
    const std::vector<int>& values,
    AlgorithmStats& stats)
{
    if (values.empty())
    {
        return {-1, -1, 0};
    }
    return findMaximumRecursive(values,0,static_cast<int>(values.size()) - 1,stats);
}