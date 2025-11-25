#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter {
private:
  // Orthodox Canonical Form
  ScalarConverter(void);
  ScalarConverter(ScalarConverter const &other);
  ScalarConverter &operator=(ScalarConverter const &other);
  ~ScalarConverter(void);

  // Helper methods
  static bool isSpecialValue(std::string const &input);
  static void handleSpecialValue(std::string const &input);

public:
  // Other methods
  static void convert(std::string const &input);
  // Exceptions
  class ConversionException : public std::exception {
    const char *what() const throw();
  };
};

#endif
