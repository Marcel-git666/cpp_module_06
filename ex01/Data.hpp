#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
    std::string key;
    int value;

    Data(const std::string &k, int v);
};

#endif
