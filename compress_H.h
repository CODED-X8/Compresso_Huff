#ifndef compress_H
#define compress_H
#include <fstream>
#include <filesystem>
#include <array>
#include <cstdint>
#include <fstream>

void writeHeader(std::ofstream& out, uint64_t originalSize,
    const std::array<uint64_t, 256>& freq, const std::string& ext);

    void compressFile(const std::string& inputFile);

#endif
