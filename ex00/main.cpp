#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

// Barvy pro lepší čitelnost výstupu
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define NC "\033[0m" // No Color

void runTest(const std::string &test_name, const std::string &input) {
    std::cout << "\n"
              << BLUE << "--- Test: " << test_name << " ---" << NC << std::endl;
    std::cout << YELLOW << "Input: ./convert " << input << NC << std::endl;

    ScalarConverter::convert(input);

    std::cout << BLUE << "---------------------------------" << NC << std::endl;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        std::cout << GREEN
                  << "Running conversion for command line argument: " << argv[1]
                  << NC << std::endl;
        ScalarConverter::convert(argv[1]);

    } else if (argc == 1) {
        // --- 2. Rozsáhlý testovací scénář (Volitelné testy) ---

        std::cout << YELLOW
                  << "No argument provided. Running comprehensive test suite..."
                  << NC << std::endl;

        // A. PŘÍKLADY ZADÁNÍ / BĚŽNÉ HODNOTY
        runTest("Char Literal", "a");
        runTest("Int Literal", "42");
        runTest("Float Literal", "42.0f"); // [cite: 132]
        runTest("Double Literal", "42.0");

        // B. SPECIÁLNÍ LITERÁLY
        runTest("Special: Not a Number (double)", "nan");       // [cite: 127]
        runTest("Special: Infinity (float)", "+inff");          // [cite: 105]
        runTest("Special: Negative Infinity (double)", "-inf"); // [cite: 110]
        runTest("Special: Zero Float", "0.0f");                 // [cite: 104]

        // C. OKRAJOVÉ PŘÍPADY / PŘETEČENÍ (Overflow / Impossible)

        // 1. Zobrazitelnost (Char)
        runTest("Non-displayable Char (ASCII 0)",
                "0"); // Mělo by vypsat "Non displayable" [cite: 102]
        runTest("Non-displayable Char (ASCII 10)",
                "10"); // Mělo by vypsat "Non displayable" [cite: 102]

        // 2. Přetečení (Int / Char z Float/Double)
        runTest("Float Overflow to Int/Char",
                "2147483648.0f"); // Přetečení rozsahu int (INT_MAX + 1)
        runTest("Double Overflow to Float",
                "1.8e309"); // Přetečení rozsahu float (za FLOAT_MAX)
        runTest("Int too large for Char",
                "1000"); // Mimo rozsah char -> "impossible" [cite: 117]

        // D. NEPLATNÉ VSTUPY (Mělo by se vrátit UNKNOWN_LITERAL)
        runTest("Invalid Input (Multiple decimals)", "1.2.3f");
        runTest("Invalid Input (Invalid char)", "42abc");

    } else {
        // --- 3. Chybný počet argumentů ---

        std::cerr << RED << "Error: Invalid number of arguments." << NC
                  << std::endl;
        std::cerr << "Usage: " << argv[0] << " <literal_value>" << std::endl;
        std::cerr << "Example: " << argv[0] << " 42.0f" << std::endl;
        return 1;
    }
    return 0;
}
