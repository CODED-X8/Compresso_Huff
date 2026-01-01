#include "BIT_IO_H.h"
#include "decompress_H.h"

BitWriter::BitWriter(std::ofstream& out) : out(out), buffer(0), bitCount(0) {};

void BitWriter::writeBit(bool bit){
    buffer <<= 1;
    if(bit) buffer |= 1;

    bitCount++;

    if(bitCount == 8){
        out.put(static_cast<char>(buffer));
        buffer=0;
        bitCount=0;
    }
}

void BitWriter::writeBits(const std::vector<bool>& bits){
    for(bool b:bits) writeBit(b);
}

void BitWriter::flush(){
    if(bitCount>0){
        buffer <<= (8-bitCount);
        out.put(static_cast<char>(buffer));
        buffer=0;
        bitCount=0;
    }
}

BitReader::BitReader(std::ifstream& in)
    : in(in), buffer(0), bitsLeft(0) {}

bool BitReader::readBit(bool& bit){
    if(bitsLeft==0){
        char c;
        if(!in.get(c)) return false;
        buffer = static_cast<uint8_t>(c);
        bitsLeft = 8;
    }

    bit = (buffer & 0x80) !=0;
    buffer<<=1;
    bitsLeft--;

    return true;
}