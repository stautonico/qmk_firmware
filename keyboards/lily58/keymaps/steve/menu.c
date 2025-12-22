#include "menu.h"
#include "shared.h"
#include "oled.h"
#include "pet.h"

#define MENU_ITEM_COUNT 5
#define OLED_ROWS 4

static const char *menu_items[MENU_ITEM_COUNT] = {
    "MODE",
    "OLED",
    "PET",
    "LOCK",
    "RESET"
};

void menu_render(void) {
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_ln("MENU", false);

    // arrow above if there are items above the window
    if (shared_state.menu_top_index > 0) {
        oled_set_cursor(0, 1);
        oled_write_ln("^", false);
    }

    // draw visible menu items
    for (uint8_t row = 0; row < OLED_ROWS; row++) {
        uint8_t idx = shared_state.menu_top_index + row;
        if (idx >= MENU_ITEM_COUNT) break;

        oled_set_cursor(0, row + 1 + (shared_state.menu_top_index > 0 ? 1 : 0)); // +1 if arrow is shown
        if (idx == shared_state.menu_index) {
            oled_write("> ", false);
        } else {
            oled_write("  ", false);
        }
        oled_write_ln(menu_items[idx], false);
    }

    // arrow below if there are items below the window
    uint8_t last_visible = shared_state.menu_top_index + OLED_ROWS - 1;
    if (last_visible < MENU_ITEM_COUNT - 1) {
        oled_set_cursor(0, OLED_ROWS + (shared_state.menu_top_index > 0 ? 1 : 0));
        oled_write_ln("v", false);
    }
}



void menu_next(void) {
    if (++shared_state.menu_index >= MENU_ITEM_COUNT)
        shared_state.menu_index = 0;

    // make sure the selected item is visible
    if (shared_state.menu_index >= shared_state.menu_top_index + OLED_ROWS) {
        shared_state.menu_top_index = shared_state.menu_index - OLED_ROWS + 1;
    }
}

void menu_prev(void) {
    if (shared_state.menu_index == 0)
        shared_state.menu_index = MENU_ITEM_COUNT - 1;
    else
        shared_state.menu_index--;

    if (shared_state.menu_index < shared_state.menu_top_index) {
        shared_state.menu_top_index = shared_state.menu_index;
    }
}

void menu_select(void) {
    switch (shared_state.menu_index) {
        case 0:  // MODE
            layer_invert(_ADJUST);
            break;
        case 1:  // OLED
            oled_off();
            break;
        case 2:  // PET
            break;
        case 3:  // LOCK
            break;
        case 4:  // RESET
            soft_reset_keyboard();
            break;
    }
}
