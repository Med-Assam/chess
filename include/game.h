#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "defines.h"
#include "board.h"

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_CHECKMATE,
    STATE_STALEMATE,
    STATE_QUIT
} GameState;

typedef struct {
    Board* board;
    GameState state;
    int white_turn;
    Move last_move;
    int half_moves;
    int full_moves;
    Position selected;
    int piece_selected;
} Game;

Game* game_create(void);
void game_free(Game* g);
void game_init(Game* g);
void game_reset(Game* g);
int game_make_move(Game* g, Move m);
void game_toggle_turn(Game* g);
int game_is_white_turn(Game* g);

#endif
