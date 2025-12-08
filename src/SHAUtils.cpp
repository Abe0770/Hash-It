// SHAUtils.cpp

#include "SHAUtils.h"
#include <string>

using std::string;

namespace sha_utils {

    string toBinary(const string& st, int bits) {
        string binStr;
        for (char ch : st)
            binStr.append(std::bitset<8>(ch).to_string());

        binStr.append("1");
        for (int i = (st.size() * 8) + 1; i < bits - 64; i++)
            binStr.append("0");

        binStr.append(std::bitset<64>(st.size() * 8).to_string());
        return binStr;
    }

    unsigned long toULong(const string& str) {
        return std::bitset<32>(str).to_ulong();
    }

    unsigned long rotateLeft(unsigned long value, int bits) {
        return ((value << bits) | (value >> (32 - bits))) & 0xFFFFFFFF;
    }

    string padMessage(const string& input, size_t blockSize, size_t lengthSize) {
        string bin;
        for (char c : input)
            bin += std::bitset<8>(c).to_string();
        size_t originalLength = bin.size();
        bin += '1';
        while ((bin.size() + lengthSize) % blockSize != 0)
            bin += '0';
        bin += std::bitset<128>(originalLength).to_string().substr(128 - lengthSize);

        return bin;
    }

    unsigned long long toULL(const string& str) {
        return std::bitset<64>(str).to_ullong();
    }

    unsigned long long rotateLeft(unsigned long long value, int bits) {
        return ((value << bits) | (value >> (64 - bits)));
    }
}