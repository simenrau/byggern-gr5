#include "define2.h"
#include "SPI2.h"

#define SS_init PB0
#define SCK PB1
#define MOSI PB2
#define MISO PB3
#define SS	PB7

void SPI_MasterInit(void)
{
	DDRB |= (1 << MOSI) | (1 << SS) | (1 << SCK) | (1 << SS_init);
	DDRB &= ~(1 << MISO);
	PORTB |= (1<<SS_init);
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(char cdata)
{
	SPDR = cdata;
	
	while(!(SPSR & (1 << SPIF)));
}

void SPI_SlaveInit(void)
{
	DDRB = (1 << MISO);
	
	SPCR = (1<<SPE);
}

uint8_t SPI_SlaveReceive(void)
{
	SPI_MasterTransmit(0x0);
	return SPDR;
}