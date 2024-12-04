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