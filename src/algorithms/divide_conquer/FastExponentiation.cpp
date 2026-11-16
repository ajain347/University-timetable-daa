#include "algorithms/divide_conquer/FastExponentiation.h"

#include <stdexcept>

long long FastExponentiation::power(long long base,int exponent,AlgorithmStats& stats)
{
    if (exponent < 0)
    {
        throw std::invalid_argument(
            "Negative exponents are not supported"
        );
    }
    if (exponent == 0)
    {
        return 1;
    }
    long long half = power(base,exponent / 2,stats);

    long long result = half * half;
    stats.operations++;

    if (exponent % 2 != 0)
    {
        result = result * base;
        stats.operations++;
    }
    return result;
}