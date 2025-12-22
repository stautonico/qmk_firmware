#include "oled.h"
#include "shared.h"
#include "pet.h"
#include "menu.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return is_keyboard_master() ? rotation : OLED_ROTATION_180;
}

void oled_render_master(void) {
    oled_clear();
    oled_set_cursor(0, 0);

    oled_write("LAYER: ", false);
    switch (shared_state.layer) {
        case _QWERTY: oled_write_ln("QWERTY", false); break;
        case _LOWER:  oled_write_ln("LOWER", false);  break;
        case _RAISE:  oled_write_ln("RAISE", false);  break;
        case _ADJUST: oled_write_ln("ADJUST", false); break;
        default:      oled_write_ln("UNDEF", false); break;
    }

    // oled_write_ln("", false);
    oled_write("WPM: ", false);
    oled_write_ln(get_u8_str(get_current_wpm(), ' '), false);
    char buf[16];
    snprintf(buf, sizeof(buf), "Firmware: %s", FIRMWARE_VERSION);
    oled_write_ln(buf, false);
}

void oled_render_slave(void) {
    render_bongo_cat();
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        if (shared_state.menu_active) {
            menu_render();
        } else {
            oled_render_master();
        }
    } else {
        oled_render_slave();
    }
    return false;
}

#endif
