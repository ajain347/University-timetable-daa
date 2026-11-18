
#include "algorithms/string_matching/StringMatching.h"
#include <stdexcept>

using namespace std;

// All four algorithms reject empty patterns.
// This gives every method the same input contract.

static void validatePattern(const string& pattern)
{
    if (pattern.empty())
        throw invalid_argument("Search pattern cannot be empty");
}

// ---------------- NAIVE MATCHING ----------------

vector<int> StringMatching::naive(
    const string& text,
    const string& pattern,
    AlgorithmStats& stats)
{
    vector<int> matches;

    int n = (int)text.size();
    int m = (int)pattern.size();

    validatePattern(pattern);

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;

        while (j < m)
        {
            stats.comparisons++;

            if (text[i + j] != pattern[j])
                break;

            j++;
        }

        if (j == m)
            matches.push_back(i);
    }

    return matches;
}

// ---------------- RABIN-KARP ----------------

vector<int> StringMatching::rabinKarp(
    const string& text,
    const string& pattern,
    AlgorithmStats& stats)
{
    vector<int> matches;

    int n = (int)text.size();
    int m = (int)pattern.size();

    validatePattern(pattern);

    if (m > n)
        return matches;

    const long long base = 256;
    const long long mod = 1000000007LL;

    long long patternHash = 0;
    long long textHash = 0;
    long long highestPower = 1;

    for (int i = 1; i < m; i++)
        highestPower = (highestPower * base) % mod;

    for (int i = 0; i < m; i++)
    {
        patternHash =
            (patternHash * base + (unsigned char)pattern[i]) % mod;

        textHash =
            (textHash * base + (unsigned char)text[i]) % mod;

        stats.operations++;
    }

    for (int i = 0; i <= n - m; i++)
    {
        stats.comparisons++;

        if (patternHash == textHash)
        {
            int j = 0;

            while (j < m)
            {
                stats.comparisons++;

                if (text[i + j] != pattern[j])
                    break;

                j++;
            }

            if (j == m)
                matches.push_back(i);
        }

        if (i < n - m)
        {
            textHash =
                (textHash -
                 (unsigned char)text[i] * highestPower % mod
                 + mod) % mod;

            textHash =
                (textHash * base +
                 (unsigned char)text[i + m]) % mod;

            stats.operations++;
        }
    }

    return matches;
}

// ---------------- FINITE AUTOMATON MATCHING ----------------

vector<int> StringMatching::finiteAutomaton(
    const string& text,
    const string& pattern,
    AlgorithmStats& stats)
{
    vector<int> matches;

    int n = (int)text.size();
    int m = (int)pattern.size();

    validatePattern(pattern);

    // Build transition table manually.
    // 256 possible byte values.
    vector<vector<int>> transition(
        m + 1, vector<int>(256, 0)
    );

    for (int state = 0; state <= m; state++)
    {
        for (int ch = 0; ch < 256; ch++)
        {
            int maxCandidate = state + 1;

            if (maxCandidate > m)
                maxCandidate = m;

            for (int candidate = maxCandidate;
                 candidate >= 1;
                 candidate--)
            {
                bool valid = true;

                for (int k = 0; k < candidate; k++)
                {
                    int position =
                        state + 1 - candidate + k;

                    unsigned char actual;

                    if (position == state)
                        actual = (unsigned char)ch;
                    else
                        actual = (unsigned char)pattern[position];

                    stats.comparisons++;

                    if (actual !=
                        (unsigned char)pattern[k])
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                {
                    transition[state][ch] = candidate;
                    break;
                }
            }

            stats.operations++;
        }
    }

    int state = 0;

    for (int i = 0; i < n; i++)
    {
        state = transition[state][
            (unsigned char)text[i]
        ];

        stats.operations++;

        if (state == m)
            matches.push_back(i - m + 1);
    }

    stats.memoryBytes =
        1LL * (m + 1) * 256 * sizeof(int);

    return matches;
}

// ---------------- KMP ----------------

vector<int> StringMatching::kmp(
    const string& text,
    const string& pattern,
    AlgorithmStats& stats)
{
    vector<int> matches;

    int n = (int)text.size();
    int m = (int)pattern.size();

    validatePattern(pattern);

    vector<int> lps(m, 0);

    // Construct LPS array manually.
    int len = 0;
    int i = 1;

    while (i < m)
    {
        stats.comparisons++;

        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else if (len != 0)
        {
            len = lps[len - 1];
        }
        else
        {
            lps[i] = 0;
            i++;
        }

        stats.operations++;
    }

    i = 0;
    int j = 0;

    while (i < n)
    {
        stats.comparisons++;

        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else if (j != 0)
        {
            j = lps[j - 1];
        }
        else
        {
            i++;
        }

        stats.operations++;

        if (j == m)
        {
            matches.push_back(i - j);
            j = lps[j - 1];
        }
    }

    stats.memoryBytes = 1LL * m * sizeof(int);

    return matches;
}
