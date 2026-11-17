
#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <vector>
#include "analysis/AlgorithmStats.h"

struct GraphEdge {
    int u, v, weight;
};

struct MSTResult {
    int totalWeight = 0;
    std::vector<GraphEdge> edges;
    bool connected = false;
};

class GraphAlgorithms {
public:
    static std::vector<int> dijkstra(
        const std::vector<std::vector<int>>& graph,
        int source,
        AlgorithmStats& stats
    );

    static MSTResult prim(
        const std::vector<std::vector<int>>& graph,
        AlgorithmStats& stats
    );

    static MSTResult kruskal(
        int vertices,
        std::vector<GraphEdge> edges,
        AlgorithmStats& stats
    );
};

#endif
