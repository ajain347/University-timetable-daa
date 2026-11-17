
#include "algorithms/greedy/GreedyScheduling.h"
#include <stdexcept>

// Sort activities by finishing time
static void sortByFinish(std::vector<Activity>& a,
                         AlgorithmStats& stats)
{
    for (int i = 1; i < (int)a.size(); i++)
    {
        Activity key = a[i];
        int j = i - 1;

        while (j >= 0)
        {
            stats.comparisons++;
            if (a[j].finish <= key.finish)
                break;

            a[j + 1] = a[j];
            stats.operations++;
            j--;
        }

        a[j + 1] = key;
        stats.operations++;
    }
}

// Sort activities by starting time
static void sortByStart(std::vector<Activity>& a,
                        AlgorithmStats& stats)
{
    for (int i = 1; i < (int)a.size(); i++)
    {
        Activity key = a[i];
        int j = i - 1;

        while (j >= 0)
        {
            stats.comparisons++;
            if (a[j].start <= key.start)
                break;

            a[j + 1] = a[j];
            stats.operations++;
            j--;
        }

        a[j + 1] = key;
        stats.operations++;
    }
}

// Activity selection: maximum non-overlapping activities
std::vector<Activity> GreedyScheduling::activitySelection(
    std::vector<Activity> activities,
    AlgorithmStats& stats)
{
    for (const Activity& a : activities)
        if (a.start >= a.finish)
            throw std::invalid_argument("Invalid activity interval");

    sortByFinish(activities, stats);

    std::vector<Activity> selected;
    int lastFinish = 0;
    bool first = true;

    for (const Activity& a : activities)
    {
        stats.comparisons++;

        if (first || a.start >= lastFinish)
        {
            selected.push_back(a);
            lastFinish = a.finish;
            first = false;
            stats.operations++;
        }
    }

    return selected;
}

// Interval partitioning: minimum number of rooms
int GreedyScheduling::intervalPartitioning(
    std::vector<Activity> activities,
    AlgorithmStats& stats)
{
    for (const Activity& a : activities)
        if (a.start >= a.finish)
            throw std::invalid_argument("Invalid activity interval");

    sortByStart(activities, stats);

    std::vector<int> roomEndTimes;

    for (const Activity& a : activities)
    {
        bool assigned = false;

        for (int& endTime : roomEndTimes)
        {
            stats.comparisons++;

            if (endTime <= a.start)
            {
                endTime = a.finish;
                assigned = true;
                stats.operations++;
                break;
            }
        }

        if (!assigned)
        {
            roomEndTimes.push_back(a.finish);
            stats.operations++;
        }
    }

    return (int)roomEndTimes.size();
}

// Fractional knapsack: allocate divisible resources
KnapsackResult GreedyScheduling::fractionalKnapsack(
    std::vector<ResourceRequest> requests,
    double capacity,
    AlgorithmStats& stats)
{
    if (capacity < 0)
        throw std::invalid_argument("Negative capacity");

    for (const ResourceRequest& r : requests)
        if (r.quantity <= 0 || r.value < 0)
            throw std::invalid_argument("Invalid resource request");

    // Manual insertion sort by value/quantity ratio
    for (int i = 1; i < (int)requests.size(); i++)
    {
        ResourceRequest key = requests[i];
        int j = i - 1;

        while (j >= 0)
        {
            stats.comparisons++;

            double leftRatio =
                requests[j].value / requests[j].quantity;

            double keyRatio = key.value / key.quantity;

            if (leftRatio >= keyRatio)
                break;

            requests[j + 1] = requests[j];
            stats.operations++;
            j--;
        }

        requests[j + 1] = key;
        stats.operations++;
    }

    KnapsackResult result;

    for (const ResourceRequest& r : requests)
    {
        if (capacity <= 0)
            break;

        double taken = r.quantity;

        if (taken > capacity)
            taken = capacity;

        result.totalValue +=
            (taken / r.quantity) * r.value;

        result.allocations.push_back({r.id, taken});
        capacity -= taken;
        stats.operations++;
    }

    return result;
}
