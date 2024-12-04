
#include "hamming.h"

void EncodeFromInput() {
    int input;
    std::cout << "Enter a number between 0 and 15 to encode:";
    std::cin >> input;

    if (input < 0 || input > 15) {
        std::cout << "Invalid input. Please enter a number between 0 and 15." << std::endl;
        return;
    }

    uint8_t byte = static_cast<uint8_t>(input);
    std::vector<uint8_t> bytes = { byte };
    std::vector<uint8_t> encoded = Encode(bytes);

    std::cout << "Encoded result:" << std::bitset<8>(encoded[0]) << std::endl;
}

void DecodeFromInput() {
    std::string input;
    std::cout << "Enter a string of 8 bits:";
    std::cin >> input;

    if (input.size() != 8 || input.find_first_not_of("01") != std::string::npos) {
        std::cout << "Invalid input. Please enter exactly 8 bits (0s and 1s)." << std::endl;
        return;
    }

    uint8_t byte = 0;
    for (size_t i = 0; i < 8; ++i) {
        byte |= (input[i] - '0') << (7 - i);
    }

    std::vector<uint8_t> bytes = { byte };
    std::vector<uint8_t> decoded = Decode(bytes);

    if (decoded.empty()) {
        std::cout << "Decoding failed due to 2 errors." << std::endl;
    } else {
        std::cout << "Decoded result:" << std::bitset<4>(decoded[0]) << std::endl;
    }
}

void ShowMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Encode a number (0-15)" << std::endl;
    std::cout << "2. Decode a binary string (8 bits)" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Choose an option:";
}

int main() {
    int choice;
    do {
        ShowMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                EncodeFromInput();
                break;
            case 2:
                DecodeFromInput();
                break;
            case 3:
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please select 1, 2, or 3." << std::endl;
        }
    } while (choice != 3);

    return 0;
}