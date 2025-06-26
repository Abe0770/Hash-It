// HashAlgorithm.h

#ifndef HASHALGORITHM_H
#define HASHALGORITHM_H

#include <string>
using std::string;

class HashAlgorithm {
public:
    virtual void hashString(const string &input) = 0;
    virtual void display() const = 0;
    virtual ~HashAlgorithm() = default;
};

#endif