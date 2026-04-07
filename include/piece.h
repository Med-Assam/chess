#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "defines.h"
#include "board.h"

int is_white(Piece p);
int is_black(Piece p);
int is_empty(Piece p);
int is_pawn(Piece p);
int is_rook(Piece p);
int is_knight(Piece p);
int is_bishop(Piece p);
int is_queen(Piece p);
int is_king(Piece p);

char piece_to_char(Piece p);
int same_color(Piece a, Piece b);

#endif
