
#include "algorithms/dp/AdvancedDP.h"
#include <climits>
#include <stdexcept>

static const long long INF = LLONG_MAX / 4;

// ---------- OPTIMAL BINARY SEARCH TREE ----------
// Keys are assumed to be in sorted order.
// Frequencies represent successful search counts.

long long AdvancedDP::optimalBST(
    const std::vector<int>& freq,
    AlgorithmStats& stats)
{
    int n = (int)freq.size();
    if (n == 0) return 0;

    for (int f : freq)
        if (f < 0)
            throw std::invalid_argument("Negative frequency");

    std::vector<std::vector<long long>> dp(
        n, std::vector<long long>(n, 0));

    std::vector<long long> prefix(n + 1, 0);

    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + freq[i];

    for (int length = 1; length <= n; length++)
    {
        for (int i = 0; i + length <= n; i++)
        {
            int j = i + length - 1;
            long long sum = prefix[j + 1] - prefix[i];

            dp[i][j] = INF;

            for (int root = i; root <= j; root++)
            {
                long long left =
                    root > i ? dp[i][root - 1] : 0;

                long long right =
                    root < j ? dp[root + 1][j] : 0;

                long long cost = left + right + sum;

                stats.comparisons++;

                if (cost < dp[i][j])
                    dp[i][j] = cost;

                stats.operations++;
            }
        }
    }

    stats.memoryBytes =
        1LL * n * n * sizeof(long long)
        + 1LL * (n + 1) * sizeof(long long);

    return dp[0][n - 1];
}

// ---------- BELLMAN-FORD ----------

std::vector<long long> AdvancedDP::bellmanFord(
    int vertices,
    const std::vector<WeightedEdge>& edges,
    int source,
    AlgorithmStats& stats)
{
    if (vertices <= 0 || source < 0 || source >= vertices)
        throw std::invalid_argument("Invalid graph/source");

    for (const auto& e : edges)
        if (e.from < 0 || e.from >= vertices ||
            e.to < 0 || e.to >= vertices)
            throw std::invalid_argument("Invalid edge");

    std::vector<long long> dist(vertices, INF);
    dist[source] = 0;

    for (int i = 1; i < vertices; i++)
    {
        bool changed = false;

        for (const auto& e : edges)
        {
            stats.comparisons++;

            if (dist[e.from] != INF &&
                dist[e.from] + e.weight < dist[e.to])
            {
                dist[e.to] = dist[e.from] + e.weight;
                changed = true;
                stats.operations++;
            }
        }

        if (!changed) break;
    }

    for (const auto& e : edges)
    {
        if (dist[e.from] != INF &&
            dist[e.from] + e.weight < dist[e.to])
        {
            throw std::runtime_error(
                "Reachable negative cycle detected");
        }
    }

    stats.memoryBytes = 1LL * vertices * sizeof(long long);
    return dist;
}

// ---------- FLOYD-WARSHALL ----------
// Matrix convention: -1 means no edge;
// diagonal is zero. Negative edges are allowed.

std::vector<std::vector<long long>>
AdvancedDP::floydWarshall(
    const std::vector<std::vector<int>>& graph,
    AlgorithmStats& stats)
{
    int n = (int)graph.size();

    std::vector<std::vector<long long>> dist(
        n, std::vector<long long>(n, INF));

    for (int i = 0; i < n; i++)
    {
        if ((int)graph[i].size() != n)
            throw std::invalid_argument("Non-square matrix");

        for (int j = 0; j < n; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else if (graph[i][j] != -1)
                dist[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] == INF ||
                    dist[k][j] == INF)
                    continue;

                stats.comparisons++;

                long long candidate =
                    dist[i][k] + dist[k][j];

                if (candidate < dist[i][j])
                {
                    dist[i][j] = candidate;
                    stats.operations++;
                }
            }

    for (int i = 0; i < n; i++)
        if (dist[i][i] < 0)
            throw std::runtime_error(
                "Negative cycle detected");

    stats.memoryBytes = 1LL * n * n * sizeof(long long);
    return dist;
}

// ---------- TSP USING BITMASK DP ----------
// -1 represents a missing edge.
// Start and finish at vertex 0.

TSPResult AdvancedDP::travellingSalesperson(
    const std::vector<std::vector<int>>& graph,
    AlgorithmStats& stats)
{
    int n = (int)graph.size();

    if (n == 0) return {0, true};

    if (n > 15)
        throw std::invalid_argument(
            "TSP limited to 15 vertices");

    for (const auto& row : graph)
    {
        if ((int)row.size() != n)
            throw std::invalid_argument("Non-square graph");

        for (int w : row)
            if (w < -1)
                throw std::invalid_argument("Invalid edge weight");
    }

    if (n == 1) return {0, true};

    int states = 1 << n;

    std::vector<std::vector<long long>> dp(
        states, std::vector<long long>(n, INF));

    dp[1][0] = 0;

    for (int mask = 1; mask < states; mask++)
    {
        if (!(mask & 1)) continue;

        for (int u = 0; u < n; u++)
        {
            if (dp[mask][u] == INF) continue;

            for (int v = 1; v < n; v++)
            {
                if ((mask & (1 << v)) ||
                    graph[u][v] == -1)
                    continue;

                int nextMask = mask | (1 << v);

                long long cost =
                    dp[mask][u] + graph[u][v];

                stats.comparisons++;

                if (cost < dp[nextMask][v])
                {
                    dp[nextMask][v] = cost;
                    stats.operations++;
                }
            }
        }
    }

    long long best = INF;
    int fullMask = states - 1;

    for (int u = 1; u < n; u++)
    {
        if (dp[fullMask][u] == INF ||
            graph[u][0] == -1)
            continue;

        long long cost =
            dp[fullMask][u] + graph[u][0];

        if (cost < best)
            best = cost;
    }

    stats.memoryBytes =
        1LL * states * n * sizeof(long long);

    if (best == INF)
        return {0, false};

    return {best, true};
}
