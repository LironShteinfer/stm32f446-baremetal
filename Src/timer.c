




#include "timer.h"
#include "stm32f446xx.h"

#define TIMER_COUNT_HZ  1000U   /* the counter steps once every millisecond */

static timer_callback_t s_callback;

void tim2_init(uint32_t timer_clk_hz, uint32_t period_ms, uint32_t priority)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    (void)RCC->APB1ENR;

    TIM2->CR1  = TIM_CR1_URS;                   /* only an overflow sets UIF  */
    TIM2->PSC  = (timer_clk_hz / TIMER_COUNT_HZ) - 1U;  /* 16 MHz / 16000 */
    TIM2->ARR  = period_ms - 1U;
    TIM2->EGR  = TIM_EGR_UG;                    /* load PSC and ARR right now */
    TIM2->DIER = TIM_DIER_UIE;                  /* switch 2: peripheral enable */

    NVIC_SetPriority(TIM2_IRQn, priority);
    NVIC_EnableIRQ(TIM2_IRQn);                  /* switch 3: NVIC enable      */
}

void tim2_set_callback(timer_callback_t cb)
{
    s_callback = cb;
}

void tim2_set_period_ms(uint32_t period_ms)
{
    TIM2->ARR = period_ms - 1U;
    TIM2->EGR = TIM_EGR_UG;     /* restart from 0: CNT may be past the new ARR */
}

void tim2_start(void)
{
    TIM2->CR1 |= TIM_CR1_CEN;
}

void tim2_stop(void)
{
    TIM2->CR1 &= ~TIM_CR1_CEN;
}

void TIM2_IRQHandler(void)
{
    if ((TIM2->SR & TIM_SR_UIF) != 0U) {
        TIM2->SR = ~TIM_SR_UIF;     /* rc_w0: write 0 to clear */

        if (s_callback != 0) {
            s_callback();
        }
    }
}