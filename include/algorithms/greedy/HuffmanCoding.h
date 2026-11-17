
#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

#include <string>
#include <vector>
#include "analysis/AlgorithmStats.h"

struct HuffmanCode {
    char symbol;
    std::string bits;
};

class HuffmanCoding {
public:
    static std::vector<HuffmanCode> generateCodes(
        const std::string& text,
        AlgorithmStats& stats
    );

    static std::string encode(
        const std::string& text,
        const std::vector<HuffmanCode>& codes
    );
};

#endif
