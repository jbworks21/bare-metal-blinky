// main.c - Bare-metal blinky for STM32F407 (LED on PD12)
#include <stdint.h>

// --- Register Address Definitions (from the datasheet) ---
// RCC: Reset and Clock Control
#define RCC_AHB1ENR   (*(volatile uint32_t *)0x40023830)
// GPIO Port D
#define GPIOD_MODER   (*(volatile uint32_t *)0x40020C00)
#define GPIOD_ODR     (*(volatile uint32_t *)0x40020C14)

// Bit definitions
#define RCC_AHB1ENR_GPIODEN  (1U << 3) // Enable clock for GPIOD
#define LED_PIN              12        // LED is on pin PD12

// A simple, crude delay function
void delay(volatile uint32_t count) {
    while (count--) {
        __asm__("nop"); // No-operation: just waste time
    }
}

int main(void) {
    // Step 1: Enable the clock for GPIOD
    // Without this, writing to GPIOD registers will do nothing.
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // Step 2: Configure PD12 as a general-purpose output
    // First, clear the two mode bits for pin 12
    GPIOD_MODER &= ~(3U << (LED_PIN * 2));
    // Then, set the mode to 01 (General purpose output mode)
    GPIOD_MODER |= (1U << (LED_PIN * 2));

    // Step 3: Toggle the LED in an infinite loop
    while (1) {
        // Turn LED ON (set bit 12 in ODR)
        GPIOD_ODR |= (1U << LED_PIN);
        delay(500000);

        // Turn LED OFF (clear bit 12 in ODR)
        GPIOD_ODR &= ~(1U << LED_PIN);
        delay(500000);
    }

    return 0; // Never reached
}
