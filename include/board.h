#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "defines.h"

typedef struct {
    Piece board[BOARD_SIZE][BOARD_SIZE];
} Board;

Board* board_create(void);
void board_free(Board* b);
void board_init(Board* b);
void board_print(Board* b);
Piece board_get(Board* b, int row, int col);
void board_set(Board* b, int row, int col, Piece p);
void board_move(Board* b, Move m);
void board_reset(Board* b);

#endif
