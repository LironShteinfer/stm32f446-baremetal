



#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

typedef void (*timer_callback_t)(void);

void tim2_init(uint32_t timer_clk_hz, uint32_t period_ms, uint32_t priority);
void tim2_set_callback(timer_callback_t cb);    /* runs in ISR context */
void tim2_set_period_ms(uint32_t period_ms);
void tim2_start(void);
void tim2_stop(void);

#endif /* TIMER_H_ */