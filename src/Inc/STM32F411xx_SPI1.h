/*
 * STM32F411xx_SPI1.h
 *
 * Created on: Sep 1, 2021
 * Author: Devashish Lahariya
*/

#ifndef STM32F411XX_SPI1_H_
#define STM32F411XX_SPI1_H_

//#include "STM32F411xx.h"
#include <STM32F411xx_GPIO.h>

//SPI1 -> CR1
#define SPI_CPHA	 		0U
#define SPI_CPOL 	 		1U
#define SPI_MSTR 	 		2U
#define SPI_BR 		 		3U
#define SPI_SPE 	 		6U
#define SPI_LSBFIRST 		7U
#define SPI_SSI 	 		8U
#define SPI_SSM 	 		9U
#define SPI_RXONLY   		10U
#define SPI_DFF		 		11U
#define SPI_CRCNEXT	 		12U
#define SPI_SPICRCEN 		13U
#define SPI_BIDIOE	 		14U
#define SPI_BIDIMODE 		15U

//SPI1 -> CR2
#define SPI_RXDMAEN  		0U
#define SPI_TXDMAEN  		1U
#define SPI_SSOE	 		2U
#define SPI_FRF		 		4U
#define SPI_ERRIE	 		5U
#define SPI_RXNEIE	 		6U
#define SPI_TXEIE	 		7U

//SPI1 -> SR
#define SPI_RXNE	 		0U
#define SPI_TXE		 		1U
#define SPI_CHSIDE	 		2U
#define SPI_UDR			 	3U
#define SPI_CRCERR	 		4U
#define SPI_MODF	 		5U
#define SPI_OVR		 		6U
#define SPI_BSY		 		7U
#define SPI_FRE		 		8U

//SPI1 -> I2SCFGR
#define SPI_CHLEN	 		0U
#define SPI_DATLEN	 		1U
#define SPI_CKPOL	 		3U
#define SPI_I2SSTD	 		4U
#define SPI_PCMSYNC	 		7U
#define SPI_I2SCFG	 		8U
#define SPI_I2SE	 		10U
#define SPI_I2SMOD	 		11U

//SPI1 -> I2SPR
#define SPI_I2SDIV	 		0U
#define SPI_ODD		 		1U
#define SPI_MCKOE	 		2U

#define SPI_SCK		 		3U
#define SPI_MISO	 		4U
#define SPI_MOSI	 		5U

//SPI OPMODES
#define SPI_SLAVE_MODE  	0U
#define SPI_MASTER_MODE 	1U

uint8_t SPI_SS;

enum SPI_MODES
{
	SPI_MODE_0,		//CLK is Active HIGH & Data is Captured On Leading Edge
	SPI_MODE_1,		//CLK is Active HIGH & Data is Captured On Trailing Edge
	SPI_MODE_2,		//CLK is Active LOW & Data is Captured On Leading Edge
	SPI_MODE_3		//CLK is Active LOW & Data is Captured On Trailing Edge
};

enum SPI_SPEEDS
{
	SPI_CLK_DIV_BY_2,
	SPI_CLK_DIV_BY_4,
	SPI_CLK_DIV_BY_8,
	SPI_CLK_DIV_BY_16,
	SPI_CLK_DIV_BY_32,
	SPI_CLK_DIV_BY_64,
	SPI_CLK_DIV_BY_128,
	SPI_CLK_DIV_BY_256
};

void SPI1_init(uint8_t _ss, uint8_t _spi_opmode , uint8_t _spi_mode, uint8_t _spi_prescalar);
void SPI1_deinit(void);
void SPI1_beginTransmission(void);
void SPI1_write(uint8_t _data);
void SPI1_endTransmission(void);
uint8_t SPI1_read(void);

#endif
