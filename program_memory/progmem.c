/**
 * This program reads data held in flash memory to SRAM.
 */
#include <avr/pgmspace.h>

const char string_in_flash [] PROGMEM = "I'm held in flash memory.";

void print(const char *data);

void main(void)
{
    print(string_in_flash);

    asm volatile("nop"); /* breakpoint */
}

void print(const char *data)
{
    static volatile char string[30];

    for(uint8_t i = 0; pgm_read_byte(data) != 0x00; i++) {
        string[i] = pgm_read_byte(data++);
    }
}
