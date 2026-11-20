#ifndef BOARD_H_
#define BOARD_H_

#include "stm32f446xx.h"

#define SYSCLK_HZ 16000000UL
#define TIM2_CLK_HZ SYSCLK_HZ

#define LED_PORT GPIOA
#define LED_PIN 5U

#define LED2_PORT   GPIOA
#define LED2_PIN    6U

#define BTN_PORT GPIOC
#define BTN_PIN 13U

#define BTN2_PORT   GPIOA
#define BTN2_PIN    7U           /* PA7 = D11, external button to GND */

#define CPACR_FPU_FULL_ACCESS ((3UL << 20U) | (3UL << 22U))

#define BLINK_SLOW_MS 500U
#define BLINK_FAST_MS 100U

#define PRIO_TICK 5U
#define PRIO_BUTTON 5U
#define PRIO_BLINK 6U

#endif // BOARD_H_  