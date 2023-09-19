#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <cstdlib>

using namespace std;

class SHA256 {
private:
    vector<string> H;
    vector<string> K;

    int calcBits(int size) {
        int bits = 512;
        size = 8*size;
        int rounded = ((size / 512) + 1) * 512;
        if(size >= rounded - 64) 
            rounded += 512;
        return rounded;
    }

    string binConv(string st, int bits) {
        string binStr;
        for(int i = 0 ; i < st.size() ; i++) {
            binStr.append(bitset<8>(st[i]).to_string());
        }
        binStr.append("1");
        for(int i = (st.size()*8) + 1 ; i < bits - 64; i++) {
            binStr.append("0");
        }
        binStr.append(bitset<64>(st.size()*8).to_string());
        return binStr;
    }

    void mSplit(vector<string> &M, string binStr, int N) {
        for(int i = 0 ; i < N*16; i++) {
            M.push_back(binStr.substr(32*i, 32));
        }
    }

    ulong toULong(string str) {
        bitset<32> bits(str);
        return bits.to_ulong();
    }

    string sigma(string s1, int a1, int a2, int a3) {
        string s2 = s1, s3 = s1;

        rotate(s1.rbegin(), s1.rbegin() + a1, s1.rend());
        string rotRa = s1;

        rotate(s2.rbegin(), s2.rbegin() + a2, s2.rend());
        string rotRb = s2;

        bitset<32> bits(s3);
        bitset<32> sh = bits >> a3;
        string shR = sh.to_string();
        bitset<32> sum = toULong(rotRa) ^ toULong(rotRb) ^ toULong(shR);
        string sigma = sum.to_string();
        return sigma;
    }

    string SIGMA(string s1, int a1, int a2, int a3) {
        string s2 = s1, s3 = s1;

        rotate(s1.rbegin(), s1.rbegin() + a1, s1.rend());
        string rotRa = s1;

        rotate(s2.rbegin(), s2.rbegin() + a2, s2.rend());
        string rotRb = s2;

        rotate(s3.rbegin(), s3.rbegin() + a3, s3.rend());
        string rotRc = s3;

        bitset<32> sum = toULong(rotRa) ^ toULong(rotRb) ^ toULong(rotRc);
        string SIGMA = sum.to_string();
        return SIGMA;
    }

    string choose(string e, string f, string g) {
        string st;
        for(int i = 0 ; i < 32 ; i++) {
            if(e[i] == '0')
                st.append(1, g[i]);
            else
                st.append(1, f[i]);
        }
        return st;
    }

    string maj(string a, string b, string c) {
        string st;
        for(int i = 0 ; i < 32 ; i++)
            a[i] == b[i] ? st.append(1, a[i]) : (b[i] == c[i] ? st.append(1, b[i]) : st.append(1, c[i]));
        return st;
    }

