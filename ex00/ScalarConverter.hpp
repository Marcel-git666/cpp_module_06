#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter {
  private:
    enum e_literal_type {
        CHAR_LITERAL,
        INT_LITERAL,
        FLOAT_LITERAL,
        DOUBLE_LITERAL,
        SPECIAL_FLOAT_LITERAL,
        SPECIAL_DOUBLE_LITERAL,
        UNKNOWN_LITERAL
    };
    // Orthodox Canonical Form
    ScalarConverter(void);
    ScalarConverter(ScalarConverter const &other);
    ScalarConverter &operator=(ScalarConverter const &other);
    ~ScalarConverter(void);

    // Helper methods
    static bool isSpecialFloatLiteral(std::string const &input);
    static bool isSpecialDoubleLiteral(std::string const &input);
    static bool isCharLiteral(std::string const &input);
    static void handleSpecialValue(std::string const &input);
    static e_literal_type identifyType(std::string const &input);
    static void convertFromChar(char c);
    static void convertFromInt(long l);
    static void convertFromFloat(float f, std::string const &input);
    static void convertFromDouble(double d, std::string const &input);
    static void printChar(long value);
    static void printInt(long value);
    static void printFloat(double value, int precision);
    static void printDouble(double value, int precision);
    static int getPrecision(std::string const &input);

  public:
    // Other methods
    static void convert(std::string const &input);
};

#endif
