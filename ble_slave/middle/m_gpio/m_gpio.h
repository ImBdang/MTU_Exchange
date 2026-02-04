#ifndef __M_GPIO_H__
#define __M_GPIO_H__

#include "gpio.h"

/* ====================================== LED ======================================= */

void m_set_led_on(const GPIO_PinTypeDef* led_pins, u8 num);
void m_set_led_off(const GPIO_PinTypeDef* led_pins, u8 num);
void m_set_led_toggle(GPIO_PinTypeDef led_pin);

void led_init_all(void);

/* ====================================== TOUCHPAD ======================================= */
typedef struct {
    GPIO_PinTypeDef led_pin;
    GPIO_PinTypeDef touchpad_pin;
    u8 touchpad_state;  
} touchpad_t;

void touchpad_led_set_by_id(u8 id, u8 on);

void touchpad_proc(void);
void touchpad_init(void);

#endif /*<! __M_GPIO_H__ */