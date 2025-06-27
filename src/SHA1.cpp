// SHA1.cpp

#include "SHA1.h"
#include "SHAUtils.h"
#include <bitset>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using sha_utils::rotateLeft, sha_utils::padMessage;
using std::string, std::stringstream;
using std::vector, std::bitset;
using std::cout;
using std::exit;
using std::setw, std::setfill, std::hex;

SHA1::SHA1() {
    H = {
        "01100111010001010010001100000001",
        "11101111110011011010101110001001",
        "10011000101110101101110011111110",
        "00010000001100100101010001110110",
        "11000011110100101110000111110000"
    };
}

unsigned long SHA1::f(int t, unsigned long B, unsigned long C, unsigned long D) {
    if (t < 20) return (B & C) | ((~B) & D);
    if (t < 40) return B ^ C ^ D;
    if (t < 60) return (B & C) | (B & D) | (C & D);
    return B ^ C ^ D;
}

unsigned long SHA1::k(int t) {
    if (t < 20) return 0x5A827999;
    if (t < 40) return 0x6ED9EBA1;
    if (t < 60) return 0x8F1BBCDC;
    return 0xCA62C1D6;
}

void SHA1::hashString(const string& input) {
    string bin = padMessage(input, 512, 64);
    int N = bin.size() / 512;

    vector<string> M;
    for (int i = 0; i < N * 16; ++i)
        M.push_back(bin.substr(i * 32, 32));

    blockComp(M);
}

void SHA1::display() const {
    cout << "\nHash value: ";
    for (const string &h : H) {
        stringstream ss;
        ss << hex << setw(8) << setfill('0') << bitset<32>(h).to_ulong();
        cout << ss.str();
    }
    cout << '\n';
}

void SHA1::blockComp(const vector<string>& M) {
    for (size_t i = 0; i < M.size(); i += 16) {
        unsigned long W[80];
        for (int t = 0; t < 16; ++t)
            W[t] = bitset<32>(M[i + t]).to_ulong();
        for (int t = 16; t < 80; ++t)
            W[t] = rotateLeft(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);

        unsigned long A = bitset<32>(H[0]).to_ulong();
        unsigned long B = bitset<32>(H[1]).to_ulong();
        unsigned long C = bitset<32>(H[2]).to_ulong();
        unsigned long D = bitset<32>(H[3]).to_ulong();
        unsigned long E = bitset<32>(H[4]).to_ulong();

        for (int t = 0; t < 80; ++t) {
            unsigned long TEMP = (rotateLeft(A, 5) + f(t, B, C, D) + E + W[t] + k(t)) & 0xFFFFFFFF;
            E = D;
            D = C;
            C = rotateLeft(B, 30);
            B = A;
            A = TEMP;
        }

        H[0] = bitset<32>((A + bitset<32>(H[0]).to_ulong()) & 0xFFFFFFFF).to_string();
        H[1] = bitset<32>((B + bitset<32>(H[1]).to_ulong()) & 0xFFFFFFFF).to_string();
        H[2] = bitset<32>((C + bitset<32>(H[2]).to_ulong()) & 0xFFFFFFFF).to_string();
        H[3] = bitset<32>((D + bitset<32>(H[3]).to_ulong()) & 0xFFFFFFFF).to_string();
        H[4] = bitset<32>((E + bitset<32>(H[4]).to_ulong()) & 0xFFFFFFFF).to_string();
    }
}
