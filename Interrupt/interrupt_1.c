/*
 * This program blinks led and when external interrupt (switch) happens,
 * the other led is lit.
 */

#ifndef F_CPU
#define F_CPU 2000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DELAY 500

#define SWITCH_PIN PINB0
#define LED_PIN_1 PIND0
#define LED_PIN_2 PIND1

void main(void)
{
    DDRB |= (1 << SWITCH_PIN);
    PORTB |= (1 << SWITCH_PIN); /* using internal pull-up resistor */
    DDRD |= (1 << LED_PIN_1) | (1 << LED_PIN_2);

    GIMSK |= (1 << PCIE0); /* changes in PCINT7...PCINT0 result in interrupt */
    PCMSK0 |= (1 << PCINT0); /* pin change interrupt enabled on I/O pin */

    sei(); /* enable interrupts */

    while(1) {
        PORTD ^= (1 << LED_PIN_2); /* toggle pin */
        _delay_ms(DELAY);
    }
}

ISR(PCINT0_vect) {
    if(!(PINB & (1 << SWITCH_PIN))) {
        PORTD |= (1 << LED_PIN_1);
    } else if(PINB & (1 << SWITCH_PIN)) {
        PORTD &= ~(1 << LED_PIN_1);
    } else {
        /*
         * ERROR HANDLING
         */
    }
}
