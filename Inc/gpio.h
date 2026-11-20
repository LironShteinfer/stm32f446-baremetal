#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f446xx.h"
#include <stdint.h>
#include <stdbool.h>

#define GPIO_PORT_STRIDE 0x400U
#define GPIO_BSRR_RESET_SHIFT 16U

typedef enum {
    GPIO_MODE_INPUT = 0U,
    GPIO_MODE_OUTPUT = 1U,
    GPIO_MODE_AF = 2U,
    GPIO_MODE_ANALOG = 3U
} gpio_mode_t;

typedef enum {
    GPIO_PULL_NONE = 0U,
    GPIO_PULL_UP = 1U,
    GPIO_PULL_DOWN = 2U
} gpio_pull_t;

void gpio_clock_enable(GPIO_TypeDef *port);
void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode);
void gpio_set_pull(GPIO_TypeDef *port, uint8_t pin, gpio_pull_t pull);
void gpio_set_open_drain(GPIO_TypeDef *port, uint8_t pin, bool open_drain);
void gpio_set_af(GPIO_TypeDef *port, uint8_t pin, uint32_t af);

static inline void gpio_write(GPIO_TypeDef *port, uint8_t pin, bool value)
{
    if (value) {
        port->BSRR = (1U << pin);
    } else {
        port->BSRR = (1U << (pin + GPIO_BSRR_RESET_SHIFT));
    }
}

static inline uint32_t gpio_port_index(GPIO_TypeDef *port)
{
    return ((uint32_t)port - (uint32_t)GPIOA) / GPIO_PORT_STRIDE;
}

static inline bool gpio_read(GPIO_TypeDef *port, uint8_t pin)
{
    return (port->IDR & (1U << pin)) != 0U;
}

static inline void gpio_toggle(GPIO_TypeDef *port, uint8_t pin)
{
    gpio_write(port, pin, (port->ODR & (1UL << pin)) == 0U);
}

#endif // GPIO_H_