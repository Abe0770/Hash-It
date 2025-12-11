// TerminalUtils.cpp

#include "TerminalUtils.h"
#include <termios.h>
#include <unistd.h>
#include <cstdio>

namespace terminal {
    bool clearICanon() {
        struct termios settings;
        if (tcgetattr(STDIN_FILENO, &settings) < 0) {
            std::perror("tcgetattr failed");
            return false;
        }
        settings.c_lflag &= ~ICANON;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) < 0) {
            std::perror("tcsetattr failed");
            return false;
        }
        return true;
    }
}
