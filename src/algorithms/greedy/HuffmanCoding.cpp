
#include "algorithms/greedy/HuffmanCoding.h"
#include <stdexcept>

struct HuffmanNode {
    unsigned char symbol;
    int frequency;
    int left;
    int right;
};

static void buildCodes(
    const std::vector<HuffmanNode>& nodes,
    int index,
    const std::string& prefix,
    std::vector<HuffmanCode>& codes)
{
    const HuffmanNode& node = nodes[index];

    if (node.left == -1 && node.right == -1) {
        codes.push_back({
            (char)node.symbol,
            prefix.empty() ? "0" : prefix
        });
        return;
    }

    buildCodes(nodes, node.left, prefix + "0", codes);
    buildCodes(nodes, node.right, prefix + "1", codes);
}

std::vector<HuffmanCode> HuffmanCoding::generateCodes(
    const std::string& text,
    AlgorithmStats& stats)
{
    int frequency[256] = {0};

    for (unsigned char c : text) {
        frequency[c]++;
        stats.operations++;
    }

    std::vector<HuffmanNode> nodes;
    std::vector<int> active;

    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            nodes.push_back({
                (unsigned char)i,
                frequency[i], -1, -1
            });
            active.push_back((int)nodes.size() - 1);
        }
    }

    if (active.empty())
        return {};

    while (active.size() > 1) {
        int first = -1;
        int second = -1;

        // Find two nodes with minimum frequency
        for (int index : active) {
            stats.comparisons++;

            if (first == -1 ||
                nodes[index].frequency < nodes[first].frequency) {
                second = first;
                first = index;
            }
            else if (second == -1 ||
                     nodes[index].frequency < nodes[second].frequency) {
                second = index;
            }
        }

        int combined = (int)nodes.size();

        nodes.push_back({
            0,
            nodes[first].frequency + nodes[second].frequency,
            first,
            second
        });

        std::vector<int> remaining;

        for (int index : active) {
            if (index != first && index != second)
                remaining.push_back(index);
        }

        remaining.push_back(combined);
        active = remaining;
        stats.operations++;
    }

    std::vector<HuffmanCode> codes;
    buildCodes(nodes, active[0], "", codes);

    return codes;
}

std::string HuffmanCoding::encode(
    const std::string& text,
    const std::vector<HuffmanCode>& codes)
{
    std::string result;

    for (unsigned char c : text) {
        bool found = false;

        for (const HuffmanCode& code : codes) {
            if ((unsigned char)code.symbol == c) {
                result += code.bits;
                found = true;
                break;
            }
        }

        if (!found)
            throw std::invalid_argument("Missing Huffman code");
    }

    return result;
}
