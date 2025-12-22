#include "pet.h"
#include "timer.h"
#include "frames.h"

uint32_t anim_timer = 0;
uint8_t curr_anim_frame = 0;

void render_bongo_cat(void) {
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();

        if (get_current_wpm() < READY_SPEED) {
            oled_write_raw_P(ready_frame, ANIM_SIZE);
        } else if (get_current_wpm() >= TAP_SPEED) {
            curr_anim_frame = (curr_anim_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(animation_frames[abs((TAP_FRAMES - 1) - curr_anim_frame)], ANIM_SIZE);
        } else {
            oled_write_raw_P(waiting_frame, ANIM_SIZE);
        }
    }
}
