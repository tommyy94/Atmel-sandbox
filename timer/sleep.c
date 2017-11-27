/**
 * This program toggles led and sleeps otherwise.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED_PIN_1 PIND0
#define LED_PIN_2 PIND1


void timer1_init(void);


void main(void)
{
    DDRD |= (1 << LED_PIN_2) | (1 << LED_PIN_1);

    timer1_init();
    
    set_sleep_mode(SLEEP_MODE_IDLE);

    while(1) {
        sleep_mode();
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
