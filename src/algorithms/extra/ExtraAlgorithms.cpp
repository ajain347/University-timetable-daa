
#include "algorithms/extra/ExtraAlgorithms.h"
#include <stdexcept>
#include <climits>

using Matrix = std::vector<std::vector<long long>>;

// ---------------- FORD-FULKERSON ----------------

int ExtraAlgorithms::fordFulkerson(
    const std::vector<std::vector<int>>& capacity,
    int source, int sink,
    AlgorithmStats& stats)
{
    int n = (int)capacity.size();

    if (n == 0 || source < 0 || sink < 0 ||
        source >= n || sink >= n || source == sink)
        throw std::invalid_argument("Invalid flow network");

    for (const auto& row : capacity) {
        if ((int)row.size() != n)
            throw std::invalid_argument("Non-square capacity matrix");

        for (int c : row)
            if (c < 0)
                throw std::invalid_argument("Negative capacity");
    }

    std::vector<std::vector<int>> residual = capacity;
    int maxFlow = 0;

    while (true)
    {
        std::vector<int> parent(n, -1);
        std::vector<int> queue(n);

        int front = 0, back = 0;
        queue[back++] = source;
        parent[source] = source;

        while (front < back && parent[sink] == -1)
        {
            int u = queue[front++];

            for (int v = 0; v < n; v++)
            {
                stats.comparisons++;

                if (parent[v] == -1 && residual[u][v] > 0)
                {
                    parent[v] = u;
                    queue[back++] = v;
                }
            }
        }

        if (parent[sink] == -1)
            break;

        int flow = INT_MAX;

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            if (residual[u][v] < flow)
                flow = residual[u][v];
        }

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            residual[u][v] -= flow;
            residual[v][u] += flow;
            stats.operations++;
        }

        if (flow > INT_MAX - maxFlow)
            throw std::overflow_error("Maximum flow overflow");

        maxFlow += flow;
    }

    return maxFlow;
}

// ---------------- BIPARTITE MATCHING ----------------

static bool augment(
    int u,
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    std::vector<int>& matched,
    AlgorithmStats& stats)
{
    int rightCount = (int)matched.size();

    for (int v = 0; v < rightCount; v++)
    {
        stats.comparisons++;

        if (graph[u][v] && !visited[v])
        {
            visited[v] = true;

            if (matched[v] == -1 ||
                augment(matched[v], graph, visited, matched, stats))
            {
                matched[v] = u;
                stats.operations++;
                return true;
            }
        }
    }

    return false;
}

int ExtraAlgorithms::bipartiteMatching(
    const std::vector<std::vector<int>>& compatibility,
    AlgorithmStats& stats)
{
    int leftCount = (int)compatibility.size();
    if (leftCount == 0) return 0;

    int rightCount = (int)compatibility[0].size();

    for (const auto& row : compatibility) {
        if ((int)row.size() != rightCount)
            throw std::invalid_argument("Invalid matching matrix");
    }

    std::vector<int> matched(rightCount, -1);
    int result = 0;

    for (int u = 0; u < leftCount; u++)
    {
        std::vector<bool> visited(rightCount, false);

        if (augment(u, compatibility, visited, matched, stats))
            result++;
    }

    return result;
}

// ---------------- CHINESE REMAINDER THEOREM ----------------

