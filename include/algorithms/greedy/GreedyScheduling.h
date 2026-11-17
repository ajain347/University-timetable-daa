
#ifndef GREEDY_SCHEDULING_H
#define GREEDY_SCHEDULING_H

#include <vector>
#include "analysis/AlgorithmStats.h"

struct Activity {
    int id;
    int start;
    int finish;
};

struct ResourceRequest {
    int id;
    double value;
    double quantity;
};

struct FractionalAllocation {
    int id;
    double quantityTaken;
};

struct KnapsackResult {
    double totalValue = 0;
    std::vector<FractionalAllocation> allocations;
};

class GreedyScheduling {
public:
    static std::vector<Activity> activitySelection(
        std::vector<Activity> activities,
        AlgorithmStats& stats
    );

    static int intervalPartitioning(
        std::vector<Activity> activities,
        AlgorithmStats& stats
    );

    static KnapsackResult fractionalKnapsack(
        std::vector<ResourceRequest> requests,
        double capacity,
        AlgorithmStats& stats
    );
};

#endif
