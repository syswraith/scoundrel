CC := clang++

CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Og -g3 -Iinclude -Werror
LDFLAGS :=

SRC := $(wildcard src/*.cpp)
TARGET := dist/main

VALGRIND := valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--errors-for-leak-kinds=all \
	--error-exitcode=1

.PHONY: all test clean


default: clean all test

all: $(TARGET)

run:
	./$(TARGET)

$(TARGET): $(SRC)
	mkdir -p dist
	$(CC) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

test: $(TARGET)
	$(VALGRIND) ./$(TARGET)

clean:
	rm -rf dist


