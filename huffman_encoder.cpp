#include <iostream>
#include <fstream>
#include "huffman_encoder.h"

huffman_encoder::huffman_encoder(const frequency_table &table){
    MinHeap letter_priority;
    for (auto kv : table.data) {
        letter_priority.push(new BinTree(kv.second, std::string(1, kv.first), nullptr, nullptr));
    }
    std::cout <<"Check the values!!" << std::endl;
    for (auto a : letter_priority.heap) {
        std::cout << a->value << " ";
    }
    std::cout << std::endl;
    while (letter_priority.heap.size() > 1) {
        BinTree* left = letter_priority.pop();
        BinTree* right = letter_priority.pop();
        std::string value = left->value + right->value;
        BinTree* merged = new BinTree (left->priority + right->priority, value, left, right);
        letter_priority.push(merged);
    }
    encoding_tree = letter_priority.pop(); // Shallow Copy!!!!!!!!!!!!!!!!!!
    print_codes(encoding_tree, "");
}
huffman_encoder::~huffman_encoder(){
    recursive_delete(encoding_tree);
}
void huffman_encoder::recursive_delete(BinTree* delete_me) {
    if (delete_me == nullptr)
        return;
    if (delete_me -> left != nullptr)
        recursive_delete(delete_me -> left);
    if (delete_me -> right != nullptr)
        recursive_delete(delete_me -> right);
    delete delete_me;
}

void huffman_encoder::print_codes(BinTree* tree, std::string path) const {
    if (tree == nullptr) {
        return;
    }
    if (tree->is_leaf()) {
        std::cout << "Letter: " << tree->value << " Path: " << path << std::endl;
        return;
    }
    print_codes(tree->left, path + "0");
    print_codes(tree->right, path + "1");
}

std::string huffman_encoder::get_character_code(char character) const {
    std::string code;
    if (encoding_tree->is_leaf()){
        return std::string("0");
    }
    get_character_code_rec(character, encoding_tree, code);
    return code;
}
std::string huffman_encoder::get_character_code_rec(char character, BinTree* traverser, std::string& code) const {
    if (traverser->is_leaf()) {
        return code;
    } else if (traverser->left != nullptr && traverser->left->value.find(character) != std::string::npos) {
        code.push_back('0');
        return get_character_code_rec(character, traverser->left, code);
    } else if (traverser->right != nullptr && traverser->right->value.find(character) != std::string::npos) {
        code.push_back('1');
        return get_character_code_rec(character, traverser->right, code);
    }
}
std::string huffman_encoder::encode(const std::string &file_name) const {
    std::string encoded_file;
    std::ifstream to_encode(file_name);
    for (char c; to_encode.get(c); ) {
        encoded_file.append(get_character_code(c));
    }
    // std::cout << "Encoded File:  " << encoded_file << std::endl;
    return encoded_file;
}
std::string huffman_encoder::decode(const std::string &string_to_decode) const {
    std::string decoded;
    BinTree* traverser = encoding_tree;
    if (encoding_tree->is_leaf()) {
        for (auto c : string_to_decode) {
                decoded.append(encoding_tree->value);
        }
        return decoded;
    }
    for (auto c : string_to_decode) {
        if (traverser->is_leaf()){
            decoded.push_back(traverser->value[0]);
            traverser = encoding_tree;
        }
        if (c == '0') {
            traverser = traverser -> left;
        } else if(c == '1') {
            traverser = traverser -> right;
        }
    }
    decoded.append(traverser->value);
    return decoded;
}