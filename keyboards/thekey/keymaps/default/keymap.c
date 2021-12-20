/* Copyright 2021 Joe Maples <joe@maples.dev>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/*
 * Layer 1: 'Menu Mode'
 * Combos:
 *    1 + 2: Terraria Mode
 *    2 + 3: Reserved
 *    1 + 3: Reserved
 *    1 + 2 + 3: Discord
 *
 * To return from any mode, press all three keys (returns to 'Menu Mode')
*/

#include QMK_KEYBOARD_H

enum custom_keycodes {
    COPYALL = SAFE_RANGE,
    MENU_ONE,
    MENU_TWO,
    MENU_THREE,
    // Discord Layer
    EXIT_DISCORD_KEY,
    DISCORD_MUTE,
    DISCORD_DEAFEN
};

enum combo_events {
  TO_DISCORD,
  EXIT_DISCORD,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM discord[] = {MENU_ONE, MENU_TWO, MENU_THREE, COMBO_END};

combo_t key_combos[] = {
    [TO_DISCORD]= COMBO_ACTION(discord),
//    COMBO(discord, TO(1)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(MENU_ONE, MENU_TWO, MENU_THREE),
    [1] = LAYOUT(EXIT_DISCORD_KEY, DISCORD_MUTE, DISCORD_DEAFEN)

};


void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case TO_DISCORD:
            if (pressed){
                SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT(SS_LGUI("q"))))); // Enter notif mode
                SEND_STRING("w"); // Discord notif
                layer_move(1);
            }
            break;
    } // END SWITCH
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DISCORD_MUTE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT("m"))));
        }
        break;

    case DISCORD_DEAFEN:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT("d"))));
        }

    case EXIT_DISCORD_KEY:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT(SS_LGUI("q"))))); // Enter notif mode
            SEND_STRING("q"); // Menu notif
            layer_move(0);
        }
        break;

    } // END SWITCH
    return true;
};
