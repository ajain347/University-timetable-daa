#ifndef FAST_EXPONENTIATION_H
#define FAST_EXPONENTIATION_H

#include "analysis/AlgorithmStats.h"

class FastExponentiation
{
public:
    static long long power(
        long long base,
        int exponent,
        AlgorithmStats& stats
    );
};

#endif