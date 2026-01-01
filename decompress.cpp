#include <fstream>
#include <array>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <filesystem>
#include "huffman_H.h"
#include "BIT_IO_H.h"
#include "huffman_node.h"
#include "decompress_H.h"



HeaderInfo readHeader(std::ifstream& in){
    HeaderInfo header{};

    char magic[4];
    in.read(magic,4);
    if(std::string(magic,4)!="HUF1") throw std::runtime_error("Invalid compressed format.\n");

    //original size
    in.read(reinterpret_cast<char*>(&header.originalSize),sizeof(header.originalSize));

    //ext len
    uint32_t extLen;
    in.read(reinterpret_cast<char*>(&extLen),sizeof(extLen));

    //ext
    header.extension.resize(extLen);
    in.read(header.extension.data(),extLen);

    //freq table
    for(int i=0;i<256;i++){
        in.read(reinterpret_cast<char*>(&header.freq[i]),sizeof(uint64_t));
    }

    return header;
}

void decompressFile(const std::string& inputfile){
    std::ifstream in(inputfile, std::ios::binary);
    if(!in) throw std::runtime_error("Failed to open compressed file.");

    //read header
    HeaderInfo header = readHeader(in);

    //rebuild huffmann tree
    HuffmanNode* root = buildHuffmanTree(header.freq);

    //output filename
    std::filesystem::path p(inputfile);
    std::filesystem::path outPath = p.parent_path() / (p.stem().string() + "_decompressed");

    std::string outputfile = outPath.string()+header.extension;


    std::ofstream out(outputfile,std::ios::binary);
    if(!out) {
        freeTree(root);
        throw std::runtime_error("Failed to create output file.");
    } 

    BitReader br(in);

    uint64_t written = 0;
    HuffmanNode* curr = root;

    while(written<header.originalSize){
        bool bit;
        if(!br.readBit(bit)) break;

        curr = bit? curr->right:curr->left;

        if(!curr->left && !curr->right){
            out.put(static_cast<char>(curr->byte));
            written++;
            curr=root;
        }
    }

    freeTree(root);
}
