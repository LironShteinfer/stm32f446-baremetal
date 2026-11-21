


#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

typedef void (*systick_callback_t)(void);

void     systick_init(uint32_t sysclk_hz, uint32_t priority);
void     systick_set_callback(systick_callback_t cb);   
uint32_t millis(void);
void     delay_ms(uint32_t ms);

#endif /* SYSTICK_H_ */