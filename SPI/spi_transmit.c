/**
 * This program uses software SPI to communicate.
 * Device ATmega328P
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>


#define DDR_SPI DDRB
#define DD_MOSI PINB3
#define DD_SCK PINB5


void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void SPI_MasterTransmitString(char string[]);


void main(void)
{
    char string[] = "Epic test!\r\n";

    SPI_MasterInit();

    while(1) {
        SPI_MasterTransmitString(string);
        _delay_ms(10);
    }
}


void SPI_MasterInit(void)
{
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}


void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF))) {
        ;
    }
}


void SPI_MasterTransmitString(char string[])
{
    for(uint8_t i = 0; i < strlen(string); i++) {
        SPI_MasterTransmit(string[i]);
    }
}
