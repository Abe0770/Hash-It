// SHAUtils.cpp

#include "SHAUtils.h"
#include <string>

namespace sha_utils {

    std::string toBinary(const std::string& st, int bits) {
        std::string binStr;
        for (char ch : st)
            binStr.append(std::bitset<8>(ch).to_string());

        binStr.append("1");
        for (int i = (st.size() * 8) + 1; i < bits - 64; i++)
            binStr.append("0");

        binStr.append(std::bitset<64>(st.size() * 8).to_string());
        return binStr;
    }

    unsigned long toULong(const std::string& str) {
        return std::bitset<32>(str).to_ulong();
    }

}