CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
INCLUDE = -Iinclude
LIBS = -lm

SRC = src/main.c src/game.c src/board.c src/piece.c src/move.c src/graphics.c
OBJ = $(SRC:.c=.o)
OUTPUT = chess.exe

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUTPUT) $(LIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	del /Q src\*.o chess.exe 2>nul || true

run: $(OUTPUT)
	.\chess.exe

.PHONY: all clean run
