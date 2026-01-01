#include <queue>
#include <array>
#include <vector>
#include "huffman_node.h"
#include "huffman_H.h"
#include "frequency_table_H.h"
#include "frequency_table_H.h"
using HuffmanCode = std::vector<bool>;


HuffmanNode* buildHuffmanTree(const std::array<uint64_t, 256>& freq){
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>,Compare> pq;

    for(int i=0;i<256;++i){
        if(freq[i]>0){
            pq.push(new HuffmanNode(static_cast<uint8_t>(i), freq[i]));
        }
    }

    if(pq.empty()) return nullptr;

    if(pq.size()==1) {
        HuffmanNode* only = pq.top();
        pq.pop();
        return new HuffmanNode(only, nullptr);
    }

    while(pq.size()>1){
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* parent = new HuffmanNode(left,right);
        pq.push(parent);
    }

    return pq.top();
}

void dfsGenerate(HuffmanNode* node, std::vector<bool>& path,
    std::array<HuffmanCode, 256>& codes){

    if(!node) return;

    if(!node->left && !node->right){
        if(path.empty()){
            path.push_back(0);
        }
        codes[node->byte] = path;
        return;
    }

    //go left -> 0
    path.push_back(0);
    dfsGenerate(node->left,path,codes);
    path.pop_back();

    //go right -> 1
    path.push_back(1);
    dfsGenerate(node->right,path,codes);
    path.pop_back();
}

void freeTree(HuffmanNode* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}


void generateCodes(HuffmanNode* root, std::array<HuffmanCode,256>& codes){
    std::vector<bool> path;
    dfsGenerate(root,path,codes);
}