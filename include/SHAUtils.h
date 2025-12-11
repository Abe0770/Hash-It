// SHAUtils.h

#ifndef SHAUTILS_H
#define SHAUTILS_H

#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

using std::string;

namespace sha_utils {
    string toBinary(const string &st, int bits);
    unsigned long toULong(const string &str);
    unsigned long rotateLeft(unsigned long value, int bits);
    string padMessage(const std::string& input, size_t blockSize, size_t lengthSize);
}

#endif