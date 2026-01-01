#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include "compress_H.h"
#include "decompress_H.h"


//menu cli
void showmenu(std::string& inputfile){
    std::cout<<"<====================File Compression Tool==================>\n";
    std::cout<<"Enter File Path: ";
    std::getline(std::cin,inputfile);
}

//compress or decompress
int decisionMenu(){
    int decision;
    std::cout<<"\n1.Compress\n2.Decompress\nEnter Number: ";
    std::cout<<"\n";
    std::cin>>decision;
    if(decision==1) return 1;
    if(decision==2) return 0;
    throw std::runtime_error("Error");
}




int main(int argc, char* argv[]){
    //file name input
    std::string inputfile,outputfile,ext;
    
    if (argc==1){
        showmenu(inputfile);
    }
    else if(argc==2){
        inputfile = argv[1];
        
    }else {
        std::cerr<<"Please provide valid inputs.\n";
        return 1;
    }
    if(!std::filesystem::exists(inputfile)){
        std::cerr<<"File doesn't exist.\n";
        return 1;
    }
    
    int k = decisionMenu();
    auto start = std::chrono::high_resolution_clock::now();
    
    //compression logic
    if(k){
        compressFile(inputfile);
        
    } 
    else{
        decompressFile(inputfile);
        
    } 
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end-start;

    std::cout<<"Process Completed."<<"\nTime taken: "<< elapsed.count()<<" seconds\n";

    return 0;
}