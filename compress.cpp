#include <filesystem>
#include <array>
#include <cstdint>
#include <fstream>
#include "compress_H.h"
#include <string>
#include "frequency_table_H.h"
#include "huffman_H.h"
#include "BIT_IO_H.h"

void writeHeader(std::ofstream& out, uint64_t originalSize,
    const std::array<uint64_t, 256>& freq, const std::string& ext){
        const char magic[4] = {'H','U','F','1'};
        out.write(magic,4);

        //orginal size
        out.write(reinterpret_cast<const char*>(&originalSize), sizeof(originalSize));
        //writing extension name
        uint32_t extLen = static_cast<uint32_t>(ext.size());
        out.write(reinterpret_cast<const char*>(&extLen),sizeof(extLen));
        out.write(ext.data(),extLen);


        //freq table
        for(uint64_t f: freq){
            out.write(reinterpret_cast<const char*>(&f), sizeof(f));
        }
    }

void compressFile(const std::string& inputFile){
    std::string outputfile,ext;
    std::filesystem::path file(inputFile);
    ext = file.extension().string();
    std::filesystem::path outPath = file.parent_path() / (file.stem().string() + "_compressed");

    std::string outputFile = outPath.string();




    //Build freq table
    std::array<uint64_t,256> freq{};
    buildFrequencyTable(inputFile, freq);

    //Build HuffMan Tree
    HuffmanNode* root = buildHuffmanTree(freq);

    //Generate Codes
    std::array<HuffmanCode, 256> codes;
    generateCodes(root, codes);

    //Opening output file
    std::ofstream out(outputFile,std::ios::binary);
    if(!out){
        freeTree(root);
        throw std::runtime_error("Filed to open output file.\n");
    }

    //writer Header
    uint64_t originalSizeip = std::filesystem::file_size(inputFile);
    writeHeader(out, originalSizeip, freq, ext);

    //prepare bitwriter
    BitWriter bw(out);

    //opening input file
    std::ifstream in(inputFile, std::ios::binary);
    if(!in){
        freeTree(root);
        throw std::runtime_error("Failed to open file.\n");
    }

    //compression pass
    constexpr size_t CHUNK_SIZE = 8192;
    char buffer[CHUNK_SIZE];

    while(true){
        in.read(buffer,CHUNK_SIZE);
        std::streamsize bytesRead = in.gcount();
        if(bytesRead<=0) break;
        
        for(std::streamsize i =0;i<bytesRead;i++){
            uint8_t byte = static_cast<uint8_t>(buffer[i]);
            bw.writeBits(codes[byte]);
        }
    }

    bw.flush();

    freeTree(root);

}