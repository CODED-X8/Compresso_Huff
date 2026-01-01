#include <array>
#include <cstdint>
#include <fstream>
#include <string>
#include <stdexcept>

void buildFrequencyTable(const std::string& inputfile, std::array<uint64_t,256>& freq){
    std::ifstream in(inputfile, std::ios::binary);
    if(!in) {
        throw std::runtime_error("Failed to open file");
    }

    constexpr size_t CHUNK_SIZE = 8192;
    char buffer[CHUNK_SIZE];

    while(true){
        in.read(buffer,CHUNK_SIZE);
        std::streamsize bytesRead = in.gcount();
        if(bytesRead<=0) break;

        for(std::streamsize i=0;i<bytesRead;i++){
            uint8_t byte = static_cast<uint8_t>(buffer[i]);
            freq[byte]++;
        }
    }
}