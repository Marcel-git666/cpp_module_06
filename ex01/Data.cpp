
#include "Data.hpp"
#include <iostream>

Data::Data(const std::string &k, int v) : key(k), value(v) {
    std::cout << "Data object created." << std::endl;
}
