#pragma once

#include <iostream>
#include <unordered_map>
using std::unordered_map;
class frequency_table {
    // Something to store the frequency of each character
    
    void increment(char k);
    public:
        unordered_map<char, int> data;
        frequency_table(const std::string &file_name);
        ~frequency_table();
        
        int get_frequency(char c) const;
};