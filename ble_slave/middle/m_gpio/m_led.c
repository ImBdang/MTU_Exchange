#include "m_gpio.h"
#include "hardware.h"

_attribute_data_retention_ u8 g_led_state[4] = {0};

u8* gen_str_led_state(void)
{
    static u8 msg[7];
    msg[0] = '1'; msg[1] = g_led_state[1] ? '1' : '0';
    msg[2] = '2'; msg[3] = g_led_state[2] ? '1' : '0';
    msg[4] = '3'; msg[5] = g_led_state[3] ? '1' : '0';
    msg[6] = '\0';    

    return msg;
}

void m_set_led_on(const GPIO_PinTypeDef* led_pins, u8 num)
{
    for (uint8_t i = 0; i < num; i++) {
        gpio_write(led_pins[i], LED_ACTIVE);
    }
}

void m_set_led_off(const GPIO_PinTypeDef* led_pins, u8 num)
{
    for (uint8_t i = 0; i < num; i++) {
        gpio_write(led_pins[i], LED_IDLE);
    }
}

void m_set_led_toggle(GPIO_PinTypeDef led_pin)
{
    gpio_toggle(led_pin);
}


static void led_pin_init(GPIO_PinTypeDef pin)
{
    gpio_set_func(pin, AS_GPIO);

    gpio_set_input_en(pin, 0);
    gpio_set_output_en(pin, 1);

    gpio_setup_up_down_resistor(pin, PM_PIN_UP_DOWN_FLOAT);

    gpio_write(pin, LED_IDLE);
}

void led_init_all(void)
{
    led_pin_init(LED_STT);
    led_pin_init(LED_PAD_1);
    led_pin_init(LED_PAD_2);
    led_pin_init(LED_PAD_3);
    led_pin_init(LED_PAD_4);
}
