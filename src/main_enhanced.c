#include "game.h"
#include "move.h"
#include "piece.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// ANSI Colors
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define BLACK_BG "\x1b[40m"
#define WHITE_BG "\x1b[47m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define BRIGHT_WHITE "\x1b[97m"
#define BRIGHT_YELLOW "\x1b[93m"

// Unicode Chess Pieces
#define WK "♔" // White King
#define WQ "♕" // White Queen  
#define WR "♖" // White Rook
#define WB "♗" // White Bishop
#define WN "♘" // White Knight
#define WP "♙" // White Pawn
#define BK "♚" // Black King
#define BQ "♛" // Black Queen
#define BR "♜" // Black Rook
#define BB "♝" // Black Bishop
#define BN "♞" // Black Knight
#define BP "♟" // Black Pawn

static void clear_screen(void) {
    system("cls");
}

static void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

static const char* piece_unicode(Piece p) {
    switch(p) {
        case PAWN_W: return WP;
        case ROOK_W: return WR;
        case KNIGHT_W: return WN;
        case BISHOP_W: return WB;
        case QUEEN_W: return WQ;
        case KING_W: return WK;
        case PAWN_B: return BP;
        case ROOK_B: return BR;
        case KNIGHT_B: return BN;
        case BISHOP_B: return BB;
        case QUEEN_B: return BQ;
        case KING_B: return BK;
        default: return " ";
    }
}

static void print_title(void) {
    set_color(14);
    printf("\n");
    printf("  ╔════════════════════════════════════════════╗\n");
    printf("  ║  ");
    set_color(11);
    printf("♔♕♖♗♘♙  CHESS GAME IN C  ♙♘♗♖♕♔");
    set_color(14);
    printf("  ║\n");
    printf("  ║         Professional Terminal Edition      ║\n");
    printf("  ╚════════════════════════════════════════════╝\n\n");
    set_color(7);
}

static void print_menu(void) {
    clear_screen();
    set_color(14);
    printf("\n  ╔════════════════════════════════════════════╗\n");
    printf("  ║           CHESS - MAIN MENU                ║\n");
    printf("  ╚════════════════════════════════════════════╝\n\n");
    set_color(11);
    printf("  ");
    set_color(12);
    printf("▶");
    set_color(11);
    printf("  Type 'play' to start a new game\n");
    printf("  ");
    set_color(12);
    printf("▶");
    set_color(11);
    printf("  Type 'rules' for chess rules\n");
    printf("  ");
    set_color(12);
    printf("▶");
    set_color(11);
    printf("  Type 'quit' to exit\n\n");
    set_color(7);
}

static int parse_move_input(const char *input, Move *m) {
    char from[10], to[10];
    int n = sscanf(input, "%s %s", from, to);
    if (n != 2) return 0;
    if (strlen(from) < 2 || strlen(to) < 2) return 0;
    
    from[0] = tolower((unsigned char)from[0]);
    from[1] = tolower((unsigned char)from[1]);
    to[0] = tolower((unsigned char)to[0]);
    to[1] = tolower((unsigned char)to[1]);
    
    if (from[0] < 'a' || from[0] > 'h' || from[1] < '1' || from[1] > '8') return 0;
    if (to[0] < 'a' || to[0] > 'h' || to[1] < '1' || to[1] > '8') return 0;
    
    m->from.col = from[0] - 'a';
    m->from.row = 8 - (from[1] - '0');
    m->to.col = to[0] - 'a';
    m->to.row = 8 - (to[1] - '0');
    
    return 1;
}

static void print_board_fancy(Game *g) {
    set_color(7);
    printf("\n  ╔──────────────────────────────────────────────────╗\n");
    printf("  ║     a   b   c   d   e   f   g   h             ║\n");
    printf("  ║   ┌───────────────────────────────────────┐   ║\n");
    
    for (int r = 0; r < 8; r++) {
        printf("  ║ ");
        set_color(15);
        printf("%d", 8 - r);
        set_color(7);
        printf("  │");
        
        for (int c = 0; c < 8; c++) {
            Piece p = board_get(g->board, r, c);
            int is_light = (r + c) % 2 == 0;
            
            if (is_light) {
                set_color(7);
                printf(" ");
            } else {
                set_color(8);
                printf("█");
            }
            
            if (p != EMPTY) {
                if (is_white(p)) {
                    set_color(15);
                } else {
                    set_color(0);
                }
                printf("%s", piece_unicode(p));
            } else {
                printf(" ");
            }
            
            if (is_light) {
                set_color(7);
                printf(" ");
            } else {
                set_color(7);
                printf(" ");
            }
        }
        
        set_color(7);
        printf("│ ");
        set_color(15);
        printf("%d", 8 - r);
        set_color(7);
        printf(" ║\n");
    }
    
    printf("  ║   └───────────────────────────────────────┘   ║\n");
    printf("  ║     a   b   c   d   e   f   g   h             ║\n");
    printf("  ╚──────────────────────────────────────────────────╝\n");
}

