/*
 * main.c - Light Station.
 *
 * LD2 follows the blue button B1. The red LED on PA6 shows the
 * external button on PA7, which uses the internal pull-up.
 */

#include "board.h"
#include "gpio.h"

int main(void)
{
    gpio_clock_enable(LED_PORT);
    gpio_clock_enable(BTN_PORT);

    gpio_set_mode(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_mode(BTN_PORT, BTN_PIN, GPIO_MODE_INPUT);

    /* Exercise 2: external red LED */
    gpio_set_mode(LED2_PORT, LED2_PIN, GPIO_MODE_OUTPUT);

    /* Exercise 3: external button to GND, internal pull-up */
    gpio_set_mode(BTN2_PORT, BTN2_PIN, GPIO_MODE_INPUT);
    gpio_set_pull(BTN2_PORT, BTN2_PIN, GPIO_PULL_UP);

    for (;;) {
        bool pressed  = !gpio_read(BTN_PORT, BTN_PIN);     /* active low */
        bool ext_level = gpio_read(BTN2_PORT, BTN2_PIN);   /* 1 = released */

        gpio_write(LED_PORT, LED_PIN, pressed);
        gpio_write(LED2_PORT, LED2_PIN, !ext_level);       /* on while pressed */
    }
}
