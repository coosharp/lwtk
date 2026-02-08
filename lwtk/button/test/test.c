#include <stdio.h>
#include "../inc/lw_btn.h"

static void btn_event_cb(lw_btn_event_dsc_t * event_dsc)
{
    lw_btn_event_t code = lw_btn_get_event_code(event_dsc);

    switch (code) {
        case LW_BTN_EVENT_PRESSED:
            printf("button pressed\n");
            break;
        case LW_BTN_EVENT_LONG_PRESSED:
            printf("button long pressed\n");
            break;
        case LW_BTN_EVENT_LONG_LONG_PRESSED:
            printf("button long long pressed\n");
            break;
        default:
            printf("button event %d\n", code);
            break;
    }
}

static bool btn_is_pressed(uint8_t button_id)
{
    return true;
}

int main(void)
{
    lw_btn_t btns[10] = {0};

    lw_btn_init(btns, sizeof(btns));

    lw_btn_t * btn1 = lw_btn_create(1, btn_is_pressed);
    lw_btn_long_long_press_en(btn1, true);
    lw_btn_add_event(btn1, LW_BTN_EVENT_PRESSED, btn_event_cb, NULL);
    lw_btn_add_event(btn1, LW_BTN_EVENT_LONG_PRESSED, btn_event_cb, NULL);
    lw_btn_add_event(btn1, LW_BTN_EVENT_LONG_LONG_PRESSED, btn_event_cb, NULL);

    for(int i = 0; i < 0xFFFF; i++) {
        lw_btn_handler();
        lw_btn_increase_tick(1);
    }

    return 0;
}