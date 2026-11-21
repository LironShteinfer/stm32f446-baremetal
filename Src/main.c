/*
 * main.c - Light Station.
 *
 * LD2 follows the blue button B1. The red LED on PA6 shows the
 * external button on PA7, which uses the internal pull-up.
 */

#include "board.h"
#include "gpio.h"
#include "systick.h"

int main(void)
{
    gpio_clock_enable(LED_PORT);
    gpio_set_mode(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT);

    systick_init(SYSCLK_HZ, PRIO_TICK);

    for (;;) {
        gpio_toggle(LED_PORT, LED_PIN);
        delay_ms(BLINK_SLOW_MS);        /* exact at any optimization level */
    }
}