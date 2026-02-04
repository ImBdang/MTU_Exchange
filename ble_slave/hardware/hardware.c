#include "hardware.h"

u32 telink_get_tick(void)
{
    return clock_time();
}


void hw_touchpad_cfg(uint32_t pin)
{
    GPIO_PinTypeDef p = (GPIO_PinTypeDef)pin;

    gpio_set_func(p, AS_GPIO);
    gpio_set_output_en(p, 0);
    gpio_set_input_en(p, 1);
    gpio_setup_up_down_resistor(p, PM_PIN_PULLUP_10K);
}

uint32_t hw_btn_read(uint32_t pin)
{
    GPIO_PinTypeDef p = (GPIO_PinTypeDef)pin;
    return gpio_read(p);  
}