static long long gcdManual(long long a, long long b)
{
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static long long extendedGCD(
    long long a, long long b,
    long long& x, long long& y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long g = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

CRTResult ExtraAlgorithms::chineseRemainder(
    const std::vector<long long>& remainders,
    const std::vector<long long>& moduli,
    AlgorithmStats& stats)
{
    int n = (int)moduli.size();

    if (n == 0 || remainders.size() != moduli.size())
        throw std::invalid_argument("Invalid CRT input");

    long long product = 1;

    for (int i = 0; i < n; i++)
    {
        if (moduli[i] <= 1)
            throw std::invalid_argument("Invalid modulus");

        for (int j = 0; j < i; j++)
            if (gcdManual(moduli[i], moduli[j]) != 1)
                return {0, 0, false};

        if (product > LLONG_MAX / moduli[i])
            throw std::overflow_error("CRT modulus overflow");

        product *= moduli[i];
    }

    // Use modular arithmetic to reduce intermediate terms.
    // __int128 is supported by Apple Clang and GCC.
    __int128 answer = 0;

    for (int i = 0; i < n; i++)
    {
        long long partial = product / moduli[i];
        long long x, y;

        extendedGCD(partial, moduli[i], x, y);

        long long inverse =
            (x % moduli[i] + moduli[i]) % moduli[i];

        long long remainder =
            (remainders[i] % moduli[i] + moduli[i]) % moduli[i];

        __int128 term =
            (__int128)remainder * partial * inverse;

        answer = (answer + term) % product;
        stats.operations++;
    }

    return {(long long)answer, product, true};
}

// ---------------- CELEBRITY IDENTIFICATION ----------------

int ExtraAlgorithms::celebrity(
    const std::vector<std::vector<int>>& knows,
    AlgorithmStats& stats)
{
    int n = (int)knows.size();
    if (n == 0) return -1;

    for (const auto& row : knows)
        if ((int)row.size() != n)
            throw std::invalid_argument("Invalid relationship matrix");

    int candidate = 0;

    for (int i = 1; i < n; i++)
    {
        stats.comparisons++;

        if (knows[candidate][i])
            candidate = i;
    }

    for (int i = 0; i < n; i++)
    {
        if (i == candidate) continue;

        stats.comparisons += 2;

        if (knows[candidate][i] ||
            !knows[i][candidate])
            return -1;
    }

    return candidate;
}

// ---------------- MATRIX UTILITIES ----------------

static Matrix addMatrix(const Matrix& a, const Matrix& b, int sign)
{
    int n = (int)a.size();
    Matrix result(n, std::vector<long long>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = a[i][j] + sign * b[i][j];

    return result;
}

static Matrix classicalSquare(
    const Matrix& a, const Matrix& b,
    AlgorithmStats& stats)
{
    int n = (int)a.size();
    Matrix c(n, std::vector<long long>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
                stats.operations++;
            }

    return c;
}

std::vector<std::vector<long long>>
ExtraAlgorithms::classicalMultiply(
    const Matrix& a, const Matrix& b,
    AlgorithmStats& stats)
{
    int n = (int)a.size();
    if (n == 0) return {};

    int k = (int)a[0].size();
    if (k == 0 || (int)b.size() != k)
        throw std::invalid_argument("Invalid matrix dimensions");

    int m = (int)b[0].size();

    for (const auto& row : a)
        if ((int)row.size() != k)
            throw std::invalid_argument("Invalid matrix A");

    for (const auto& row : b)
        if ((int)row.size() != m)
            throw std::invalid_argument("Invalid matrix B");

    Matrix result(n, std::vector<long long>(m, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int t = 0; t < k; t++)
            {
                result[i][j] += a[i][t] * b[t][j];
                stats.operations++;
            }

    return result;
}

// ---------------- STRASSEN ----------------

static Matrix strassenRecursive(
    const Matrix& a, const Matrix& b,
    AlgorithmStats& stats)
{
    int n = (int)a.size();

    if (n <= 2)
        return classicalSquare(a, b, stats);

    int h = n / 2;

    Matrix a11(h, std::vector<long long>(h));
    Matrix a12 = a11, a21 = a11, a22 = a11;
    Matrix b11 = a11, b12 = a11, b21 = a11, b22 = a11;

    for (int i = 0; i < h; i++)
        for (int j = 0; j < h; j++)
        {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + h];
            a21[i][j] = a[i + h][j];
            a22[i][j] = a[i + h][j + h];

            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + h];
            b21[i][j] = b[i + h][j];
            b22[i][j] = b[i + h][j + h];
        }

    Matrix m1 = strassenRecursive(
        addMatrix(a11, a22, 1),
        addMatrix(b11, b22, 1), stats);

    Matrix m2 = strassenRecursive(
        addMatrix(a21, a22, 1), b11, stats);

    Matrix m3 = strassenRecursive(
        a11, addMatrix(b12, b22, -1), stats);

    Matrix m4 = strassenRecursive(
        a22, addMatrix(b21, b11, -1), stats);

    Matrix m5 = strassenRecursive(
        addMatrix(a11, a12, 1), b22, stats);

    Matrix m6 = strassenRecursive(
        addMatrix(a21, a11, -1),
        addMatrix(b11, b12, 1), stats);

    Matrix m7 = strassenRecursive(
        addMatrix(a12, a22, -1),
        addMatrix(b21, b22, 1), stats);

    Matrix c11 = addMatrix(
        addMatrix(addMatrix(m1, m4, 1), m5, -1),
        m7, 1);

    Matrix c12 = addMatrix(m3, m5, 1);
    Matrix c21 = addMatrix(m2, m4, 1);

    Matrix c22 = addMatrix(
        addMatrix(addMatrix(m1, m2, -1), m3, 1),
        m6, 1);

    Matrix c(n, std::vector<long long>(n, 0));

    for (int i = 0; i < h; i++)
        for (int j = 0; j < h; j++)
        {
            c[i][j] = c11[i][j];
            c[i][j + h] = c12[i][j];
            c[i + h][j] = c21[i][j];
            c[i + h][j + h] = c22[i][j];
        }

    return c;
}

std::vector<std::vector<long long>>
ExtraAlgorithms::strassenMultiply(
    const Matrix& a, const Matrix& b,
    AlgorithmStats& stats)
{
    int rowsA = (int)a.size();
    if (rowsA == 0) return {};

    int colsA = (int)a[0].size();
    int rowsB = (int)b.size();

    if (colsA == 0 || colsA != rowsB)
        throw std::invalid_argument("Invalid dimensions");

    int colsB = (int)b[0].size();

    for (const auto& row : a)
        if ((int)row.size() != colsA)
            throw std::invalid_argument("Invalid A");

    for (const auto& row : b)
        if ((int)row.size() != colsB)
            throw std::invalid_argument("Invalid B");

    int size = 1;

    while (size < rowsA ||
           size < colsA ||
           size < colsB)
        size *= 2;

    Matrix paddedA(size, std::vector<long long>(size, 0));
    Matrix paddedB(size, std::vector<long long>(size, 0));

    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsA; j++)
            paddedA[i][j] = a[i][j];

    for (int i = 0; i < rowsB; i++)
        for (int j = 0; j < colsB; j++)
            paddedB[i][j] = b[i][j];

    Matrix paddedC = strassenRecursive(
        paddedA, paddedB, stats);

    Matrix result(rowsA, std::vector<long long>(colsB));

    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsB; j++)
            result[i][j] = paddedC[i][j];

    return result;
}
