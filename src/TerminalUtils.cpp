// TerminalUtils.cpp

#include "TerminalUtils.h"
#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#endif
#include <cstdio>

namespace terminal {
    bool clearICanon() {
#ifdef _WIN32
        return true; // No-op for Windows for now
#else
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
#endif
    }
}
