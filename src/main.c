#include "game.h"
#include "move.h"
#include "piece.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

static void clear_screen(void) {
    system("cls");
}

static void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

static void print_title(void) {
    set_color(14); // Yellow
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║       ♟  CHESS GAME IN C  ♟          ║\n");
    printf("║     Click & Move with Mouse           ║\n");
    printf("║     Full 3D-Like Experience          ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    set_color(7); // White
}

static void print_menu(void) {
    clear_screen();
    set_color(14); // Yellow
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║        CHESS - MAIN MENU              ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    set_color(11); // Cyan
    printf("  ► Type 'play' to start a new game\n");
    printf("  ► Type 'rules' for chess rules\n");
    printf("  ► Type 'quit' to exit\n\n");
    set_color(7);
}

static int parse_move_input(const char *input, Move *m) {
    char from[10], to[10];
    int n = sscanf(input, "%s %s", from, to);
    if (n != 2) {
        return 0;
    }
    
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
    set_color(7); // White default
    printf("\n  ╔─────────────────────────────────────────╗\n");
    printf("  ║   a   b   c   d   e   f   g   h       ║\n");
    
    for (int r = 0; r < 8; r++) {
        printf("  ║ ");
        set_color(15); // Bright white for row number
        printf("%d", 8 - r);
        set_color(7);
        printf(" ");
        
        for (int c = 0; c < 8; c++) {
            // Highlight selected square
            if (g->piece_selected && g->selected.row == r && g->selected.col == c) {
                set_color(10); // Green
            } else {
                set_color(7); // White
            }
            
            Piece p = board_get(g->board, r, c);
            char piece_char = piece_to_char(p);
            
            if (!is_empty(p)) {
                if (is_white(p)) {
                    set_color(15); // Bright white 
                } else {
                    set_color(8); // Dark gray
                }
                printf("[%c]", piece_char);
            } else {
                set_color(7);
                printf(" . ");
            }
        }
        set_color(7);
        printf(" ║ ");
        set_color(15);
        printf("%d\n", 8 - r);
        set_color(7);
    }
    
    printf("  ║   a   b   c   d   e   f   g   h       ║\n");
    printf("  ╚─────────────────────────────────────────╝\n");
}

static void play_game(void) {
    Game *game = game_create();
    if (!game) {
        set_color(12); // Red
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
        
        set_color(14); // Yellow
        printf("\n  Status: ");
        
        if (game->state == STATE_PLAYING) {
            if (game->white_turn) {
                set_color(15); // Bright white
                printf("WHITE'S TURN");
            } else {
                set_color(8); // Dark gray
                printf("BLACK'S TURN");
            }
            set_color(7);
            printf("  |  Move #%d\n", game->full_moves);
            printf("\n  Enter move (e.g., e2 e4): ");
        } else if (game->state == STATE_CHECKMATE) {
            set_color(12); // Red
            printf("*** CHECKMATE ***");
            set_color(7);
            if (game->white_turn) {
                set_color(8);
                printf(" BLACK WINS!\n");
            } else {
                set_color(15);
                printf(" WHITE WINS!\n");
            }
            set_color(7);
            printf("\n  Command (play/quit): ");
        } else if (game->state == STATE_STALEMATE) {
            set_color(11); // Cyan
            printf("*** STALEMATE ***");
            set_color(7);
            printf(" DRAW!\n\n  Command (play/quit): ");
        }
        
        if (!fgets(input, sizeof(input), stdin)) break;
        
        // Trim newline
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        
        if (strlen(input) == 0) continue;
        
        // Commands
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
                    set_color(10); // Green
                    printf("✓ Move accepted!\n");
                    set_color(7);
                    getchar();
                } else {
                    set_color(12); // Red
                    printf("✗ Illegal move!\n");
                    set_color(7);
                    getchar();
                }
            } else {
                set_color(12); // Red
                printf("✗ Invalid format! Use: e2 e4\n");
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
            set_color(11); // Cyan
            printf("CHESS RULES:\n\n");
            set_color(7);
            printf("  • PAWN (P/p): Moves 1 forward, 2 on first move. Captures diagonally.\n");
            printf("  • ROOK (R/r): Moves horizontally or vertically any distance.\n");
            printf("  • KNIGHT (N/n): Moves in L-shape (2+1 squares).\n");
            printf("  • BISHOP (B/b): Moves diagonally any distance.\n");
            printf("  • QUEEN (Q/q): Combines Rook and Bishop movements.\n");
            printf("  • KING (K/k): Moves 1 square in any direction.\n\n");
            printf("  • CHECK: King is under attack.\n");
            printf("  • CHECKMATE: King is in check with no legal moves - instant win!\n");
            printf("  • STALEMATE: King not in check but has no legal moves - draw.\n\n");
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
            printf("  Unknown command!\n");
            set_color(7);
            getchar();
        }
    }
    
    return 0;
}
