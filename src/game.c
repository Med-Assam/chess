#include "game.h"
#include "move.h"
#include <stdlib.h>

Game* game_create(void) {
    Game* g = (Game*)malloc(sizeof(Game));
    if (!g) return NULL;
    g->board = board_create();
    if (!g->board) {
        free(g);
        return NULL;
    }
    game_init(g);
    return g;
}

void game_free(Game* g) {
    if (g) {
        if (g->board) board_free(g->board);
        free(g);
    }
}

void game_init(Game* g) {
    if (!g) return;
    g->state = STATE_MENU;
    g->white_turn = 1;
    g->last_move.from.row = -1;
    g->last_move.from.col = -1;
    g->half_moves = 0;
    g->full_moves = 1;
    g->selected.row = -1;
    g->selected.col = -1;
    g->piece_selected = 0;
    board_init(g->board);
}

void game_reset(Game* g) {
    if (g) {
        board_reset(g->board);
        g->white_turn = 1;
        g->state = STATE_PLAYING;
        g->selected.row = -1;
        g->selected.col = -1;
        g->piece_selected = 0;
        g->half_moves = 0;
        g->full_moves = 1;
    }
}

int game_make_move(Game* g, Move m) {
    if (!g || !g->board) return 0;
    
    if (!is_valid_move(g->board, m, g->white_turn)) {
        return 0;
    }
    
    Board* temp = board_create();
    if (!temp) return 0;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            temp->board[i][j] = board_get(g->board, i, j);
        }
    }
    board_move(temp, m);
    
    if (is_in_check(temp, g->white_turn)) {
        board_free(temp);
        return 0;
    }
    board_free(temp);
    
    board_move(g->board, m);
    g->last_move = m;
    g->half_moves++;
    
    if (!g->white_turn) {
        g->full_moves++;
    }
    
    game_toggle_turn(g);
    
    if (is_in_checkmate(g->board, g->white_turn)) {
        g->state = STATE_CHECKMATE;
    } else if (is_in_stalemate(g->board, g->white_turn)) {
        g->state = STATE_STALEMATE;
    }
    
    return 1;
}

void game_toggle_turn(Game* g) {
    if (g) g->white_turn = !g->white_turn;
}

int game_is_white_turn(Game* g) {
    return g ? g->white_turn : 0;
}
