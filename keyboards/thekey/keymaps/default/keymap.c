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

#include QMK_KEYBOARD_H

enum custom_keycodes {
    COPYALL = SAFE_RANGE,
    OPEN,
};

const uint16_t PROGMEM copy_all[] = {KC_LCTRL, KC_C, COMBO_END};
const uint16_t PROGMEM switch_to_gaming[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM switch_back[] = {KC_A, KC_SPACE, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(copy_all, COPYALL),
    COMBO(switch_to_gaming, TO(1)),
    COMBO(switch_back, TO(0)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(KC_LCTRL, KC_C, KC_V),
    [1] = LAYOUT(KC_A, KC_SPACE, KC_D)

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case COPYALL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("ac"));
	}
        break;
    }
    return true;
};
