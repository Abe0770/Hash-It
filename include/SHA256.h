// SHA256.h

#ifndef SHA256_H
#define SHA256_H

#include "HashAlgorithm.h"
#include "SHAUtils.h"
#include <vector>
#include <string>

using std::vector, std::string;

class SHA256 : public HashAlgorithm {
public:
    SHA256();
    void hashString(const string &input) override;
    void display() const override;

private:
    vector <string> H;
    vector <string> K;

    int calcBits(int size);
    void mSplit(vector <string> &M, const string &binStr, int N);

    string sigma(const string &s, int a1, int a2, int a3);
    string SIGMA(const string &s, int a1, int a2, int a3);
    string choose(const string &e, const string &f, const string &g);
    string maj(const string &a, const string &b, const string &c);
    void blockComp(int N, const vector <string> &M, vector <string> &W);
};

#endif