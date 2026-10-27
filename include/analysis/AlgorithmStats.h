#ifndef ALGORITHM_STATS_H
#define ALGORITHM_STATS_H

struct AlgorithmStats {
    long long comparisons;
    long long operations;
    long long memoryBytes;
    double executionTimeMs;

    AlgorithmStats()
        : comparisons(0),
          operations(0),
          memoryBytes(0),
          executionTimeMs(0.0)
    {
    }
    void reset()
    {
        comparisons = 0;
        operations = 0;
        memoryBytes = 0;
        executionTimeMs = 0.0;
    }
};

#endif