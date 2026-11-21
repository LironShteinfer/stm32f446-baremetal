


#include "systick.h"
#include "stm32f446xx.h"
#include "units.h"

#define SYSTICK_HZ      1000U  

static volatile uint32_t s_ticks;         
static systick_callback_t s_callback;

void systick_init(uint32_t sysclk_hz, uint32_t priority)
{
    SysTick->CTRL = 0U;                            
    SysTick->LOAD = (sysclk_hz / SYSTICK_HZ) - 1U;  
    SysTick->VAL  = 0U;                             
    NVIC_SetPriority(SysTick_IRQn, priority);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk      
                  | SysTick_CTRL_TICKINT_Msk        
                  | SysTick_CTRL_ENABLE_Msk;       
}

void systick_set_callback(systick_callback_t cb)
{
    s_callback = cb;
}


void SysTick_Handler(void)
{
    s_ticks++;

    if (s_callback != 0) {
        s_callback();
    }
}

uint32_t millis(void)
{
    return s_ticks;         
}

void delay_ms(uint32_t ms)
{
    uint32_t start = millis();

  
    while ((millis() - start) < ms) {
    }
}
