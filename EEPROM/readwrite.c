/**
 * This program writes variable values to EEPROM memory then reads them
 * to prove it works as intended.
 */
#include <avr/eeprom.h>

#define SIZE 4
#define EEPROM_INIT_ADDR 0x00

void write_eeprom(void);
void read_eeprom(void);

void main(void)
{
    write_eeprom();
    read_eeprom();
}


void write_eeprom(void)
{
    uint8_t eeprom_addr = EEPROM_INIT_ADDR;
    uint8_t *ptr_eeprom_addr = &eeprom_addr;

    float floating_point = 6.9;
    uint16_t integer = 666;
    uint8_t character = 'q';
    uint8_t string[SIZE] = "wasd";

    /* write data to defined eeprom addresses, increment pointer afterwards */
    eeprom_update_float((float *)ptr_eeprom_addr, floating_point);
    ptr_eeprom_addr += sizeof(float);
    eeprom_update_word((uint16_t *)ptr_eeprom_addr, integer);
    ptr_eeprom_addr += sizeof(uint16_t);
    eeprom_update_block((const void *)string, (void *)ptr_eeprom_addr, SIZE);
    ptr_eeprom_addr += sizeof(uint8_t) * SIZE;
    eeprom_update_byte((uint8_t *)ptr_eeprom_addr, character);
    ptr_eeprom_addr += sizeof(uint8_t);
}


void read_eeprom(void)
{
    uint8_t eeprom_addr = EEPROM_INIT_ADDR;
    uint8_t *ptr_eeprom_addr = &eeprom_addr;

    /* volatile to avoid compiler optimization */
    volatile float floating_point;
    volatile uint16_t integer;
    volatile uint8_t character;
    volatile uint8_t string[SIZE];

    /* read data from defined eeprom addresses, increment pointer afterwards */
    floating_point = eeprom_read_float((float *)ptr_eeprom_addr);
    ptr_eeprom_addr += sizeof(float);
    integer = eeprom_read_word((uint16_t *)ptr_eeprom_addr);
    ptr_eeprom_addr += sizeof(uint16_t);
    eeprom_read_block((void *)string, (const void *)ptr_eeprom_addr, SIZE);
    ptr_eeprom_addr += sizeof(uint8_t) * SIZE;
    character = eeprom_read_byte((uint8_t *)ptr_eeprom_addr);
    ptr_eeprom_addr += sizeof(uint8_t);

    asm volatile("nop"); /* breakpoint */
}
