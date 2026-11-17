
#include "algorithms/dp/DynamicProgramming.h"

#include <algorithm>
#include <climits>
#include <stdexcept>

// ---------- 0/1 KNAPSACK ----------

ZeroOneKnapsackResult DynamicProgramming::zeroOneKnapsack(
    const std::vector<KnapsackItem>& items,
    int capacity,
    AlgorithmStats& stats)
{
    if (capacity < 0)
        throw std::invalid_argument("Negative capacity");

    int n = static_cast<int>(items.size());

    for (const auto& item : items) {
        if (item.weight < 0 || item.value < 0)
            throw std::invalid_argument("Invalid knapsack item");
    }

    std::vector<std::vector<int>> dp(
        n + 1, std::vector<int>(capacity + 1, 0)
    );

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i - 1][w];

            stats.comparisons++;

            if (items[i - 1].weight <= w) {
                int candidate =
                    items[i - 1].value +
                    dp[i - 1][w - items[i - 1].weight];

                stats.comparisons++;

                if (candidate > dp[i][w])
                    dp[i][w] = candidate;
            }

            stats.operations++;
        }
    }

    ZeroOneKnapsackResult result;
    result.maxValue = dp[n][capacity];

    int w = capacity;

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            result.selectedIds.push_back(items[i - 1].id);
            w -= items[i - 1].weight;
        }
    }

    stats.memoryBytes =
        static_cast<long long>(n + 1) *
        (capacity + 1) * sizeof(int);

    return result;
}

// ---------- MATRIX CHAIN MULTIPLICATION ----------

static std::string buildParenthesization(
    const std::vector<std::vector<int>>& split,
    int i, int j)
{
    if (i == j)
        return "A" + std::to_string(i + 1);

    int k = split[i][j];

    return "(" +
        buildParenthesization(split, i, k) +
        " x " +
        buildParenthesization(split, k + 1, j) +
        ")";
}

MatrixChainResult DynamicProgramming::matrixChain(
    const std::vector<int>& dimensions,
    AlgorithmStats& stats)
{
    int n = static_cast<int>(dimensions.size()) - 1;

    if (n < 1)
        throw std::invalid_argument("At least one matrix required");

    for (int d : dimensions)
        if (d <= 0)
            throw std::invalid_argument("Invalid matrix dimension");

    std::vector<std::vector<long long>> dp(
        n, std::vector<long long>(n, 0)
    );

    std::vector<std::vector<int>> split(
        n, std::vector<int>(n, 0)
    );

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost =
                    dp[i][k] + dp[k + 1][j] +
                    1LL * dimensions[i] *
                    dimensions[k + 1] *
                    dimensions[j + 1];

                stats.comparisons++;

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }

                stats.operations++;
            }
        }
    }

    MatrixChainResult result;
    result.minMultiplications = dp[0][n - 1];
    result.parenthesization =
        buildParenthesization(split, 0, n - 1);

    stats.memoryBytes =
        1LL * n * n * (sizeof(long long) + sizeof(int));

    return result;
}

// ---------- LONGEST COMMON SUBSEQUENCE ----------

LCSResult DynamicProgramming::longestCommonSubsequence(
    const std::string& a,
    const std::string& b,
    AlgorithmStats& stats)
{
    int m = static_cast<int>(a.size());
    int n = static_cast<int>(b.size());

    std::vector<std::vector<int>> dp(
        m + 1, std::vector<int>(n + 1, 0)
    );

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            stats.comparisons++;

            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else {
                dp[i][j] =
                    dp[i - 1][j] > dp[i][j - 1]
                    ? dp[i - 1][j]
                    : dp[i][j - 1];
            }

            stats.operations++;
        }
    }

    LCSResult result;
    result.length = dp[m][n];

    std::string reversed;
    int i = m, j = n;

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            reversed += a[i - 1];
            i--;
            j--;
        }
        else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    // Reverse manually
    for (int k = static_cast<int>(reversed.size()) - 1;
         k >= 0; k--) {
        result.sequence += reversed[k];
    }

    stats.memoryBytes =
        1LL * (m + 1) * (n + 1) * sizeof(int);

    return result;
}
