# STM32F446RE Bare-Metal Drivers

Register-level drivers for the **NUCLEO-F446RE** (STM32F446RE, ARM Cortex-M4), written in C without the ST HAL. Every peripheral is configured directly through its registers, using only the CMSIS device headers for register definitions, following the STM32F446 reference manual.

> **Status:** work in progress. I keep adding drivers to this repository as I learn new peripherals (see [Roadmap](#roadmap)).

## What's inside

| Module | Files | What it does |
|---|---|---|
| **GPIO** | `Inc/gpio.h`, `Src/gpio.c` | Enables the port clock (RCC AHB1ENR), sets pin mode (input / output / alternate function / analog), pull-up / pull-down, push-pull or open-drain, and the alternate-function number (AFRL/AFRH). Read, write and toggle are `static inline`; writes go through **BSRR** so they are atomic. |
| **SysTick** | `Inc/systick.h`, `Src/systick.c` | 1 kHz system tick from the core SysTick timer, with configurable NVIC priority. Provides `millis()` and a blocking `delay_ms()` that is safe across counter wrap-around, plus an optional callback that runs on every tick. |
| **TIM2** | `Inc/timer.h`, `Src/timer.c` | Periodic **update interrupt** from the general-purpose timer TIM2. The prescaler makes the counter step once per millisecond, and ARR sets the period. The application registers a callback that runs inside `TIM2_IRQHandler`. The period can be changed at run time, and the timer can be started and stopped. |
| **System init** | `Src/system.c` | `SystemInit()`, called from the startup code before `main()`. Enables the Cortex-M4 FPU (full access to CP10/CP11 in `SCB->CPACR`), followed by `DSB`/`ISB`, because the project is built with `-mfloat-abi=hard`. |
| **Board config** | `Inc/board.h`, `Inc/units.h` | Clock frequency, pin assignments, blink periods and interrupt priorities in one place, so drivers contain no magic numbers. |

### Implementation notes

- **Enabling an interrupt takes three steps**, and the code follows them in order: the peripheral's own interrupt enable (`TIM2->DIER.UIE`), the NVIC enable (`NVIC_EnableIRQ`), and finally starting the counter (`CR1.CEN`).
- **`URS` is set in TIM2**, so only a real counter overflow raises the update flag. Writing `UG` (to load a new prescaler or period immediately) does not fire a spurious interrupt.
- **The update flag is cleared by writing 0** (`TIM2->SR = ~TIM_SR_UIF`), because the status bits are `rc_w0`. A read-modify-write could clear other flags by mistake.
- **The RCC enable register is read back** after enabling a clock, so the peripheral is ready before it is accessed.
- **The FPU is enabled before `main()`.** It is off after reset, and any floating-point instruction would raise a UsageFault, so `SystemInit()` enables it before the C library initialization runs.
- **Clock:** the MCU runs from the internal 16 MHz HSI oscillator (no PLL), so all timing is derived from `SYSCLK_HZ = 16 MHz` in `board.h`.

## Current demo (`Src/main.c`)

The on-board LED **LD2 (PA5)** blinks every 500 ms. The toggle runs from the TIM2 update interrupt callback, and the main loop is empty: the timing comes entirely from the timer hardware, not from a busy-wait delay.

## Hardware

- NUCLEO-F446RE board, connected over USB (on-board ST-LINK for flashing and debugging).
- LD2 (PA5) and the blue user button B1 (PC13) are on the board.
- `board.h` also defines an external LED on **PA6** and an external button on **PA7** (to GND, with the internal pull-up) for the next steps of the project.

## Build

Requirements: **CMake ≥ 3.20**, **Ninja**, and the **GNU Arm Embedded toolchain** (`arm-none-eabi-gcc`), for example the one bundled with STM32CubeIDE or the STM32Cube extension for VS Code.

```bash
cmake --preset Debug          # configure (build/Debug)
cmake --build --preset Debug  # build -> build/Debug/stm32f446-baremetal.elf
```

Use the `Release` preset for an optimized (`-Os`) build. The project compiles with `-Wall -Wextra -Wpedantic`.

## Flash and debug

- **VS Code:** with the STM32Cube extension, use the included launch configuration **"STM32Cube: Launch ST-Link GDB Server"** (`.vscode/launch.json`). It builds, flashes and stops at `main`.
- **STM32CubeProgrammer:** flash `build/Debug/stm32f446-baremetal.elf` over ST-LINK.

## Project structure

```
Inc/                     driver headers and board configuration
Src/                     driver sources, main.c, system init, startup code, newlib syscalls
Drivers/CMSIS/           ARM CMSIS core and ST STM32F4 device headers (register definitions only)
cmake/                   toolchain file and compiler / linker flags
stm32f446xe_flash.ld     linker script (512 KB flash, 128 KB RAM)
CMakeLists.txt, CMakePresets.json
```

## Roadmap

- [ ] EXTI interrupts for the user button (PC13) and the external button (PA7)
- [ ] USART2 driver with interrupt-driven receive (ST-LINK virtual COM port)
- [ ] Port the I2C / HD44780 LCD driver from [LCD1602-I2C-STM32F446RE](https://github.com/LironShteinfer/LCD1602-I2C-STM32F446RE) into this driver set

## Related repositories

- [stm32f446-learning](https://github.com/LironShteinfer/stm32f446-learning): my earlier STM32CubeIDE projects (USART2 driver, EXTI, serial shell)
- [LCD1602-I2C-STM32F446RE](https://github.com/LironShteinfer/LCD1602-I2C-STM32F446RE): bare-metal I2C driver for an HD44780 LCD through a PCF8574 expander
