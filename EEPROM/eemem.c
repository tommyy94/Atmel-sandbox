/** 
 * This program initializes EEPROM with users values at build stage.
 * Then it reads the data.
 */
#include <avr/eeprom.h>

#define SIZE 10

/** 
 * Following initializes .eep file (.eseg) with values
 * and it needs to be uploaded to MCU separately.
 * Attribute section can't be specified for local variables.
 */
uint32_t EEMEM integer = 69;
uint8_t EEMEM character = 'Q';
uint8_t EEMEM string[SIZE] = "WASD";

void main(void)
{
    /* Build -> upload EEPROM -> flash MCU -> read EEPROM from debug viewer */

    /* volatile to avoid optimization */
    volatile uint32_t e_int;
    volatile uint8_t e_char;
    volatile uint8_t e_string[SIZE];

    e_int = eeprom_read_dword(&integer); /* read 32-bit value */
    e_char = eeprom_read_byte(&character);
    eeprom_read_block((void *) e_string, (const void *) string, SIZE);

    asm volatile("nop"); /* breakpoint */
}
