// SHA1.h

#ifndef SHA1_H
#define SHA1_H

#include "HashAlgorithm.h"
#include "SHAUtils.h"
#include <vector>
#include <string>

using std::vector, std::string;

class SHA1 : public HashAlgorithm {
public:
    SHA1();
    void hashString(const string &input) override;
    void display() const override;

private:
    vector <string> H;
    
    unsigned long f(int t, unsigned long B, unsigned long C, unsigned long D);
    unsigned long k(int t);
    void blockComp(const vector <string> &M);
};

#endif