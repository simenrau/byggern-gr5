#include "define.h"
#include "SPI.h"

#define SS PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7


void SPI_MasterInit(void)
{
	DDRB |= (1 << MOSI) | (1 << SS) | (1 << SCK);
	DDRB &= ~(1 << MISO);
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
	SPI_MasterTransmit(0);
	return SPDR;
}