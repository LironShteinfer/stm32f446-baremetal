/*
 * main.c - TIM2 interrupt blink demo.
 *
 * LD2 (PA5) toggles every BLINK_SLOW_MS milliseconds. The toggle runs in the
 * TIM2 update interrupt callback, so the main loop stays empty and the timing
 * comes from the timer hardware, not from a busy-wait delay.
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