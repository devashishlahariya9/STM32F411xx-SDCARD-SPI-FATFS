/*
 * STM32F411xx_SD.c
 *
 * Created on: 17-Jan-2022
 * Author: Devashish Lahariya
*/

#include <STM32F411xx_SD_SPI.h>

static void SD_Command(SD_CARD* sd_handler, uint8_t _cmd, uint32_t _arg, uint8_t _crc)
{
	SPI_Write(sd_handler->SPI, (uint8_t)(_cmd | 0x40));
	SPI_Write(sd_handler->SPI, (uint8_t)(_arg >> 24));
	SPI_Write(sd_handler->SPI, (uint8_t)(_arg >> 16));
	SPI_Write(sd_handler->SPI, (uint8_t)(_arg >> 8));
	SPI_Write(sd_handler->SPI, (uint8_t)_arg);
	SPI_Write(sd_handler->SPI, _crc);
}

static uint8_t SD_readRes1(SD_CARD* sd_handler)
{
	uint8_t counter = 0;
	uint8_t resp = 0;

	while((resp = SPI_Read(sd_handler->SPI)) != 0x01)
	{
		SPI_Write(sd_handler->SPI, 0xFF);
		counter++;
		if(counter == 8) break;
	}
	SPI_Write(sd_handler->SPI, 0xFF);						//Dummy Byte

	return resp;
}

static uint8_t SD_readTillSDOK(SD_CARD* sd_handler)
{
	uint8_t counter = 0;
	uint8_t resp = 1;

	while(resp != 0x00)
	{
		SPI_Write(sd_handler->SPI, 0xFF);
		resp = SPI_Read(sd_handler->SPI);
		counter++;
		if(counter == 8) break;
	}
	SPI_Write(sd_handler->SPI, 0xFF);						//Dummy Byte

	return resp;
}

static uint8_t SD_readTillReadOK(SD_CARD* sd_handler)
{
	uint8_t counter = 0;
	uint8_t resp = 0;

	while(resp != 0xFE)
	{
		SPI_Write(sd_handler->SPI, 0xFF);
		resp = SPI_Read(sd_handler->SPI);
		counter++;
		if(counter == 149) break;
	}
	SPI_Write(sd_handler->SPI, 0xFF);						//Dummy Byte

	return resp;
}

static void SD_readRes3(SD_CARD* sd_handler)
{
	SD_readRes1(sd_handler);
	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_Write(sd_handler->SPI, 0xFF);
}

static uint8_t SD_waitTillIdleClear(SD_CARD* sd_handler)
{
	uint8_t resp = 1;
	uint8_t counter = 0;

	while(resp != 0x00)
	{
		SD_Command(sd_handler, SD_CMD55, SD_CMD55_ARG, SD_CMD55_CRC);
		SD_readRes1(sd_handler);
		SD_Command(sd_handler, SD_ACMD41, SD_ACMD41_ARG, SD_ACMD41_CRC);

		if((resp = SD_readTillSDOK(sd_handler)) == 0x00)
		{
			return 1;
		}
		else
		{
			counter++;
			if(counter == 149) break;
		}
	}
	return 0;
}

