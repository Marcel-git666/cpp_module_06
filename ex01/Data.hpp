#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <string>

struct Data {
    std::string key;
    int value;

    Data(const std::string &k, int v) : key(k), value(v) {
        std::cout << "Data object created." << std::endl;
    }
};

#endif
