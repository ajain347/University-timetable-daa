#include "algorithms/backtracking/ExactAlgorithms.h"
#include <iostream>
#include <stdexcept>

static void require(bool good, const char* message) {
    if (!good) throw std::runtime_error(message);
}
int main() {
    AlgorithmStats s;
    auto queens = ExactAlgorithms::nQueens(4, s);
    require(queens.solutions == 2, "NQueens 4 must have 2 solutions");
    s.reset();
    auto subsets = ExactAlgorithms::sumOfSubsets({3, 4, 5, 6}, 9, s);
    require(subsets.subsets.size() == 2, "Subset target 9 must have 2 solutions");
    std::vector<ExactItem> items = {{1,10,60},{2,20,100},{3,30,120}};
    s.reset();
    auto backtrack = ExactAlgorithms::backtrackingKnapsack(items, 50, s);
    require(backtrack.bestValue == 220, "Backtracking knapsack expected 220");
    for (BoundStrategy strategy : {BoundStrategy::FIFO, BoundStrategy::LIFO,
                                   BoundStrategy::BEST_BOUND}) {
        s.reset();
        auto r = ExactAlgorithms::branchBoundKnapsack(items, 50, strategy, s);
        require(r.bestValue == 220, "Branch and bound expected 220");
    }
    std::cout << "PASS: NQueens, Subsets, Backtracking Knapsack, FIFO/LIFO/Best-Bound\n";
}