uint8_t SD_Init(SD_CARD* sd_handler, SPI_PERIPHERALS_t* SPI, void(*remap_func)(void), GPIO_PERIPHERALS_t* CS_GPIO, uint8_t CS)
{
	sd_handler->SPI     = SPI;
	sd_handler->CS_GPIO = CS_GPIO;
	sd_handler->CS      = CS;

	SPI_Init(sd_handler->SPI, remap_func, CS_GPIO, CS, SPI_MASTER_MODE, SPI_MODE_0, SPI_CLK_DIV_BY_64);		//SD CLK Set To 250KHz

	SPI_EndTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);		//Pull CS HIGH

	Sys_Delay_ms(2);									//Wait 2ms

	for(uint8_t i=0; i<10; i++)							//Send 80 BITS
	{
		SPI_Write(sd_handler->SPI, 0xFF);				//MOSI HIGH
	}
	SPI_BeginTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);
	SPI_Write(sd_handler->SPI, 0xFF);					//Dummy Byte
	SPI_Write(sd_handler->SPI, 0xFF);					//Dummy Byte

	SD_Command(sd_handler, SD_CMD0, SD_CMD0_ARG, SD_CMD0_CRC);
	uint8_t _res1 = SD_readRes1(sd_handler);

	if(_res1 == 0x01)
	{
		SD_Command(sd_handler, SD_CMD8, SD_CMD8_ARG, SD_CMD8_CRC);
		SD_readRes3(sd_handler);

		uint8_t resp = SD_waitTillIdleClear(sd_handler);

		if(resp == 0x00)
		{
			SPI_Deinit(sd_handler->SPI);
			SPI_Init(sd_handler->SPI, remap_func, CS_GPIO, CS, SPI_MASTER_MODE, SPI_MODE_0, SPI_CLK_DIV_BY_2);	//Set The Pre-scaler According To Needs
		}
		return resp;
	}
	else return 0;
}

static uint8_t SD_waitTillReadOK(SD_CARD* sd_handler, uint32_t _block)
{
	uint8_t resp = 1;
	uint8_t counter = 0;

	while(resp != 0xFE)
	{
		SD_Command(sd_handler, SD_CMD17, _block, SD_CMD17_CRC);
		SD_readTillSDOK(sd_handler);

		if((resp = SD_readTillReadOK(sd_handler)) == 0xFE)
		{
			return 1;
		}
		else
		{
			counter++;
			if(counter == 149) break;
		}
	}
	return 0;
}

void SD_ReadBlock(SD_CARD* sd_handler, uint32_t _block, uint8_t* _buffer)
{
	SPI_EndTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);
	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_BeginTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);
	SPI_Write(sd_handler->SPI, 0xFF);

	SD_waitTillReadOK(sd_handler, _block);

	*_buffer++ = SPI_Read(sd_handler->SPI);

	for(uint16_t i=0; i<512; i++)
	{
		SPI_Write(sd_handler->SPI, 0xFF);
		*_buffer++ = SPI_Read(sd_handler->SPI);
	}
	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_Write(sd_handler->SPI, 0xFF);

	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_EndTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);
	SPI_Write(sd_handler->SPI, 0xFF);
}

static uint8_t SD_readWriteFinish(SD_CARD* sd_handler)
{
	uint8_t counter = 0;
	uint8_t resp = 0;

	while((resp = SPI_Read(sd_handler->SPI)) != 0xE5)
	{
		SPI_Write(sd_handler->SPI, 0xFF);
		counter++;
		if(counter == 8) break;
	}
	SPI_Write(sd_handler->SPI, 0xFF);
	return resp;
}

static void SD_readTillDataWriteComplete(SD_CARD* sd_handler)
{
	uint8_t resp = 0;

	SPI_BeginTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);

	while((resp = SPI_Read(sd_handler->SPI)) == 0x00)
	{
		SPI_Write(sd_handler->SPI, 0xFF);
	}
	SPI_EndTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);
	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_Write(sd_handler->SPI, 0xFF);
}

void SD_WriteBlock(SD_CARD* sd_handler, uint32_t _block, uint8_t _buffer[])
{
	SPI_EndTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);
	SPI_Write(sd_handler->SPI, 0xFF);
	SPI_BeginTransmission(sd_handler->SPI, sd_handler->CS_GPIO, sd_handler->CS);
	SPI_Write(sd_handler->SPI, 0xFF);

	SD_Command(sd_handler, SD_CMD24, _block, SD_CMD24_CRC);
	SD_readTillSDOK(sd_handler);
	SPI_Write(sd_handler->SPI, 0xFE);

	for(uint16_t i=0; i<512; i++)
	{
		SPI_Write(sd_handler->SPI, _buffer[i]);
	}
	SD_readWriteFinish(sd_handler);
	SD_readTillDataWriteComplete(sd_handler);
}
