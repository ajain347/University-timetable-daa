
#ifndef STRING_MATCHING_H
#define STRING_MATCHING_H

#include <string>
#include <vector>
#include "analysis/AlgorithmStats.h"

class StringMatching
{
public:
    static std::vector<int> naive(
        const std::string& text,
        const std::string& pattern,
        AlgorithmStats& stats
    );

    static std::vector<int> rabinKarp(
        const std::string& text,
        const std::string& pattern,
        AlgorithmStats& stats
    );

    static std::vector<int> finiteAutomaton(
        const std::string& text,
        const std::string& pattern,
        AlgorithmStats& stats
    );

    static std::vector<int> kmp(
        const std::string& text,
        const std::string& pattern,
        AlgorithmStats& stats
    );
};

#endif
