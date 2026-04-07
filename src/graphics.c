#include "graphics.h"

// Terminal graphics - stub implementation
void graphics_init(void) {
}

void graphics_close(void) {
}

void graphics_draw_board(Game* g) {
}

void graphics_draw_menu(void) {
}

void graphics_draw_checkmate(int white_wins) {
}

void graphics_draw_stalemate(void) {
}

void graphics_handle_click(Game* g, int mouse_x, int mouse_y) {
}

Position graphics_get_square_from_mouse(int mouse_x, int mouse_y) {
    Position p = {-1, -1};
    return p;
}

int graphics_in_board_bounds(int mouse_x, int mouse_y) {
    return 0;
}
