#include "piece.h"
#include <ctype.h>

int is_white(Piece p) {
    return p >= PAWN_W && p <= KING_W;
}

int is_black(Piece p) {
    return p >= PAWN_B && p <= KING_B;
}

int is_empty(Piece p) {
    return p == EMPTY;
}

int is_pawn(Piece p) {
    return p == PAWN_W || p == PAWN_B;
}

int is_rook(Piece p) {
    return p == ROOK_W || p == ROOK_B;
}

int is_knight(Piece p) {
    return p == KNIGHT_W || p == KNIGHT_B;
}

int is_bishop(Piece p) {
    return p == BISHOP_W || p == BISHOP_B;
}

int is_queen(Piece p) {
    return p == QUEEN_W || p == QUEEN_B;
}

int is_king(Piece p) {
    return p == KING_W || p == KING_B;
}

char piece_to_char(Piece p) {
    switch (p) {
        case PAWN_W: return 'P';
        case ROOK_W: return 'R';
        case KNIGHT_W: return 'N';
        case BISHOP_W: return 'B';
        case QUEEN_W: return 'Q';
        case KING_W: return 'K';
        case PAWN_B: return 'p';
        case ROOK_B: return 'r';
        case KNIGHT_B: return 'n';
        case BISHOP_B: return 'b';
        case QUEEN_B: return 'q';
        case KING_B: return 'k';
        default: return '.';
    }
}

int same_color(Piece a, Piece b) {
    if (is_empty(a) || is_empty(b)) return 0;
    return (is_white(a) && is_white(b)) || (is_black(a) && is_black(b));
}
