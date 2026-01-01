#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <cstdint>

struct HuffmanNode {
    uint8_t byte;
    uint64_t freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(uint8_t b, uint64_t f)
        : byte(b), freq(f), left(nullptr), right(nullptr) {}

    HuffmanNode(HuffmanNode* l, HuffmanNode* r)
        : byte(0), freq(l->freq + r->freq), left(l), right(r) {}
};

struct Compare {
    bool operator()(const HuffmanNode* a,
                    const HuffmanNode* b) const {
        return a->freq > b->freq;
    }
};

#endif
