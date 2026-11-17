
#ifndef EXTRA_ALGORITHMS_H
#define EXTRA_ALGORITHMS_H

#include <vector>
#include <utility>
#include "analysis/AlgorithmStats.h"

struct CRTResult {
    long long solution;
    long long modulus;
    bool possible;
};

class ExtraAlgorithms {
public:
    static int fordFulkerson(
        const std::vector<std::vector<int>>& capacity,
        int source, int sink,
        AlgorithmStats& stats
    );

    static int bipartiteMatching(
        const std::vector<std::vector<int>>& compatibility,
        AlgorithmStats& stats
    );

    static CRTResult chineseRemainder(
        const std::vector<long long>& remainders,
        const std::vector<long long>& moduli,
        AlgorithmStats& stats
    );

    static int celebrity(
        const std::vector<std::vector<int>>& knows,
        AlgorithmStats& stats
    );

    static std::vector<std::vector<long long>> classicalMultiply(
        const std::vector<std::vector<long long>>& a,
        const std::vector<std::vector<long long>>& b,
        AlgorithmStats& stats
    );

    static std::vector<std::vector<long long>> strassenMultiply(
        const std::vector<std::vector<long long>>& a,
        const std::vector<std::vector<long long>>& b,
        AlgorithmStats& stats
    );
};

#endif
