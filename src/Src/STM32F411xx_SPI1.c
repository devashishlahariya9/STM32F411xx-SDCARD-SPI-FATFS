/*
 * STM32F411xx_SPI1.c
 *
 * Created on: 04-Nov-2021
 * Author: Devashish Lahariya
*/

#include <STM32F411xx_SPI1.h>

void SPI1_init(uint8_t _ss, uint8_t _spi_opmode , uint8_t _spi_mode, uint8_t _spi_prescalar)
{
	RCC -> AHB1ENR |= (1 << GPIOBEN);
	RCC -> APB2ENR |= (1 << SPI1EN);

	SPI_SS = _ss;

	GPIOB -> AFRL |= (AF5 << 12) | (AF5 << 16) | (AF5 << 20); 					//Re-map Pins For AFIO

	GPIO_setMode(PORTB, SPI_SCK,  HIGH_SPEED, PUSH_PULL, AFIO);
	GPIO_setMode(PORTB, SPI_MISO, HIGH_SPEED, PUSH_PULL, AFIO);
	GPIO_setMode(PORTB, SPI_MOSI, HIGH_SPEED, PUSH_PULL, AFIO);

	GPIO_pin(PORTB, SPI_SS, HIGH);

	GPIO_setMode(PORTB, SPI_SS,   HIGH_SPEED, PUSH_PULL, GPIO);

	if(_spi_mode != SPI_MODE_0)
	{
		SPI1 -> CR1 |= (_spi_mode  << SPI_CPHA);								//Set SPI Mode
	}

	if(_spi_prescalar != SPI_CLK_DIV_BY_2)
	{
		SPI1 -> CR1 |= (_spi_prescalar << SPI_BR);								//Set SPI Speed
	}

	if(_spi_opmode == SPI_MASTER_MODE)
	{
		SPI1 -> CR1 |= (1 << SPI_MSTR);											//Enable MSTR Bit (For SPI MASTER MODE)
	}
	SPI1 -> CR1 |= (1 << SPI_SSM);												//Enable SSM Bit
	SPI1 -> CR1 |= (1 << SPI_SSI);												//Enable SSI Bit

	SPI1 -> CR1 |= (1 << SPI_SPE);  											//Enable SPI1
}

void SPI1_deinit(void)
{
	while((SPI1 -> SR & (1 << SPI_BSY)));

	SPI1 -> CR1 &= ~(3  << SPI_CPHA);
	SPI1 -> CR1 &= ~(7 << SPI_BR);
	SPI1 -> CR1 &= ~(1 << SPI_MSTR);
	SPI1 -> CR1 &= ~(1 << SPI_SSM);
	SPI1 -> CR1 &= ~(1 << SPI_SSI);
	SPI1 -> CR1 &= ~(1 << SPI_SPE);
}

void SPI1_beginTransmission(void)
{
	while((SPI1 -> SR & (1 << SPI_BSY)));
	while(!(SPI1 -> SR & (1 << SPI_TXE)));

	GPIOB -> ODR &= ~(1 << SPI_SS);
}

void SPI1_write(uint8_t _data)
{
	while((SPI1 -> SR & (1 << SPI_BSY)));
	while(!(SPI1 -> SR & (1 << SPI_TXE)));

	SPI1 -> DR = _data;
}

void SPI1_endTransmission(void)
{
	while((SPI1 -> SR & (1 << SPI_BSY)));
	while(!(SPI1 -> SR & (1 << SPI_TXE)));

	GPIOB -> ODR |= (1 << SPI_SS);
}

uint8_t SPI1_read(void)
{
	while((SPI1 -> SR & (1 << SPI_BSY)));
	while(!(SPI1 -> SR & (1 << SPI_RXNE)));

	return SPI1 -> DR;
}
