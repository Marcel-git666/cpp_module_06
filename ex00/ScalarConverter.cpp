#include "ScalarConverter.hpp"
#include <cctype>
#include <iomanip>
#include <limits>
#include <stddef.h>
#include <string>

ScalarConverter::ScalarConverter(void) {}
ScalarConverter::ScalarConverter(ScalarConverter const &) {}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &) {
    return *this;
}
ScalarConverter::~ScalarConverter(void) {}

// Other methods

bool ScalarConverter::isSpecialFloatLiteral(std::string const &input) {
    if (input == "nanf" || input == "inff" || input == "+inff" ||
        input == "-inff") {
        return true;
    }
    return false;
}

bool ScalarConverter::isSpecialDoubleLiteral(std::string const &input) {
    if (input == "nan" || input == "inf" || input == "+inf" ||
        input == "-inf") {
        return true;
    }
    return false;
}

void ScalarConverter::handleSpecialValue(std::string const &input) {
    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";

    if (isSpecialDoubleLiteral(input)) {
        std::cout << "float: " << input << "f\n";
        std::cout << "double: " << input << "\n";
    } else {
        std::cout << "float: " << input << "\n";
        std::cout << "double: " << input.substr(0, input.size() - 1) << "\n";
    }
}

bool ScalarConverter::isCharLiteral(std::string const &input) {
    return (input.size() == 1 && !std::isdigit(input[0]));
}

ScalarConverter::e_literal_type
ScalarConverter::identifyType(std::string const &input) {
    if (isSpecialDoubleLiteral(input)) {
        return SPECIAL_DOUBLE_LITERAL;
    }
    if (isSpecialFloatLiteral(input)) {
        return SPECIAL_FLOAT_LITERAL;
    }
    if (input.size() == 1 && !std::isdigit(input[0])) {
        return CHAR_LITERAL;
    }
    char *end_ptr;
    std::strtod(input.c_str(), &end_ptr);

    std::string remainder(end_ptr);
    if (remainder == "f") {
        return FLOAT_LITERAL;
    } else if (remainder == "") {
        if (input.find('.') != std::string::npos) {
            return DOUBLE_LITERAL;
        } else {
            return INT_LITERAL;
        }
    } else {
        return UNKNOWN_LITERAL;
    }
}

void ScalarConverter::printChar(long value) {
    if (value < std::numeric_limits<char>::min() ||
        value > std::numeric_limits<char>::max()) {
        std::cout << "char: impossible\n";
    } else if (!std::isprint(static_cast<int>(value))) {
        std::cout << "char: Non displayable\n";
    } else {
        std::cout << "char: '" << static_cast<char>(value) << "'\n";
    }
}

void ScalarConverter::printInt(long value) {
    if (value < std::numeric_limits<int>::min() ||
        value > std::numeric_limits<int>::max()) {
        std::cout << "int: impossible\n";
    } else {
        std::cout << "int: " << static_cast<int>(value) << "\n";
    }
}

void ScalarConverter::printFloat(double value, int precision) {
    std::cout << "float: ";
    std::cout << std::fixed << std::showpoint << std::setprecision(precision);
    std::cout << static_cast<float>(value) << "f\n";
}

void ScalarConverter::printDouble(double value, int precision) {
    std::cout << "double: ";
    std::cout << std::fixed << std::showpoint << std::setprecision(precision);
    std::cout << value << "\n";
}

void ScalarConverter::convertFromChar(char c) {
    double d = static_cast<double>(c);
    int precision = 1;
    printChar(c);
    printInt(c);
    printFloat(d, precision);
    printDouble(d, precision);
}

void ScalarConverter::convertFromFloat(float f, std::string const &input) {
    double d = static_cast<double>(f);
    int p = getPrecision(input);
    printChar(d);
    printInt(d);
    printFloat(d, p);
    printDouble(d, p);
}

void ScalarConverter::convertFromDouble(double d, std::string const &input) {
    int p = getPrecision(input);
    printChar(d);
    printInt(d);
    printFloat(d, p);
    printDouble(d, p);
}

void ScalarConverter::convertFromInt(long l) {
    double d = static_cast<double>(l);
    int precision = 1;
    printChar(l);
    printInt(l);
    printFloat(d, precision);
    printDouble(d, precision);
}

int ScalarConverter::getPrecision(std::string const &input) {
    size_t pos = input.find('.');
    if (pos == std::string::npos) {
        return 1;
    }
    size_t end_index = input.size();
    if (end_index > 0 &&
        (input[end_index - 1] == 'f' || input[end_index - 1] == 'F')) {
        end_index--;
    }
    if (end_index - 1 == pos) {
        return 1;
    }
    return end_index - pos - 1;
}

void ScalarConverter::convert(std::string const &input) {
    switch (identifyType(input)) {
    case SPECIAL_DOUBLE_LITERAL:
        handleSpecialValue(input);
        break;
    case SPECIAL_FLOAT_LITERAL:
        handleSpecialValue(input);
        break;
    case CHAR_LITERAL:
        convertFromChar(input[0]);
        break;
    case FLOAT_LITERAL:
        convertFromFloat(std::strtod(input.c_str(), NULL), input);
        break;
    case DOUBLE_LITERAL:
        convertFromDouble(std::strtod(input.c_str(), NULL), input);
        break;
    case INT_LITERAL:
        convertFromInt(std::strtol(input.c_str(), NULL, 10));
        break;
    default:
        break;
    }
}
