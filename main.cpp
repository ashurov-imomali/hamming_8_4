#include "hamming.h"

std::vector<bool> toBinary(int a) {
    std::vector<bool> res(4,0);
    size_t i = 0;
    while (a > 0) {
        res[3 - i] = a%2;
        i++;
        a/=2;
    }
    return res;
}


void EncodeFromInput() {
    int input;
    std::cout << "Enter a number between 0 and 15 to encode:";
    std::cin >> input;

    if (input < 0 || input > 15) {
        std::cout << "Invalid input. Please enter a number between 0 and 15." << std::endl;
        return;
    }


    std::vector<bool> encoded = Encoder(toBinary(input));
    for (int bit : toBinary(input)) {
        std::cout << bit;
    }
    std::cout << " encoded to ";
    for(int bit: encoded) {
        std::cout<<bit;
    }
    std::cout << "\n";

}

void DecodeFromInput() {
    std::string input;
    std::cout << "Enter a string of 8 bits:";
    std::cin >> input;

    if (input.size() != 8 || input.find_first_not_of("01") != std::string::npos) {
        std::cout << "Invalid input. Please enter exactly 8 bits (0s and 1s)." << std::endl;
        return;
    }

    std::vector<bool> encode(8,0);
    for (size_t i = 0; i < input.length(); i++) {
        encode[i] = input[i] - '0';
    }

    std::vector<bool> decoded = Decoder(encode);

    if (decoded.empty()) {
        std::cout << "Decoding failed due to 2 errors." << std::endl;
    } else {
        std::cout<<"Decode result is:";
        for (int bit:decoded) {
            std::cout << bit;
        }
        std::cout << "\n";
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