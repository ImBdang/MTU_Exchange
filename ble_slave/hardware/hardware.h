#ifndef __HW_HARDWARE_H__
#define __HW_HARDWARE_H__

#include "gpio.h"
#include "types.h"
#include "timer.h"
#include <stdint.h>

#define MAX_TOUCHPAD        4

#define TOUCHPAD_IDLE       0
#define TOUCHPAD_ACTIVE     1

#define TOUCHPAD_1          GPIO_PB4
#define TOUCHPAD_2          GPIO_PB5
#define TOUCHPAD_3          GPIO_PB6
#define TOUCHPAD_4          GPIO_PC0


#define LED_STT             GPIO_PD4

#define LED_ACTIVE          1
#define LED_IDLE            0

#define LED_PAD_1           GPIO_PC1
#define LED_PAD_2           GPIO_PC4
#define LED_PAD_3           GPIO_PD2
#define LED_PAD_4           GPIO_PD3


void hw_touchpad_cfg(uint32_t pin);

uint32_t hw_btn_read(uint32_t pin);

u32 telink_get_tick(void);


#endif /*<! __HW_HARDWARE_H__ */