#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <array>
#include <vector>
#include <cstdint>

#include "huffman_node.h"

using HuffmanCode = std::vector<bool>;


HuffmanNode* buildHuffmanTree(
    const std::array<uint64_t, 256>& freq
);

void generateCodes(
    HuffmanNode* root,
    std::array<HuffmanCode, 256>& codes
);

void dfsGenerate(
    HuffmanNode* node,
    std::vector<bool>& path,
    std::array<HuffmanCode, 256>& codes
);

void freeTree(HuffmanNode* node);

#endif // HUFFMAN_TREE_H