static void play_game(void) {
    Game *game = game_create();
    if (!game) {
        set_color(12);
        printf("ERROR: Failed to create game\n");
        set_color(7);
        return;
    }
    
    game_reset(game);
    char input[256];
    
    while (game->state != STATE_QUIT) {
        clear_screen();
        print_title();
        print_board_fancy(game);
        
        printf("\n  ");
        set_color(14);
        printf("┌─ STATUS ");
        
        if (game->state == STATE_PLAYING) {
            printf("─ Move #%d ", game->full_moves);
            set_color(7);
            printf("─┐\n");
            printf("  │ ");
            
            if (game->white_turn) {
                set_color(15);
                printf("● WHITE TO MOVE");
            } else {
                set_color(8);
                printf("● BLACK TO MOVE");
            }
            set_color(7);
            printf("                    │\n");
            printf("  └────────────────────────────────────────┘\n");
            printf("\n  ");
            set_color(11);
            printf("Enter move (e.g., e2 e4): ");
            set_color(7);
        } else if (game->state == STATE_CHECKMATE) {
            printf("─ CHECKMATE ");
            set_color(7);
            printf("─┐\n");
            printf("  │ ");
            if (game->white_turn) {
                set_color(8);
                printf("♛ BLACK WINS! ♛");
            } else {
                set_color(15);
                printf("♔ WHITE WINS! ♔");
            }
            set_color(7);
            printf("                |\n");
            printf("  └────────────────────────────────────────┘\n");
            printf("\n  Command (play/quit): ");
        } else if (game->state == STATE_STALEMATE) {
            printf("─ STALEMATE ");
            set_color(7);
            printf("─┐\n");
            printf("  │ ");
            set_color(11);
            printf("═ DRAW - No legal moves");
            set_color(7);
            printf("  ═        │\n");
            printf("  └────────────────────────────────────────┘\n");
            printf("\n  Command (play/quit): ");
        }
        
        if (!fgets(input, sizeof(input), stdin)) break;
        
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        
        if (strlen(input) == 0) continue;
        
        if (strncmp(input, "quit", 4) == 0) {
            game->state = STATE_QUIT;
        } else if (strncmp(input, "reset", 5) == 0) {
            game_reset(game);
        } else if (strncmp(input, "play", 4) == 0) {
            game_reset(game);
        } else if (game->state == STATE_PLAYING) {
            Move m;
            if (parse_move_input(input, &m)) {
                if (game_make_move(game, m)) {
                    set_color(10);
                    printf("\n  ✓ Move accepted!\n");
                    set_color(7);
                    getchar();
                } else {
                    set_color(12);
                    printf("\n  ✗ Illegal move!\n");
                    set_color(7);
                    getchar();
                }
            } else {
                set_color(12);
                printf("\n  ✗ Invalid format! Use: e2 e4\n");
                set_color(7);
                getchar();
            }
        }
    }
    
    game_free(game);
}

int main(void) {
    char input[256];
    
    while (1) {
        print_menu();
        printf("  > ");
        
        if (!fgets(input, sizeof(input), stdin)) break;
        
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        
        if (strncmp(input, "play", 4) == 0) {
            play_game();
        } else if (strncmp(input, "rules", 5) == 0) {
            clear_screen();
            print_title();
            set_color(11);
            printf("  CHESS RULES:\n\n");
            set_color(7);
            printf("  %s PAWN (%s): Moves 1 forward, 2 on first move. Captures diagonally.\n", WP, WP);
            printf("  %s ROOK (%s): Moves horizontally or vertically any distance.\n", WR, WR);
            printf("  %s KNIGHT (%s): Moves in L-shape (2+1 squares).\n", WN, WN);
            printf("  %s BISHOP (%s): Moves diagonally any distance.\n", WB, WB);
            printf("  %s QUEEN (%s): Combines Rook and Bishop movements.\n", WQ, WQ);
            printf("  %s KING (%s): Moves 1 square in any direction.\n\n", WK, WK);
            printf("  CHECK: King is under attack.\n");
            printf("  CHECKMATE: King in check with no legal moves - instant win!\n");
            printf("  STALEMATE: King not in check but no legal moves - draw.\n\n");
            set_color(11);
            printf("  Press ENTER to return...");
            set_color(7);
            getchar();
        } else if (strncmp(input, "quit", 4) == 0) {
            set_color(11);
            printf("\n  Thanks for playing! Goodbye!\n\n");
            set_color(7);
            break;
        } else {
            set_color(12);
            printf("  ✗ Unknown command!\n");
            set_color(7);
            getchar();
        }
    }
    
    return 0;
}
