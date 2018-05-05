/**
 * Example how to communicate between two microcontrollers (ATmega16 used).
 * Pressing switch transmits data to other MCU.
 * Blinking leds indicate TX/RX.
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TX_LED PB0
#define RX_LED PB1
#define SWITCH_PIN PB2

#define XTAL F_CPU/**
 * Example how to communicate between two microcontrollers (ATmega16 used).
 * Pressing switch transmits data to other MCU.
 * Blinking leds indicate TX/RX.
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TX_LED PB0
#define RX_LED PB1
#define SWITCH_PIN PB2

#define XTAL F_CPU
#define BAUD 9600
#define OVERHEAD_ADJUST 1

#define TEST_DATA 'A'

#define HIGH(value) ((value) >> 8) /* get high 8 bits */
#define LOW(value) ((value) & 0xFF) /* get low 8 bits */

inline void uart_init(void);
void uart_transmit(unsigned char data);


void main(void)
{
    DDRB = (1 << TX_LED) | (1 << RX_LED) | ~(1 << SWITCH_PIN);
    PORTB = (1 << SWITCH_PIN);

    uart_init();
    sei();

    while(1) {
        if(~PINB & (1 << SWITCH_PIN)) {
            PORTB ^= (1 << TX_LED);
            uart_transmit(TEST_DATA);
        } else {
            PORTB &= ~(1 << TX_LED);
        }
        _delay_ms(50);
    }
}


inline void uart_init(void)
{
    /* set baud rate */
    UBRRH = HIGH(((XTAL/16)/BAUD) - OVERHEAD_ADJUST);
    UBRRL = LOW(((XTAL/16)/BAUD) - OVERHEAD_ADJUST);

    /* enable receiver interrupt, receiver, transmission */
    UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);

    /* 8n1 by default */
}


void uart_transmit(unsigned char data)
{
    while(!(UCSRA & (1 << UDRE))) {
        ; /* wait for empty transmit buffer */
    }

    UDR = data; /* put data into buffer and send it */
}


ISR(USART_RXC_vect)
{
    if(UDR == TEST_DATA) {
        PORTB ^= (1 << RX_LED); /* signal receiving data */
    } else {
        PORTB &= ~(1 << RX_LED);
    }
}
