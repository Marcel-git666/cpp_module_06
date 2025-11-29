#include <iomanip>
#include <iostream>
#include <string>

#include "Data.hpp"
#include "Serializer.hpp"

int main() {
    Data originalData("config_v1", 42);
    Data *originalPtr = &originalData;

    std::cout << "\n--- Original Data and Address ---\n";
    std::cout << "Original Key: " << originalData.key << std::endl;
    std::cout << "Original Value: " << originalData.value << std::endl;
    std::cout << "Original Pointer Address: " << originalPtr << std::endl;

    uintptr_t rawValue = Serializer::serialize(originalPtr);

    std::cout << "\n--- Serialization ---\n";
    std::cout << "Serialized Value (uintptr_t): 0x" << std::hex << rawValue
              << std::endl;

    std::cout << std::dec << std::nouppercase;

    Data *deserializedPtr = Serializer::deserialize(rawValue);

    std::cout << "\n--- Deserialization ---\n";
    std::cout << "Deserialized Pointer Address: " << deserializedPtr
              << std::endl;

    std::cout << "\n--- Check ---\n";

    if (originalPtr == deserializedPtr) {
        std::cout
            << "✅ Addresses match: Serialization/Deserialization successful."
            << std::endl;
        std::cout << "Data check: " << deserializedPtr->key << " = "
                  << deserializedPtr->value << std::endl;
    } else {
        std::cout << "❌ Error: Addresses don't match! Conversion failure."
                  << std::endl;
    }

    return 0;
}
