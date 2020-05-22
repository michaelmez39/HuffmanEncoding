#pragma once
#include "frequency_table.h"
#include <vector>
// struct for the nodes of the tree?
struct BinTree {
    int priority;
    std::string value;
    BinTree* left;
    BinTree* right;
    BinTree(int p, std::string val, BinTree* l, BinTree* r) {
        priority = p;
        value = val;
        left = l;
        right = r;
    }
    BinTree() {
        value="";
        priority=0;
        left = nullptr;
        right = nullptr;
    }
    bool is_leaf() {return left == nullptr && right == nullptr;}
};


struct MinHeap {
    std::vector<BinTree*> heap;
    void swap(int i1, int i2) {
        BinTree* temp = heap[i1];
        heap[i1] = heap[i2];
        heap[i2] = temp;
    }
    void bubble_up() {
        for (int index = heap.size() - 1;heap[index]->priority < heap[index / 2]->priority; index /= 2)
            swap(index, index / 2);
    }
    void minHeapify(int i) {
        int smallest = i;
        int left = i * 2 +1;
        int right = i * 2 + 2;
        if (left < heap.size() && heap[left]->priority < heap[smallest]->priority) {
            smallest = left;
        }
        if (right < heap.size() && heap[right]->priority < heap[smallest]->priority) {
            smallest = right;
        }

        if (smallest != i) {
            swap(smallest, i);
            minHeapify(smallest);
        }
    }
    void push(BinTree* to_add) {
        heap.push_back(to_add);
        bubble_up();
    }
    BinTree* pop() {
        BinTree* temp = heap[0];
        swap(0, heap.size() - 1);
        heap.pop_back();
        minHeapify(0);
        return temp;
    }
};

class huffman_encoder {
    BinTree* encoding_tree;
    public:
        huffman_encoder(const frequency_table &table);
        ~huffman_encoder();
        void recursive_delete(BinTree* delete_me);
        void print_codes(BinTree* tree, std::string path) const;
        std::string get_character_code(char c) const;
        std::string get_character_code_rec(char c, BinTree* traverser, std::string& code) const;
        std::string encode(const std::string &file_name) const;
        std::string decode(const std::string &string_to_decode) const;
};