#ifndef FREQ_H
#define FREQ_H

#include <array>
#include <cstdint>
#include <string>

void buildFrequencyTable(
    const std::string& inputFile,
    std::array<uint64_t, 256>& freq
);

#endif 
