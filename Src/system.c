/*
 * system.c - early system setup, called from the startup code before main().
 *
 * The project is built with -mfloat-abi=hard, so the compiler may use FPU
 * instructions. The Cortex-M4 FPU is disabled after reset, and any FPU
 * instruction would raise a UsageFault (escalated to HardFault). SystemInit()
 * grants full access to coprocessors CP10/CP11 (the FPU) in SCB->CPACR before
 * the C library init and main() run.
 */

#include "board.h"

void SystemInit(void)
{
    SCB->CPACR |= CPACR_FPU_FULL_ACCESS;
    __DSB();                            /* complete the CPACR write */
    __ISB();                            /* flush the pipeline so FPU access takes effect */
}
