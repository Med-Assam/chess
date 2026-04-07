#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "defines.h"
#include "board.h"

int is_valid_move(Board* b, Move m, int white_turn);
int is_in_check(Board* b, int white);
int is_in_checkmate(Board* b, int white);
int is_in_stalemate(Board* b, int white);
int can_move_piece(Board* b, Position from, int white_turn);
int has_legal_moves(Board* b, int white);

#endif
