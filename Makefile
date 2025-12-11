# MAKEFILE
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC_DIR = src
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/SHA1.cpp \
       $(SRC_DIR)/SHA256.cpp \
       $(SRC_DIR)/SHAUtils.cpp \
       $(SRC_DIR)/TerminalUtils.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = getHash

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean
