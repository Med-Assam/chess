#include "board.h"
#include "piece.h"
#include <stdlib.h>
#include <stdio.h>

Board* board_create(void) {
    Board* b = (Board*)malloc(sizeof(Board));
    if (!b) return NULL;
    board_init(b);
    return b;
}

void board_free(Board* b) {
    if (b) free(b);
}

void board_init(Board* b) {
    if (!b) return;
    
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            b->board[r][c] = EMPTY;
        }
    }
    
    // Black pieces (top)
    b->board[0][0] = ROOK_B;
    b->board[0][1] = KNIGHT_B;
    b->board[0][2] = BISHOP_B;
    b->board[0][3] = QUEEN_B;
    b->board[0][4] = KING_B;
    b->board[0][5] = BISHOP_B;
    b->board[0][6] = KNIGHT_B;
    b->board[0][7] = ROOK_B;
    
    for (int c = 0; c < BOARD_SIZE; c++) {
        b->board[1][c] = PAWN_B;
    }
    
    // White pieces (bottom)
    for (int c = 0; c < BOARD_SIZE; c++) {
        b->board[6][c] = PAWN_W;
    }
    
    b->board[7][0] = ROOK_W;
    b->board[7][1] = KNIGHT_W;
    b->board[7][2] = BISHOP_W;
    b->board[7][3] = QUEEN_W;
    b->board[7][4] = KING_W;
    b->board[7][5] = BISHOP_W;
    b->board[7][6] = KNIGHT_W;
    b->board[7][7] = ROOK_W;
}

void board_print(Board* b) {
    if (!b) return;
    printf("\n   a b c d e f g h\n");
    for (int r = 0; r < BOARD_SIZE; r++) {
        printf(" %d ", 8 - r);
        for (int c = 0; c < BOARD_SIZE; c++) {
            printf("%c ", piece_to_char(b->board[r][c]));
        }
        printf("%d\n", 8 - r);
    }
    printf("   a b c d e f g h\n\n");
}

Piece board_get(Board* b, int row, int col) {
    if (!b || row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return EMPTY;
    }
    return b->board[row][col];
}

void board_set(Board* b, int row, int col, Piece p) {
    if (!b || row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return;
    }
    b->board[row][col] = p;
}

void board_move(Board* b, Move m) {
    if (!b) return;
    Piece p = board_get(b, m.from.row, m.from.col);
    board_set(b, m.to.row, m.to.col, p);
    board_set(b, m.from.row, m.from.col, EMPTY);
}

void board_reset(Board* b) {
    if (b) board_init(b);
}