    void blockComp(int N, vector<string> M, vector<string> &W, vector<string> &T) {
        for(int i = 0; i < N; i++) {
            copy(&M[16*i], &M[(16*i)+16], back_inserter(W));
            for(int t = 16; t < 64; t++) {
                bitset<32> result = toULong(W[t-16]) + toULong(sigma(W[t-15], 7, 18, 3)) + toULong(W[t-7]) + toULong(sigma(W[t-2], 17, 19, 10));
                W.push_back(result.to_string());
            }
            string a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
            for(int t = 0 ; t < 64 ; t++) {
                bitset<32> t1 = toULong(h) + toULong(choose(e, f, g)) + toULong(SIGMA(e, 6, 11, 25)) + toULong(K[t]) + toULong(W[t]);
                bitset<32> t2 = toULong(SIGMA(a, 2, 13, 22)) + toULong(maj(a, b, c));
                string T1 = t1.to_string(), T2 = t2.to_string();
                bitset<32> RES1 = toULong(d) + toULong(T1);
                bitset<32> RES2 = toULong(T1) + toULong(T2);
                h = g;
                g = f;
                f = e;
                e = RES1.to_string();
                d = c;
                c = b;
                b = a;
                a = RES2.to_string();
            }
            bitset<32> res1 = toULong(a) + toULong(H[0]);
            bitset<32> res2 = toULong(b) + toULong(H[1]);
            bitset<32> res3 = toULong(c) + toULong(H[2]);
            bitset<32> res4 = toULong(d) + toULong(H[3]);
            bitset<32> res5 = toULong(e) + toULong(H[4]);
            bitset<32> res6 = toULong(f) + toULong(H[5]);
            bitset<32> res7 = toULong(g) + toULong(H[6]);
            bitset<32> res8 = toULong(h) + toULong(H[7]);
            H[0] = res1.to_string();
            H[1] = res2.to_string();
            H[2] = res3.to_string();
            H[3] = res4.to_string();
            H[4] = res5.to_string();
            H[5] = res6.to_string();
            H[6] = res7.to_string();
            H[7] = res8.to_string();
            W.clear();
        }
    }

public:
    SHA256() {
        H= {"01101010000010011110011001100111",
            "10111011011001111010111010000101",
            "00111100011011101111001101110010",
            "10100101010011111111010100111010",
            "01010001000011100101001001111111",
            "10011011000001010110100010001100",
            "00011111100000111101100110101011",
            "01011011111000001100110100011001"};

        K= {"01000010100010100010111110011000", "01110001001101110100010010010001", "10110101110000001111101111001111", "11101001101101011101101110100101",
            "00111001010101101100001001011011", "01011001111100010001000111110001", "10010010001111111000001010100100", "10101011000111000101111011010101",
            "11011000000001111010101010011000", "00010010100000110101101100000001", "00100100001100011000010110111110", "01010101000011000111110111000011",
            "01110010101111100101110101110100", "10000000110111101011000111111110", "10011011110111000000011010100111", "11000001100110111111000101110100",
            "11100100100110110110100111000001", "11101111101111100100011110000110", "00001111110000011001110111000110", "00100100000011001010000111001100",
            "00101101111010010010110001101111", "01001010011101001000010010101010", "01011100101100001010100111011100", "01110110111110011000100011011010",
            "10011000001111100101000101010010", "10101000001100011100011001101101", "10110000000000110010011111001000", "10111111010110010111111111000111",
            "11000110111000000000101111110011", "11010101101001111001000101000111", "00000110110010100110001101010001", "00010100001010010010100101100111",
            "00100111101101110000101010000101", "00101110000110110010000100111000", "01001101001011000110110111111100", "01010011001110000000110100010011",
            "01100101000010100111001101010100", "01110110011010100000101010111011", "10000001110000101100100100101110", "10010010011100100010110010000101",
            "10100010101111111110100010100001", "10101000000110100110011001001011", "11000010010010111000101101110000", "11000111011011000101000110100011",
            "11010001100100101110100000011001", "11010110100110010000011000100100", "11110100000011100011010110000101", "00010000011010101010000001110000",
            "00011001101001001100000100010110", "00011110001101110110110000001000", "00100111010010000111011101001100", "00110100101100001011110010110101", 
            "00111001000111000000110010110011", "01001110110110001010101001001010", "01011011100111001100101001001111", "01101000001011100110111111110011",
            "01110100100011111000001011101110", "01111000101001010110001101101111", "10000100110010000111100000010100", "10001100110001110000001000001000",
            "10010000101111101111111111111010", "10100100010100000110110011101011", "10111110111110011010001111110111", "11000110011100010111100011110010"};
    }

    void hashString(string st) {
        int size = st.size();
        if (size * 8 > (pow(2, 64) - 64)) {
            cout << "Maximum size exceeded!";
            exit(0);
        }
        int bits = 512;
        bits = calcBits(size);

        string binStr = binConv(st, bits);

        int N = bits / 512;
        vector<string> M;

        mSplit(M, binStr, N);
		
        vector<string> W;
        vector<string> T;
        blockComp(N, M, W, T);
        display();
    }

    void display() {
        cout << endl << "Hash value : ";
        for (int i = 0; i < 8; i++) {
            bitset<32> bits(H[i]);
            stringstream ss;
            ss << hex << setw(8) << setfill('0') << bits.to_ulong();
            string val(ss.str());
            cout << val;
        }
        cout << endl;
    }
};

int main() {
    SHA256 sha256;
    string st;
    cout << "Enter the string : ";
    getline(cin, st);
    sha256.hashString(st);
    return 0;
}

