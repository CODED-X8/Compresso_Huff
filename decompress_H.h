#ifndef decompress_H
#define decompress_H

#include <fstream>
#include <array>
#include <string>
#include <cstdint>
#include <stdexcept>

struct HeaderInfo{
    uint64_t originalSize;
    std::string extension;
    std::array<uint64_t,256>freq;
};

HeaderInfo readHeader(std::ifstream& in);

void decompressFile(const std::string& inputfile);

#endif