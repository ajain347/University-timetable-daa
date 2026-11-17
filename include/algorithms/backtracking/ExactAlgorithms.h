#ifndef EXACT_ALGORITHMS_H
#define EXACT_ALGORITHMS_H
#include <vector>
#include "analysis/AlgorithmStats.h"

struct ExactItem { int id; int weight; int value; };
struct ExactResult { int bestValue = 0; std::vector<int> selectedIds; };
struct SubsetResult { std::vector<std::vector<int>> subsets; };
struct QueensResult { long long solutions = 0; std::vector<int> firstSolution; };
enum class BoundStrategy { FIFO, LIFO, BEST_BOUND };

class ExactAlgorithms {
public:
    static QueensResult nQueens(int n, AlgorithmStats& stats);
    static SubsetResult sumOfSubsets(const std::vector<int>& values, int target,
                                    AlgorithmStats& stats);
    static ExactResult backtrackingKnapsack(const std::vector<ExactItem>& items,
                                           int capacity, AlgorithmStats& stats);
    static ExactResult branchBoundKnapsack(const std::vector<ExactItem>& items,
                                          int capacity, BoundStrategy strategy,
                                          AlgorithmStats& stats);
};
#endif
