#ifndef BIT_IO_H
#define BIT_IO_H

#include <fstream>
#include <cstdint>
#include<vector>
#include "decompress_H.h"

class BitWriter {
public:
    explicit BitWriter(std::ofstream& out);

    void writeBit(bool bit);
    void writeBits(const std::vector<bool>& bits);
    void flush();

private:
    std::ofstream& out;
    uint8_t buffer;
    int bitCount;
};



class BitReader {
public:
    explicit BitReader(std::ifstream& in);

    bool readBit(bool& bit);

private:
    std::ifstream& in;
    uint8_t buffer;
    int bitsLeft;
};


#endif
