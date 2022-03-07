/*
 * STM32F411xx_SPI1.c
 *
 * Created on: 04-Nov-2021
 * Author: Devashish Lahariya
*/

#include "STM32F411xx_SPI.h"

void SPI1_USE_GPIOA(void)
{
	GPIOA_CLK_ENABLE();

	GPIOA -> AFRL &= ~(0xF << 20);
	GPIOA -> AFRL &= ~(0xF << 24);
	GPIOA -> AFRL &= ~(0xF << 28);

	GPIOA -> AFRL |= (AF5 << 20) | (AF5 << 24) | (AF5 << 28);

	GPIO_SetMode(GPIOA, SPI1_GPIOA_SCK,  GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOA, SPI1_GPIOA_MISO, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOA, SPI1_GPIOA_MOSI, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);

	SPI1_CLK_ENABLE();
}

void SPI1_USE_GPIOB(void)
{
	GPIOB_CLK_ENABLE();

	GPIOB -> AFRL &= ~(0xF << 12);
	GPIOB -> AFRL &= ~(0xF << 16);
	GPIOB -> AFRL &= ~(0xF << 20);

	GPIOB -> AFRL |= (AF5 << 12) | (AF5 << 16) | (AF5 << 20);

	GPIO_SetMode(GPIOB, SPI1_GPIOB_SCK,  GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOB, SPI1_GPIOB_MISO, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOB, SPI1_GPIOB_MOSI, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);

	SPI1_CLK_ENABLE();
}

void SPI2_USE_GPIOB(void)
{
	GPIOB_CLK_ENABLE();

	GPIOB -> AFRH &= ~(0xF << 20);
	GPIOB -> AFRH &= ~(0xF << 24);
	GPIOB -> AFRH &= ~(0xF << 28);

	GPIOB -> AFRH |= (AF5 << 20) | (AF5 << 24) | (AF5 << 28);

	GPIO_SetMode(GPIOB, SPI2_GPIOB_SCK,  GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOB, SPI2_GPIOB_MISO, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOB, SPI2_GPIOB_MOSI, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);

	SPI2_CLK_ENABLE();
}

void SPI2_USE_GPIOC(void)
{
	GPIOB_CLK_ENABLE();
	GPIOC_CLK_ENABLE();

	GPIOB -> AFRH &= ~(0xF << 8);
	GPIOC -> AFRL &= ~(0xF << 8);
	GPIOC -> AFRL &= ~(0xF << 12);

	GPIOB -> AFRH |= (AF5 << 8);
	GPIOC -> AFRL |= (AF5 << 8) | (AF5 << 12);

	GPIO_SetMode(GPIOB, SPI2_GPIOC_SCK,  GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOC, SPI2_GPIOC_MISO, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOC, SPI2_GPIOC_MOSI, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);

	SPI2_CLK_ENABLE();
}

void SPI3_USE_GPIOB(void)
{
	GPIOB_CLK_ENABLE();

	GPIOB -> AFRL &= ~(0xF << 12);
	GPIOB -> AFRL &= ~(0xF << 16);
	GPIOB -> AFRL &= ~(0xF << 20);

	GPIOB -> AFRL |= (AF6 << 12) | (AF6 << 16) | (AF6 << 20);

	GPIO_SetMode(GPIOB, SPI3_GPIOB_SCK,  GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOB, SPI3_GPIOB_MISO, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOB, SPI3_GPIOB_MOSI, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);

	SPI3_CLK_ENABLE();
}

void SPI3_USE_GPIOC(void)
{
	GPIOC_CLK_ENABLE();

	GPIOC -> AFRH &= ~(0xF << 8);
	GPIOC -> AFRH &= ~(0xF << 12);
	GPIOC -> AFRH &= ~(0xF << 16);

	GPIOC -> AFRH |= (AF6 << 8) | (AF6 << 12) | (AF6 << 16);

	GPIO_SetMode(GPIOC, SPI3_GPIOC_SCK,  GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOC, SPI3_GPIOC_MISO, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_SetMode(GPIOC, SPI3_GPIOC_MOSI, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);

	SPI3_CLK_ENABLE();
}

void SPI_Init(SPI_PERIPHERALS_t* SPI, void(*remap_func)(void), GPIO_PERIPHERALS_t* _port, uint8_t _ss, uint8_t _spi_opmode , uint8_t _spi_mode, uint8_t _spi_prescalar)
{
	remap_func();

	GPIO_Pin(GPIOB, _ss, GPIO_STATE_HIGH);
	GPIO_SetMode(GPIOB, _ss, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_GPIO);

	SPI -> CR1 = 0;
	SPI -> CR2 = 0;

	if(_spi_mode != SPI_MODE_0)
	{
		SPI -> CR1 |= (_spi_mode  << SPI_CPHA);								//Set SPI Mode
	}

	if(_spi_prescalar != SPI_CLK_DIV_BY_2)
	{
		SPI -> CR1 |= (_spi_prescalar << SPI_BR);							//Set SPI Speed
	}

	if(_spi_opmode == SPI_MASTER_MODE)
	{
		SPI -> CR1 |= (1 << SPI_MSTR);										//Enable MSTR Bit (For SPI MASTER MODE)
	}
	SPI -> CR1 |= (1 << SPI_SSM);											//Enable SSM Bit
	SPI -> CR1 |= (1 << SPI_SSI);											//Enable SSI Bit

	SPI -> CR1 |= (1 << SPI_SPE);  											//Enable SPI
}

void SPI_Deinit(SPI_PERIPHERALS_t* SPI)
{
	if(SPI == SPI1)
	{
		RCC -> APB2RSTR |= (1 << SPI1RST);
	}

	else if(SPI == SPI2)
	{
		RCC -> APB1RSTR |= (1 << SPI2RST);
	}

	else if(SPI == SPI3)
	{
		RCC -> APB1RSTR |= (1 << SPI3RST);
	}

	else if(SPI == SPI4)
	{
		RCC -> APB2RSTR |= (1 << SPI4RST);
	}
}

void SPI_BeginTransmission(SPI_PERIPHERALS_t* SPI, GPIO_PERIPHERALS_t* _port, uint8_t _ss)
{
	while((SPI -> SR & (1 << SPI_BSY)));
	while(!(SPI -> SR & (1 << SPI_TXE)));

	_port -> ODR &= ~(1 << _ss);
}

void SPI_Write(SPI_PERIPHERALS_t* SPI, uint8_t _data)
{
	while((SPI -> SR & (1 << SPI_BSY)));
	while(!(SPI -> SR & (1 << SPI_TXE)));

	SPI -> DR = _data;
}

void SPI_WriteMulti(SPI_PERIPHERALS_t* SPI, uint8_t* _data, uint32_t _nBytes)
{
	for(uint32_t i=0; i<_nBytes; i++)
	{
		while((SPI -> SR & (1 << SPI_BSY)));
		while(!(SPI -> SR & (1 << SPI_TXE)));

		SPI -> DR = _data[i];
	}
}

void SPI_EndTransmission(SPI_PERIPHERALS_t* SPI, GPIO_PERIPHERALS_t* _port, uint8_t _ss)
{
	while((SPI -> SR & (1 << SPI_BSY)));
	while(!(SPI -> SR & (1 << SPI_TXE)));

	_port -> ODR |= (1 << _ss);
}

uint8_t SPI_Read(SPI_PERIPHERALS_t* SPI)
{
	while((SPI -> SR & (1 << SPI_BSY)));
	while(!(SPI -> SR & (1 << SPI_RXNE)));

	return (SPI -> DR);
}
