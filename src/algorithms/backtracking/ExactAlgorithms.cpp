#include "algorithms/backtracking/ExactAlgorithms.h"
#include <stdexcept>

static void queensDFS(int row, int n, std::vector<int>& columns,
                      std::vector<bool>& colUsed, std::vector<bool>& diagA,
                      std::vector<bool>& diagB, QueensResult& result,
                      AlgorithmStats& stats) {
    if (row == n) {
        result.solutions++;
        if (result.firstSolution.empty()) result.firstSolution = columns;
        return;
    }
    for (int c = 0; c < n; c++) {
        stats.comparisons++;
        int a = row - c + n - 1, b = row + c;
        if (colUsed[c] || diagA[a] || diagB[b]) continue;
        columns[row] = c;
        colUsed[c] = diagA[a] = diagB[b] = true;
        stats.operations++;
        queensDFS(row + 1, n, columns, colUsed, diagA, diagB, result, stats);
        colUsed[c] = diagA[a] = diagB[b] = false;
    }
}
QueensResult ExactAlgorithms::nQueens(int n, AlgorithmStats& stats) {
    if (n < 0 || n > 13) throw std::invalid_argument("N-Queens n must be 0..13");
    QueensResult result;
    if (n == 0) { result.solutions = 1; return result; }
    std::vector<int> cols(n, -1);
    std::vector<bool> used(n, false), a(2*n-1, false), b(2*n-1, false);
    queensDFS(0, n, cols, used, a, b, result, stats);
    return result;
}

static void subsetDFS(const std::vector<int>& v, int at, long long remaining,
                      std::vector<int>& chosen, SubsetResult& result,
                      AlgorithmStats& stats) {
    stats.operations++;
    if (remaining == 0) { result.subsets.push_back(chosen); return; }
    if (at == (int)v.size() || remaining < 0) return;
    stats.comparisons++;
    if (v[at] <= remaining) {
        chosen.push_back(v[at]);
        subsetDFS(v, at+1, remaining-v[at], chosen, result, stats);
        chosen.pop_back();
    }
    subsetDFS(v, at+1, remaining, chosen, result, stats);
}
SubsetResult ExactAlgorithms::sumOfSubsets(const std::vector<int>& values,
                                            int target, AlgorithmStats& stats) {
    if (target < 0) throw std::invalid_argument("Negative target");
    for (int x : values) if (x <= 0) throw std::invalid_argument("Subset items must be positive");
    SubsetResult result;
    std::vector<int> chosen;
    subsetDFS(values, 0, target, chosen, result, stats);
    return result;
}

static void checkItems(const std::vector<ExactItem>& items, int capacity) {
    if (capacity < 0) throw std::invalid_argument("Negative capacity");
    for (const auto& x : items)
        if (x.weight <= 0 || x.value < 0)
            throw std::invalid_argument("Items need positive weights and nonnegative values");
}
static void knapsackDFS(const std::vector<ExactItem>& items, int i, int capacity,
                        int weight, int value, std::vector<int>& chosen,
                        ExactResult& result, AlgorithmStats& stats) {
    stats.operations++;
    if (i == (int)items.size()) {
        if (value > result.bestValue) {
            result.bestValue = value;
            result.selectedIds = chosen;
        }
        return;
    }
    stats.comparisons++;
    if (weight + items[i].weight <= capacity) {
        chosen.push_back(items[i].id);
        knapsackDFS(items, i+1, capacity, weight+items[i].weight,
                    value+items[i].value, chosen, result, stats);
        chosen.pop_back();
    }
    knapsackDFS(items, i+1, capacity, weight, value, chosen, result, stats);
}
ExactResult ExactAlgorithms::backtrackingKnapsack(
    const std::vector<ExactItem>& items, int capacity, AlgorithmStats& stats) {
    checkItems(items, capacity);
    ExactResult result;
    std::vector<int> chosen;
    knapsackDFS(items, 0, capacity, 0, 0, chosen, result, stats);
    return result;
}

struct SearchNode {
    int next = 0, weight = 0, value = 0;
    double bound = 0;
    std::vector<int> chosen;
};
static double upperBound(const std::vector<ExactItem>& items, int capacity,
                         const SearchNode& node) {
    if (node.weight > capacity) return -1;
    double bound = node.value;
    int remaining = capacity - node.weight;
    for (int i = node.next; i < (int)items.size(); i++) {
        if (items[i].weight <= remaining) {
            remaining -= items[i].weight;
            bound += items[i].value;
        } else {
            bound += (double)remaining * items[i].value / items[i].weight;
            break;
        }
    }
    return bound;
}
ExactResult ExactAlgorithms::branchBoundKnapsack(
    const std::vector<ExactItem>& original, int capacity,
    BoundStrategy strategy, AlgorithmStats& stats) {
    checkItems(original, capacity);
    // Manual insertion sort by decreasing value-to-weight ratio.
    std::vector<ExactItem> items = original;
    for (int i = 1; i < (int)items.size(); i++) {
        ExactItem key = items[i];
        int j = i - 1;
        while (j >= 0) {
            stats.comparisons++;
            if (1LL*items[j].value*key.weight >= 1LL*key.value*items[j].weight) break;
            items[j+1] = items[j]; j--; stats.operations++;
        }
        items[j+1] = key;
    }
    ExactResult result;
    std::vector<SearchNode> frontier(1);
    frontier[0].bound = upperBound(items, capacity, frontier[0]);
    size_t front = 0;
    while ((strategy == BoundStrategy::FIFO ? front < frontier.size() : !frontier.empty())) {
        SearchNode node;
        if (strategy == BoundStrategy::FIFO) {
            node = frontier[front++];
        } else if (strategy == BoundStrategy::LIFO) {
            node = frontier.back(); frontier.pop_back();
        } else {
            size_t best = 0;
            for (size_t i = 1; i < frontier.size(); i++) {
                stats.comparisons++;
                if (frontier[i].bound > frontier[best].bound) best = i;
            }
            node = frontier[best];
            frontier[best] = frontier.back(); frontier.pop_back();
        }
        stats.operations++;
        if (node.bound <= result.bestValue || node.next == (int)items.size()) continue;
        const ExactItem& item = items[node.next];
        SearchNode take = node;
        take.next++;
        take.weight += item.weight;
        take.value += item.value;
        take.chosen.push_back(item.id);
        if (take.weight <= capacity) {
            if (take.value > result.bestValue) {
                result.bestValue = take.value;
                result.selectedIds = take.chosen;
            }
            take.bound = upperBound(items, capacity, take);
            if (take.bound > result.bestValue && take.next < (int)items.size())
                frontier.push_back(take);
        }
        SearchNode skip = node;
        skip.next++;
        skip.bound = upperBound(items, capacity, skip);
        if (skip.bound > result.bestValue && skip.next < (int)items.size())
            frontier.push_back(skip);
    }
    return result;
}
