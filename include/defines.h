#ifndef CHESS_DEFINES_H
#define CHESS_DEFINES_H

#define BOARD_SIZE 8
#define SQUARE_SIZE 60
#define BOARD_X 80
#define BOARD_Y 40
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef enum {
    EMPTY = 0,
    PAWN_W, ROOK_W, KNIGHT_W, BISHOP_W, QUEEN_W, KING_W,
    PAWN_B, ROOK_B, KNIGHT_B, BISHOP_B, QUEEN_B, KING_B
} Piece;

typedef struct {
    int row;
    int col;
} Position;

typedef struct {
    Position from;
    Position to;
} Move;

#endif
