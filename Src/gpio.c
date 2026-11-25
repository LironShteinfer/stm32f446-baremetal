#include "gpio.h"

#define MODER_BITS_PER_PIN 2U
#define FIELD_MASK_2BITS 3UL
#define AFR_PINS_PER_REG 8U
#define AFR_BITS_PER_PIN 4U
#define FIELD_MASK_4BIT 0xFUL

void gpio_clock_enable(GPIO_TypeDef *port)
{
    RCC->AHB1ENR |= (1UL << gpio_port_index(port));
    (void)RCC->AHB1ENR; /* read back to ensure the clock is enabled before proceeding */
}

void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode)
{
    uint32_t shift = pin * MODER_BITS_PER_PIN;
    port->MODER &= ~(FIELD_MASK_2BITS << shift);
    port->MODER |= ((uint32_t)mode << shift);
}

void gpio_set_pull(GPIO_TypeDef *port, uint8_t pin, gpio_pull_t pull)
{
    uint32_t shift = pin * MODER_BITS_PER_PIN;
    port->PUPDR &= ~(FIELD_MASK_2BITS << shift);
    port->PUPDR |= ((uint32_t)pull << shift);
}

void gpio_set_open_drain(GPIO_TypeDef *port, uint8_t pin, bool open_drain)
{
    if (open_drain) {
        port->OTYPER |= (1UL << pin);
    } else {
        port->OTYPER &= ~(1UL << pin);
    }
}

void gpio_set_af(GPIO_TypeDef *port, uint8_t pin, uint32_t af)
{
    uint32_t index = pin / AFR_PINS_PER_REG;
    uint32_t shift = (pin % AFR_PINS_PER_REG) * AFR_BITS_PER_PIN;
    port->AFR[index] &= ~(FIELD_MASK_4BIT << shift);
    port->AFR[index] |= ((uint32_t)af << shift);
}
