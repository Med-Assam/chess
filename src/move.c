#include "move.h"
#include "piece.h"
#include <stdlib.h>

static int clear_path(Board* b, Position from, Position to) {
    int dr = 0, dc = 0;
    if (to.row > from.row) dr = 1;
    else if (to.row < from.row) dr = -1;
    
    if (to.col > from.col) dc = 1;
    else if (to.col < from.col) dc = -1;
    
    int r = from.row + dr;
    int c = from.col + dc;
    
    while (r != to.row || c != to.col) {
        if (!is_empty(board_get(b, r, c))) return 0;
        r += dr;
        c += dc;
    }
    return 1;
}

static int is_valid_pawn_move(Board* b, Move m, int white) {
    Piece p = board_get(b, m.from.row, m.from.col);
    Piece dest = board_get(b, m.to.row, m.to.col);
    
    int dir = white ? -1 : 1;
    int start_row = white ? 6 : 1;
    
    if (m.to.col == m.from.col) {
        if (m.to.row == m.from.row + dir && is_empty(dest)) return 1;
        if (m.from.row == start_row && m.to.row == m.from.row + 2 * dir 
            && is_empty(dest) && is_empty(board_get(b, m.from.row + dir, m.from.col))) {
            return 1;
        }
    } else if (m.to.col == m.from.col + 1 || m.to.col == m.from.col - 1) {
        if (m.to.row == m.from.row + dir && !is_empty(dest) && !same_color(p, dest)) {
            return 1;
        }
    }
    return 0;
}

static int is_valid_knight_move(Move m) {
    int dr = abs(m.to.row - m.from.row);
    int dc = abs(m.to.col - m.from.col);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

static int is_valid_bishop_move(Board* b, Move m) {
    if (abs(m.to.row - m.from.row) != abs(m.to.col - m.from.col)) return 0;
    return clear_path(b, m.from, m.to);
}

static int is_valid_rook_move(Board* b, Move m) {
    if (m.from.row != m.to.row && m.from.col != m.to.col) return 0;
    return clear_path(b, m.from, m.to);
}

static int is_valid_queen_move(Board* b, Move m) {
    if (m.from.row == m.to.row || m.from.col == m.to.col) {
        return clear_path(b, m.from, m.to);
    }
    if (abs(m.to.row - m.from.row) == abs(m.to.col - m.from.col)) {
        return clear_path(b, m.from, m.to);
    }
    return 0;
}

static int is_valid_king_move(Move m) {
    int dr = abs(m.to.row - m.from.row);
    int dc = abs(m.to.col - m.from.col);
    return dr <= 1 && dc <= 1 && (dr != 0 || dc != 0);
}

int is_valid_move(Board* b, Move m, int white_turn) {
    if (!b) return 0;
    if (m.from.row < 0 || m.from.row >= 8 || m.from.col < 0 || m.from.col >= 8) return 0;
    if (m.to.row < 0 || m.to.row >= 8 || m.to.col < 0 || m.to.col >= 8) return 0;
    if (m.from.row == m.to.row && m.from.col == m.to.col) return 0;
    
    Piece p = board_get(b, m.from.row, m.from.col);
    Piece dest = board_get(b, m.to.row, m.to.col);
    
    if (is_empty(p)) return 0;
    if (white_turn && !is_white(p)) return 0;
    if (!white_turn && !is_black(p)) return 0;
    if (same_color(p, dest)) return 0;
    
    int valid = 0;
    if (is_pawn(p)) {
        valid = is_valid_pawn_move(b, m, white_turn);
    } else if (is_knight(p)) {
        valid = is_valid_knight_move(m);
    } else if (is_bishop(p)) {
        valid = is_valid_bishop_move(b, m);
    } else if (is_rook(p)) {
        valid = is_valid_rook_move(b, m);
    } else if (is_queen(p)) {
        valid = is_valid_queen_move(b, m);
    } else if (is_king(p)) {
        valid = is_valid_king_move(m);
    }
    
    return valid;
}

int is_in_check(Board* b, int white) {
    if (!b) return 0;
    
    Position king_pos = {-1, -1};
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece p = board_get(b, r, c);
            if (is_king(p) && ((white && is_white(p)) || (!white && is_black(p)))) {
                king_pos.row = r;
                king_pos.col = c;
                break;
            }
        }
        if (king_pos.row != -1) break;
    }
    
    if (king_pos.row == -1) return 0;
    
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece p = board_get(b, r, c);
            if (!is_empty(p) && ((white && is_black(p)) || (!white && is_white(p)))) {
                Move m = {{r, c}, king_pos};
                if (is_valid_move(b, m, !white)) return 1;
            }
        }
    }
    return 0;
}

int is_in_checkmate(Board* b, int white) {
    if (!is_in_check(b, white)) return 0;
    return !has_legal_moves(b, white);
}

int is_in_stalemate(Board* b, int white) {
    if (is_in_check(b, white)) return 0;
    return !has_legal_moves(b, white);
}

int can_move_piece(Board* b, Position from, int white_turn) {
    if (!b) return 0;
    Piece p = board_get(b, from.row, from.col);
    if (is_empty(p)) return 0;
    if (white_turn && !is_white(p)) return 0;
    if (!white_turn && !is_black(p)) return 0;
    return 1;
}

int has_legal_moves(Board* b, int white) {
    if (!b) return 0;
    
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece p = board_get(b, r, c);
            if (!is_empty(p) && ((white && is_white(p)) || (!white && is_black(p)))) {
                for (int tr = 0; tr < 8; tr++) {
                    for (int tc = 0; tc < 8; tc++) {
                        Move m = {{r, c}, {tr, tc}};
                        if (is_valid_move(b, m, white)) {
                            Board* temp = board_create();
                            if (!temp) continue;
                            
                            for (int i = 0; i < 8; i++) {
                                for (int j = 0; j < 8; j++) {
                                    temp->board[i][j] = board_get(b, i, j);
                                }
                            }
                            board_move(temp, m);
                            
                            if (!is_in_check(temp, white)) {
                                board_free(temp);
                                return 1;
                            }
                            board_free(temp);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
