#include "SHA256.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

using std::cerr, std::cout, std::string;
using std::ifstream, std::make_unique, std::unique_ptr;
using std::runtime_error, std::istreambuf_iterator;
using std::ios;

void printUsage(const char* prog) {
    cerr << "Usage:\n";
    cerr << "  " << prog << " --ALG-NAME [--SHA256, --SHA1] \"<string>\"\n";
    cerr << "  " << prog << " --ALG-NAME [--SHA256, --SHA1] --FILE <filepath>\n";
}

string readFileContents(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Failed to open file: " + filePath);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }

    string mode = argv[1];
    if (mode != "--SHA256") {
        printUsage(argv[0]);
        return 1;
    }

    unique_ptr<HashAlgorithm> hasher = make_unique<SHA256>();

    try {
        string input;
        if (argc == 3) {
            input = argv[2];
        } else if (argc == 4 && string(argv[2]) == "--FILE") {
            input = readFileContents(argv[3]);
        } else {
            printUsage(argv[0]);
            return 1;
        }

        hasher -> hashString(input);
        hasher -> display();

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}