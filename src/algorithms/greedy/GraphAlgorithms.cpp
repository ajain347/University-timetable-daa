
#include "algorithms/greedy/GraphAlgorithms.h"
#include <climits>
#include <stdexcept>

static void validateGraph(
    const std::vector<std::vector<int>>& g)
{
    int n = (int)g.size();

    for (const auto& row : g) {
        if ((int)row.size() != n)
            throw std::invalid_argument("Graph must be square");

        for (int w : row)
            if (w < 0)
                throw std::invalid_argument("Negative edge weight");
    }
}

std::vector<int> GraphAlgorithms::dijkstra(
    const std::vector<std::vector<int>>& graph,
    int source,
    AlgorithmStats& stats)
{
    validateGraph(graph);
    int n = (int)graph.size();

    if (source < 0 || source >= n)
        throw std::invalid_argument("Invalid source");

    std::vector<int> dist(n, INT_MAX);
    std::vector<bool> visited(n, false);
    dist[source] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;

        for (int j = 0; j < n; j++) {
            stats.comparisons++;
            if (!visited[j] &&
                (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        if (u == -1 || dist[u] == INT_MAX)
            break;

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 && !visited[v] &&
                dist[u] <= INT_MAX - graph[u][v]) {

                stats.comparisons++;

                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    stats.operations++;
                }
            }
        }
    }

    return dist;
}

MSTResult GraphAlgorithms::prim(
    const std::vector<std::vector<int>>& graph,
    AlgorithmStats& stats)
{
    validateGraph(graph);
    int n = (int)graph.size();
    MSTResult result;

    if (n == 0) {
        result.connected = true;
        return result;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (graph[i][j] != graph[j][i])
                throw std::invalid_argument("MST needs undirected graph");

    std::vector<int> key(n, INT_MAX);
    std::vector<int> parent(n, -1);
    std::vector<bool> inMST(n, false);
    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;

        for (int v = 0; v < n; v++) {
            stats.comparisons++;
            if (!inMST[v] &&
                (u == -1 || key[v] < key[u]))
                u = v;
        }

        if (u == -1 || key[u] == INT_MAX)
            break;

        inMST[u] = true;

        if (parent[u] != -1) {
            result.edges.push_back(
                {parent[u], u, key[u]}
            );
            result.totalWeight += key[u];
        }

        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 && !inMST[v]) {
                stats.comparisons++;

                if (graph[u][v] < key[v]) {
                    key[v] = graph[u][v];
                    parent[v] = u;
                    stats.operations++;
                }
            }
        }
    }

    result.connected =
        (int)result.edges.size() == n - 1;

    return result;
}

static int findRoot(std::vector<int>& parent, int x)
{
    if (parent[x] != x)
        parent[x] = findRoot(parent, parent[x]);

    return parent[x];
}

static bool unite(
    std::vector<int>& parent,
    std::vector<int>& rank,
    int a, int b)
{
    a = findRoot(parent, a);
    b = findRoot(parent, b);

    if (a == b)
        return false;

    if (rank[a] < rank[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;

    if (rank[a] == rank[b])
        rank[a]++;

    return true;
}

MSTResult GraphAlgorithms::kruskal(
    int vertices,
    std::vector<GraphEdge> edges,
    AlgorithmStats& stats)
{
    if (vertices < 0)
        throw std::invalid_argument("Invalid vertex count");

    for (const auto& e : edges)
        if (e.u < 0 || e.v < 0 ||
            e.u >= vertices || e.v >= vertices ||
            e.weight < 0)
            throw std::invalid_argument("Invalid edge");

    // Manual insertion sort by edge weight
    for (int i = 1; i < (int)edges.size(); i++) {
        GraphEdge key = edges[i];
        int j = i - 1;

        while (j >= 0) {
            stats.comparisons++;

            if (edges[j].weight <= key.weight)
                break;

            edges[j + 1] = edges[j];
            j--;
            stats.operations++;
        }

        edges[j + 1] = key;
    }

    std::vector<int> parent(vertices);
    std::vector<int> rank(vertices, 0);

    for (int i = 0; i < vertices; i++)
        parent[i] = i;

    MSTResult result;

    for (const auto& e : edges) {
        if (unite(parent, rank, e.u, e.v)) {
            result.edges.push_back(e);
            result.totalWeight += e.weight;
            stats.operations++;

            if ((int)result.edges.size() == vertices - 1)
                break;
        }
    }

    result.connected =
        vertices == 0 ||
        (int)result.edges.size() == vertices - 1;

    return result;
}
