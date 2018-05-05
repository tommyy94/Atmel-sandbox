/**
 * This program uses software UART to communicate.
 * Currently it is only capable of tranmitting data, max 6000 baud.
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define TX_LED PB0
#define RX_LED PB1
#define SWITCH_PIN PB2

#define TEST_DATA 'A'

#define BAUD 4800
#define STOP_BITS 1

#define TX_BIT 0
#define TX_DDR DDRC
#define TX_PORT PORTC

#define US_OVERHEAD_ADJUST 1
#define US_PER_BIT (((F_CPU/16) / BAUD) - US_OVERHEAD_ADJUST)

inline void soft_uart_init(void);
void soft_uart_transmit(uint8_t data);

void main(void)
{
    DDRB = (1 << TX_LED) | (1 << RX_LED) | ~(1 << SWITCH_PIN);
    PORTB = (1 << SWITCH_PIN);

    soft_uart_init();

    while(1) {
        if(~PINB & (1 << SWITCH_PIN)) {
            PORTB ^= (1 << TX_LED);
            soft_uart_transmit(TEST_DATA);
        } else {
            PORTB &= ~(1 << TX_LED);
        }
    }
}

inline void soft_uart_init(void)
{
    TX_PORT |= (1 << TX_BIT);
    TX_DDR |= (1 << TX_BIT);
}

void soft_uart_transmit(uint8_t data)
{
    /* send start bit */
    TX_PORT &= ~(1 << TX_BIT);
    _delay_us(US_PER_BIT);

    /* data bits */
    for(uint8_t bit_mask = 0x01; bit_mask; bit_mask <<= 1) {
        if(data & bit_mask) {
            TX_PORT |= (1 << TX_BIT);
        } else {
            TX_PORT &= ~(1 << TX_BIT);
        }
        _delay_us(US_PER_BIT);
    }
    PORTB ^= (1 << RX_LED);

    /* send stop bits */
    TX_PORT |= (1 << TX_BIT);
    _delay_us(US_PER_BIT * STOP_BITS);
}
