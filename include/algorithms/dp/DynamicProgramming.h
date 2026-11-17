
#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include <vector>
#include <string>
#include "analysis/AlgorithmStats.h"

struct KnapsackItem {
    int id;
    int weight;
    int value;
};

struct ZeroOneKnapsackResult {
    int maxValue = 0;
    std::vector<int> selectedIds;
};

struct MatrixChainResult {
    long long minMultiplications = 0;
    std::string parenthesization;
};

struct LCSResult {
    int length = 0;
    std::string sequence;
};

class DynamicProgramming {
public:
    static ZeroOneKnapsackResult zeroOneKnapsack(
        const std::vector<KnapsackItem>& items,
        int capacity,
        AlgorithmStats& stats
    );

    static MatrixChainResult matrixChain(
        const std::vector<int>& dimensions,
        AlgorithmStats& stats
    );

    static LCSResult longestCommonSubsequence(
        const std::string& a,
        const std::string& b,
        AlgorithmStats& stats
    );
};

#endif
