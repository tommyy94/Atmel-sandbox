/*
 * This program blinks led and when external interrupt (switch in this case)
 * happens, the other led is lit.
 */

#ifndef F_CPU
#define F_CPU 2000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DELAY 500

#define SWITCH_PIN PIND2
#define LED_PIN_1 PIND0
#define LED_PIN_2 PIND1

void main(void)
{
    DDRD |= (1 << SWITCH_PIN);
    PORTD |= (1 << SWITCH_PIN); /* using internal pull-up resistor */
    DDRD |= (1 << LED_PIN_1) | (1 << LED_PIN_2);

    GIMSK |= (1 << INT0); /* enable external pin interrupt */
    MCUCR |= (1 << ISC00); /* logical change generates interrupt request */

    sei(); /* enable interrupts */

    while(1) {
        PORTD ^= (1 << LED_PIN_2); /* toggle pin */
        _delay_ms(DELAY);
    }
}

ISR(INT0_vect) { /* earlier enabled external pin interrupt */
    if(!(PIND & (1 << SWITCH_PIN))) {
        PORTD |= (1 << LED_PIN_1);
    } else if(PIND & (1 << SWITCH_PIN)) {
        PORTD &= ~(1 << LED_PIN_1);
    } else {
        /*
         * ERROR/EXCEPTION HANDLING
         */
    }
}
