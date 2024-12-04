#include <iostream>
#include <cstdint>
#include <vector>
#include <bitset>

uint8_t EncodeHelper(uint8_t byte) {
    bool d1 = (byte >> 3) & 1;
    bool d2 = (byte >> 2) & 1;
    bool d3 = (byte >> 1) & 1;
    bool d4 = (byte >> 0) & 1;

    bool p1 = 1 ^ d1 ^ d3 ^ d4;
    bool p2 = 1 ^ d1 ^ d2 ^ d4;
    bool p3 = 1 ^ d1 ^ d2 ^ d3;
    bool p4 = 1 ^ p1 ^ p2 ^ p3 ^ d1 ^ d2 ^ d3 ^ d4;

    uint8_t result = 0;
    result |= (p1 << 7);
    result |= (d1 << 6);
    result |= (p2 << 5);
    result |= (d2 << 4);
    result |= (p3 << 3);
    result |= (d3 << 2);
    result |= (p4 << 1);
    result |= (d4 << 0);

    return result;
}

std::vector<uint8_t> Encode(const std::vector<uint8_t> bytes) {
    std::vector<uint8_t> resBytes;
    for (uint8_t byte : bytes) {
        uint8_t resByte = EncodeHelper(byte);
        std::cout << std::bitset<4>(byte) << " encoded to " << std::bitset<8>(resByte) << std::endl;
        resBytes.push_back(resByte);
    }

    return resBytes;
}

uint8_t DecodeHelper(uint8_t x) {
    bool p1 = (x & 0b10000000) != 0;
    bool p2 = (x & 0b00100000) != 0;
    bool p3 = (x & 0b00001000) != 0;
    bool p4 = (x & 0b00000010) != 0;
    bool d1 = (x & 0b01000000) != 0;
    bool d2 = (x & 0b00010000) != 0;
    bool d3 = (x & 0b00000100) != 0;
    bool d4 = (x & 0b00000001) != 0;

    bool A = p1 ^ d1 ^ d3 ^ d4 == 1;
    bool B = p2 ^ d1 ^ d2 ^ d4 == 1;
    bool C = p3 ^ d1 ^ d2 ^ d3 == 1;
    bool D = p1 ^ p2 ^ p3 ^ p4 ^ d1 ^ d2 ^ d3 ^ d4 == 1;

    if ((!A || !B || !C) && D)
        return 0b10000000;

    int temp = !A + !B * 2 + !C * 4 + !D * 8;


    switch (temp) {
    case 15:
        d1 ^= 1;
        break;
    case 14:
        d2 ^= 1;
        break;
    case 13:
        d3 ^= 1;
        break;
    case 11:
        d4 ^= 1;
        break;
    }

    return (d1 << 3) | (d2 << 2) | (d3 << 1) | d4;
}

std::vector<uint8_t> Decode(const std::vector<uint8_t> bytes) {
    std::vector<uint8_t> resBytes;
    for (uint8_t byte : bytes) {
        uint8_t res = DecodeHelper(byte);
        if (res == 0b10000000) {
            return std::vector<uint8_t>();
        }
        else
            std::cout << std::bitset<8>(byte) << " decoded to " << std::bitset<4>(res) << std::endl;
        resBytes.push_back(res);
    }
    return resBytes;
}

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