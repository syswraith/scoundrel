CC = gcc
CFLAGS =
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

SRC = main.c
OUT = out
BIN = $(OUT)/main

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p $(OUT)
	$(CC) $(SRC) -o $(BIN) $(LIBS)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(OUT)
