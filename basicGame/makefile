CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17 $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib) -lm

TARGET = game
SRC = main.cpp
HEADERS = $(wildcard *.hpp)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
