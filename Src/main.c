/*
 * main.c - Light Station.
 *
 * LD2 follows the blue button B1. The red LED on PA6 shows the
 * external button on PA7, which uses the internal pull-up.
 */

#include "board.h"
#include "gpio.h"
#include "timer.h"

static void blink_isr(void)             /* runs inside TIM2_IRQHandler */
{
    gpio_toggle(LED_PORT, LED_PIN);
}

int main(void)
{
    gpio_clock_enable(LED_PORT);
    gpio_set_mode(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT);

    tim2_init(TIM2_CLK_HZ, BLINK_SLOW_MS, PRIO_BLINK);
    tim2_set_callback(blink_isr);
    tim2_start();

    for (;;) {
        
    }
}