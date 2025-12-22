#pragma once
#include QMK_KEYBOARD_H

void oled_render_master(void);
void oled_render_slave(void);
bool oled_task_user(void);