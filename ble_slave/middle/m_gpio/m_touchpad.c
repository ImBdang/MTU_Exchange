#include "m_gpio.h"
#include "hardware.h"
#include "app_btn.h"
#include "timer.h"
#include "tlkapi_debug.h"
#include "app_config.h"

uint8_t g_btn_filter_cnt = 4;

static const GPIO_PinTypeDef leds_1[] = { LED_PAD_1, LED_PAD_4 };
static const GPIO_PinTypeDef leds_2[] = { LED_PAD_2 };
static const GPIO_PinTypeDef leds_3[] = { LED_PAD_3 }; //BT3, 
static const GPIO_PinTypeDef leds_4[] = { LED_PAD_1, LED_PAD_4 }; //BT4

static app_btn_hw_config_t list_touchpads_hw[] = {
    { .pin = TOUCHPAD_1, .idle_level = 1, .last_state = 1, .debounce_val = 1, .debounce_counter = 0,
      .pin_num = 2, .led_pins = leds_1 },

    { .pin = TOUCHPAD_2, .idle_level = 1, .last_state = 1, .debounce_val = 1, .debounce_counter = 0,
      .pin_num = 1, .led_pins = leds_2 },

    { .pin = TOUCHPAD_3, .idle_level = 1, .last_state = 1, .debounce_val = 1, .debounce_counter = 0,
      .pin_num = 1, .led_pins = leds_3 },

    { .pin = TOUCHPAD_4, .idle_level = 1, .last_state = 1, .debounce_val = 1, .debounce_counter = 0,
      .pin_num = 2, .led_pins = leds_4 },
};

extern void nus_notify_3switch_state(u8 s1, u8 s2, u8 s3);
extern 	u32	latest_user_event_tick;
extern u8 g_led_state[4];

extern void update_scanrsp_led_state(void);
extern void update_adv_led_state(void);

static inline void update_user_event_tick(void)
{
    latest_user_event_tick = clock_time(); 
}

static inline void tp_notify(void)
{
    nus_notify_3switch_state(g_led_state[1], g_led_state[2], g_led_state[3]);
}

void touchpad_led_set_by_id(uint8_t id, uint8_t on)
{
    if (id < 1 || id > 3) return;

    app_btn_hw_config_t *cfg = &list_touchpads_hw[id - 1];

    if (on) m_set_led_on(cfg->led_pins, cfg->pin_num);
    else    m_set_led_off(cfg->led_pins, cfg->pin_num);

    g_led_state[id] = on ? 1 : 0;
    // tp_notify();
}

static app_btn_config_t touchpad_config = {
    .config = list_touchpads_hw,
    .btn_count = (sizeof(list_touchpads_hw) / sizeof(list_touchpads_hw[0])),
    .btn_initialize = hw_touchpad_cfg,
    .btn_read = hw_btn_read,
    .get_tick_cb = telink_get_tick,
};

static void cb_pressed(int pin, int type, void *data)
{
    (void)type;
    (void)data;
    update_user_event_tick();
    for (unsigned i = 0; i < MAX_TOUCHPAD; i++)
    {
        if (pin == list_touchpads_hw[i].pin)
        {
            u8 id = i + 1;
            g_led_state[id] ^= 1;
            if (g_led_state[id])    m_set_led_on(list_touchpads_hw[i].led_pins, list_touchpads_hw[i].pin_num);
            else                    m_set_led_off(list_touchpads_hw[i].led_pins, list_touchpads_hw[i].pin_num);
            tp_notify();
            break;
        }
    }
    // update_scanrsp_led_state();
    update_adv_led_state();
}


static void cb_released(int pin, int type, void *data)
{
    (void)pin;
    (void)type;
    (void)data;
    update_user_event_tick();
    tlkapi_printf(UART_PRINT_DEBUG_ENABLE, "RELEASED CALLBACK\r\n");
}

static void cb_hold(int pin, int type, void *data)
{
    (void)pin;
    (void)type;
    (void)data;
    update_user_event_tick();
    tlkapi_printf(UART_PRINT_DEBUG_ENABLE, "HOLD CALLBACK\r\n");
}

static void cb_hold_long(int pin, int type, void *data)
{
    (void)pin;
    (void)type;
    (void)data;
    update_user_event_tick();
    tlkapi_printf(UART_PRINT_DEBUG_ENABLE, "HOLD LONG CALLBACK\r\n");
}

static void cb_double_click(int pin, int type, void *data)
{
    (void)pin;
    (void)type;
    (void)data;
}

static void cb_triple_click(int pin, int type, void *data)
{
    (void)pin;
    (void)type;
    (void)data;
}

static void cb_idle(int pin, int type, void *data)
{
    (void)pin;
    (void)type;
    (void)data;
}

static void cb_idle_break(int pin, int type, void *data)
{
    (void)pin;
    (void)type;
    (void)data;
}

static void btn_register_all_callbacks(void)
{
    app_btn_register_callback(APP_BTN_EVT_PRESSED,   cb_pressed,   NULL);
    app_btn_register_callback(APP_BTN_EVT_RELEASED,  cb_released,  NULL);
    app_btn_register_callback(APP_BTN_EVT_HOLD,      cb_hold,      NULL);
    app_btn_register_callback(APP_BTN_EVT_HOLD_LONG, cb_hold_long, NULL);

    /* app_btn_register_callback(APP_BTN_EVT_DOUBLE_CLICK, cb_double_click, NULL); */
    /* app_btn_register_callback(APP_BTN_EVT_TRIPLE_CLICK, cb_triple_click, NULL); */
    /* app_btn_register_callback(APP_BTN_EVT_IDLE,         cb_idle,         NULL); */
    /* app_btn_register_callback(APP_BTN_EVT_IDLE_BREAK,   cb_idle_break,   NULL); */
}


void touchpad_proc(void)
{
    static u32 tick = 0;
    if (!clock_time_exceed(tick, 5000)) return;  
    tick = clock_time();
    app_btn_scan(NULL);
}

static void touchpad_led_restore_all(void)
{
    for (u8 i = 0; i < 3; i++) {
        u8 id = i + 1;
        if (g_led_state[id]) m_set_led_on(list_touchpads_hw[i].led_pins, list_touchpads_hw[i].pin_num);
        else                 m_set_led_off(list_touchpads_hw[i].led_pins, list_touchpads_hw[i].pin_num);
    }
}

void touchpad_init(void)
{
    app_btn_initialize(&touchpad_config);
    touchpad_led_restore_all();
    btn_register_all_callbacks();
}
