# Bare-Metal Blinky (STM32F407 / ARM Cortex-M4)

A from-scratch "blinky" project that talks directly to hardware registers—no HAL,
no CMSIS, no IDE. Every layer (startup code, linker script, register access) is
visible and explained. Built to learn how embedded systems actually boot and run.

## What This Teaches

- **The boot sequence** — how the CPU finds the stack pointer and reset handler
- **Linker scripts** — mapping code/data into Flash and RAM
- **Startup code** — copying `.data`, zeroing `.bss`, calling `main()`
- **Memory-mapped I/O** — reading/writing hardware via `volatile` pointers
- **Peripheral clocks** — why nothing works until you enable the RCC clock

## Hardware

- **MCU:** STM32F407 (or any STM32F4 with an LED on PD12)
- **Board:** STM32F4-Discovery, Nucleo-F407, or a custom board
- **Programmer:** ST-LINK (V2 or V3), or any SWD debugger

> Adjusting for a different board? Change the register addresses in `main.c`
> and the `ORIGIN`/`LENGTH` values in `linker.ld`.

## Prerequisites (Termux)

```bash
pkg update && pkg upgrade -y
pkg install clang llvm make git -y
