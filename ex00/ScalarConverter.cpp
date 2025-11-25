#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void) {}
ScalarConverter::ScalarConverter(ScalarConverter const &) {}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &) {
  return *this;
}
ScalarConverter::~ScalarConverter(void) {}

// Other methods

bool isSpecialValue(std::string const &input) {
  if (input == "nan" || input == "nanf" || input == "inf" || input == "inff" ||
      input == "+inf" || input == "+inff" || input == "-inf" ||
      input == "-inff") {
    return true;
  }
  return false;
}

void ScalarConverter::convert(std::string const &input) {
  if (isSpecialValue(input))
    handleSpecialValue(input);
}

// Exceptions
const char *ScalarConverter::ConversionException::what() const throw() {
  return "impossible";
}
