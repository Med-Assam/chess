#include "game.h"
#include "move.h"
#include "piece.h"
#include "board.h"
#include "graphics.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SCREEN_MENU,
    SCREEN_GAME,
    SCREEN_GAME_OVER
} GameScreen;

int main(void) {
    graphics_init();
    
    Game *game = game_create();
    if (!game) {
        fprintf(stderr, "ERROR: Failed to create game\n");
        return 1;
    }
    
    game_reset(game);
    
    GameScreen screen = SCREEN_MENU;
    int game_over_winner = 0;
    
    while (!WindowShouldClose()) {
        // Handle ESC key globally
        if (IsKeyPressed(KEY_ESCAPE)) {
            if (screen == SCREEN_GAME || screen == SCREEN_GAME_OVER) {
                screen = SCREEN_MENU;
                game_reset(game);
            } else if (screen == SCREEN_MENU) {
                break;
            }
        }
        
        // Handle SPACE on game over screen
        if (screen == SCREEN_GAME_OVER && IsKeyPressed(KEY_SPACE)) {
            screen = SCREEN_GAME;
            game_reset(game);
        }
        
        BeginDrawing();
        
        switch (screen) {
            case SCREEN_MENU:
                graphics_draw_menu();
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    screen = SCREEN_GAME;
                    game_reset(game);
                }
                break;
                
            case SCREEN_GAME:
                graphics_draw_board(game);
                
                // Handle mouse clicks
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    graphics_handle_click(game, GetMouseX(), GetMouseY());
                }
                
                // Check game state
                if (game->state == CHECKMATE) {
                    game_over_winner = (game->current_player == WHITE) ? 0 : 1;
                    screen = SCREEN_GAME_OVER;
                } else if (game->state == STALEMATE) {
                    screen = SCREEN_GAME_OVER;
                }
                break;
                
            case SCREEN_GAME_OVER:
                if (game->state == CHECKMATE) {
                    graphics_draw_checkmate(game_over_winner);
                } else {
                    graphics_draw_stalemate();
                }
                break;
        }
        
        EndDrawing();
    }
    
    graphics_close();
    game_free(game);
    
    return 0;
}
