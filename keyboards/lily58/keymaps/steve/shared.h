#pragma once
#include QMK_KEYBOARD_H

// Layer enum shared across modules
typedef enum {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
} layer_number;

// Shared global state
typedef struct {
    uint8_t layer;           // current layer
    uint8_t pet_state;       // PET_IDLE=0, PET_WALK=1, PET_RUN=2
    uint8_t menu_index;      // selected menu item
    uint8_t menu_top_index; // The top most visible item
    bool menu_active;        // Show the menu flag
} shared_state_t;

extern shared_state_t shared_state;
