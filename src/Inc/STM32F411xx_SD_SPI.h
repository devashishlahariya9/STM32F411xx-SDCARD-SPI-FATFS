/*
 * STM32F411xx_SD.h
 *
 * Created on: 17-Jan-2022
 * Author: Devashish Lahariya
*/

#ifndef STM32F411XX_SD_SPI_H_
#define STM32F411XX_SD_SPI_H_

#include <stdio.h>
#include <string.h>
#include <STM32F411xx_SPI1.h>

#define SPI_CS 			6

#define SD_CMD0			0		//Software Reset
#define SD_CMD1			1		//Initiate Initialization Process
#define SD_CMD8			8		//For Only SDC V2. Check Voltage Range
#define SD_CMD9			9       //Read CSD Register
#define SD_CMD10		10      //Read CID Register
#define SD_CMD12		12      //Stop To Read Data
#define SD_CMD13		13		//IDK Why But Important
#define SD_CMD16		16      //Change R/W Block Size
#define SD_CMD17		17      //Read Block
#define SD_CMD18		18      //Read Multiple Blocks
#define SD_CMD23		23      //For Only MMC. Define Number Of Blocks To Transfer With Next Multi-Block R/W Command
#define SD_CMD24		24      //Write A Block
#define SD_CMD25		25      //Write Multiple Blocks
#define SD_CMD55		55      //Leading Command Of ACMD<n> Command
#define SD_CMD58		58      //Read OCR
#define SD_ACMD23		23      //For Only SDC. Define Number Of Blocks To Pre-Erase With Next Multi-Block Write Command
#define SD_ACMD41		41      //For Only SDC Initiate Initialization Process

#define SD_CMD0_ARG		0x00000000
#define SD_CMD8_ARG		0x000001AA
#define SD_CMD55_ARG	0x00000000
#define SD_ACMD41_ARG	0x40000000
#define SD_CMD58_ARG	0x00000000
#define SD_CMD13_ARG	0x00000000

#define SD_CMD0_CRC 	0x95
#define SD_CMD8_CRC		0x87
#define SD_CMD55_CRC	0xFF
#define SD_CMD58_CRC	0xFD
#define SD_ACMD41_CRC	0xFF
#define SD_CMD13_CRC	0xFF
#define SD_CMD16_CRC 	0xFF
#define SD_CMD17_CRC 	0xFF
#define SD_CMD24_CRC 	0xFF
#define SD_CMD25_CRC 	0xFF

#define SD_BLOCKSIZE	0x00000200	//512 (decimal)

uint8_t SD_Init(void);
void SD_readBlock(uint32_t _block, uint8_t* _buffer);
void SD_writeBlock(uint32_t _block, uint8_t _buffer[]);

#endif /* STM32F411XX_SD_SPI_H_ */
