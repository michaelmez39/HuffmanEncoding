#include "frequency_table.h"
#include <iostream>
#include <fstream>
using std::ifstream;
typedef unordered_map<char, int> map;
void frequency_table::increment(const char k) {
    map::iterator val = data.find(k);
    if (val == data.end()) {
        data.emplace(k, 1);
    } else {
        val->second += 1;
    }
}

frequency_table::frequency_table(const std::string &file_name) {
	ifstream f(file_name);
    if (!f.is_open())
        throw std::runtime_error("File not found");

    for (char c; f.get(c);) {
        increment(c);
    }
}

frequency_table::~frequency_table() {

}

int frequency_table::get_frequency(char c) const {
        const map::const_iterator v = data.find(c);
        return v == data.end() ? 0 : v->second;
}