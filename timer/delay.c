/**
 * This program toggles 2 leds with 1 second delay.
 * The other is toggled with delay function and other with timer.
 * Timer produced delay is slightly shorter.
 */

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_PIN_1 PIND0
#define LED_PIN_2 PIND1
#define SECOND 1000


void timer1_init(void);


void main(void)
{
    DDRD |= (1 << LED_PIN_2) | (1 << LED_PIN_1);

    timer1_init();

    while(1) {
        _delay_ms(SECOND);
        PORTD ^= (1 << LED_PIN_2);
    }
}


ISR(TIMER1_COMPA_vect)
{
    PORTD ^= (1 << LED_PIN_1);
}


void timer1_init(void)
{
    /* set 16-bit timer registers */
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    
    /**
     * 8 MHz/1024 = 7812.5 steps => interrupt/second
     * 7812 = 0x1E84 => 0x1E83, because 0x00 is one count
     */
    OCR1AH = 0x1E;
    OCR1AL = 0x83;

    TIMSK |= (1 << OCIE1A);

    sei(); /* enable interrupts */
}
