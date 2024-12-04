#include <iostream>
#include <cstdint>
#include <vector>
#include <bitset>

std::vector<bool> Encoder(std::vector<bool> code) {
    std::vector encode(8,false);
    encode[0] = 1 ^ code[0] ^ code[2] ^ code[3];
    encode[1] = code[0];
    encode[2] = 1 ^ code[0] ^ code[1] ^ code[3];
    encode[3] = code[1];
    encode[4] = 1 ^ code[0] ^ code[1] ^ code[2];
    encode[5] = code[2];
    encode[6] = 1 ^ code[0] ^ code[1] ^ code[2] ^ code[3] ^ encode[0] ^ encode[2] ^ encode[4];
    encode[7] = code[3];
    return encode;
}



std::vector<bool> Decoder(std::vector<bool> a) {
    bool A = a[0] ^ a[1] ^ a[5] ^ a[7] == 1;
    bool B = a[1] ^ a[2] ^ a[3] ^ a[7] == 1;
    bool C = a[1] ^ a[3] ^ a[4] ^ a[5] == 1;
    bool D = a[0] ^ a[1] ^ a[2] ^ a[3] ^ a[4] ^ a[5] ^ a[6] ^ a[7] == 1;
    if ((!A || !B || !C) && D) {
        return std::vector<bool>{};
    }
    int index = !A + !B * 2 + !C * 4 + !D * 8;
    if ((-2*index+31)%2 == 0) a[-2*index+31] = !a[-2*index+31];
    return std::vector<bool>{a[1], a[3], a[5], a[7]};
}
