
#ifndef ADVANCED_DP_H
#define ADVANCED_DP_H

#include <vector>
#include "analysis/AlgorithmStats.h"

struct WeightedEdge {
    int from, to, weight;
};

struct TSPResult {
    long long cost;
    bool feasible;
};

class AdvancedDP {
public:
    static long long optimalBST(
        const std::vector<int>& frequencies,
        AlgorithmStats& stats
    );

    static std::vector<long long> bellmanFord(
        int vertices,
        const std::vector<WeightedEdge>& edges,
        int source,
        AlgorithmStats& stats
    );

    static std::vector<std::vector<long long>> floydWarshall(
        const std::vector<std::vector<int>>& graph,
        AlgorithmStats& stats
    );

    static TSPResult travellingSalesperson(
        const std::vector<std::vector<int>>& graph,
        AlgorithmStats& stats
    );
};

#endif
