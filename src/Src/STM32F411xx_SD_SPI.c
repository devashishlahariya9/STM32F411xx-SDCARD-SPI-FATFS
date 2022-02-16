/*
 * STM32F411xx_SD.c
 *
 * Created on: 17-Jan-2022
 * Author: Devashish Lahariya
*/

#include <STM32F411xx_SD_SPI.h>

static void SD_Command(uint8_t _cmd, uint32_t _arg, uint8_t _crc)
{
	SPI1_write((uint8_t)(_cmd | 0x40));
	SPI1_write((uint8_t)(_arg >> 24));
	SPI1_write((uint8_t)(_arg >> 16));
	SPI1_write((uint8_t)(_arg >> 8));
	SPI1_write((uint8_t)_arg);
	SPI1_write(_crc);
}

static uint8_t SD_readRes1(void)
{
	uint8_t counter = 0;
	uint8_t resp = 0;

	while((resp = SPI1_read()) != 0x01)
	{
		SPI1_write(0xFF);
		counter++;
		if(counter == 8) break;
	}
	SPI1_write(0xFF);						//Dummy Byte
	return resp;
}

static uint8_t SD_readTillSDOK(void)
{
	uint8_t counter = 0;
	uint8_t resp = 1;

	while(resp != 0x00)
	{
		SPI1_write(0xFF);
		resp = SPI1_read();
		counter++;
		if(counter == 8) break;
	}
	SPI1_write(0xFF);						//Dummy Byte
	return resp;
}

static uint8_t SD_readTillReadOK(void)
{
	uint8_t counter = 0;
	uint8_t resp = 0;

	while(resp != 0xFE)
	{
		SPI1_write(0xFF);
		resp = SPI1_read();
		counter++;
		if(counter == 149) break;
	}
	SPI1_write(0xFF);						//Dummy Byte
	return resp;
}

static void SD_readRes3(void)
{
	SD_readRes1();
	SPI1_write(0xFF);
	SPI1_write(0xFF);
	SPI1_write(0xFF);
	SPI1_write(0xFF);
	SPI1_write(0xFF);
}

static uint8_t SD_waitTillIdleClear(void)
{
	uint8_t resp = 1;
	uint8_t counter = 0;

	while(resp != 0x00)
	{
		SD_Command(SD_CMD55, SD_CMD55_ARG, SD_CMD55_CRC);
		SD_readRes1();
		SD_Command(SD_ACMD41, SD_ACMD41_ARG, SD_ACMD41_CRC);

		if((resp = SD_readTillSDOK()) == 0x00)
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

uint8_t SD_Init(void)
{
	SPI1_init(SPI_CS, SPI_MASTER_MODE, SPI_MODE_0, SPI_CLK_DIV_BY_64);		//SD CLK Set To 250KHz

	SPI1_endTransmission();				//Pull CS HIGH

	for(int i=0; i<3200; i++);			//Wait 2ms

	for(uint8_t i=0; i<10; i++)			//Send 80 BITS
	{
		SPI1_write(0xFF);				//MOSI HIGH
	}
	SPI1_beginTransmission();
	SPI1_write(0xFF);					//Dummy Byte
	SPI1_write(0xFF);					//Dummy Byte

	SD_Command(SD_CMD0, SD_CMD0_ARG, SD_CMD0_CRC);
	uint8_t _res1 = SD_readRes1();

	if(_res1 == 0x01)
	{
		SD_Command(SD_CMD8, SD_CMD8_ARG, SD_CMD8_CRC);
		SD_readRes3();

		uint8_t resp = SD_waitTillIdleClear();

		if(resp == 0x00)
		{
			SPI1_deinit();
			SPI1_init(SPI_CS, SPI_MASTER_MODE, SPI_MODE_0, SPI_CLK_DIV_BY_2);	//Set The Pre-scaler According To Needs
		}
		return resp;
	}
	else return 0;
}

static uint8_t SD_waitTillReadOK(uint32_t _block)
{
	uint8_t resp = 1;
	uint8_t counter = 0;

	while(resp != 0xFE)
	{
		SD_Command(SD_CMD17, _block, SD_CMD17_CRC);
		SD_readTillSDOK();

		if((resp = SD_readTillReadOK()) == 0xFE)
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

void SD_readBlock(uint32_t _block, uint8_t* _buffer)
{
	SPI1_endTransmission();
	SPI1_write(0xFF);
	SPI1_beginTransmission();
	SPI1_write(0xFF);

	SD_waitTillReadOK(_block);

	*_buffer++ = SPI1_read();

	for(uint16_t i=0; i<512; i++)
	{
		SPI1_write(0xFF);
		*_buffer++ = SPI1_read();
	}
	SPI1_write(0xFF);
	SPI1_write(0xFF);

	SPI1_write(0xFF);
	SPI1_endTransmission();
	SPI1_write(0xFF);
}

static uint8_t SD_readWriteFinish(void)
{
	uint8_t counter = 0;
	uint8_t resp = 0;

	while((resp = SPI1_read()) != 0xE5)
	{
		SPI1_write(0xFF);
		counter++;
		if(counter == 8) break;
	}
	SPI1_write(0xFF);
	return resp;
}

static void SD_readTillDataWriteComplete(void)
{
	uint8_t resp = 0;

	SPI1_beginTransmission();

	while((resp = SPI1_read()) == 0x00)
	{
		SPI1_write(0xFF);
	}
	SPI1_endTransmission();
	SPI1_write(0xFF);
	SPI1_write(0xFF);
}

void SD_writeBlock(uint32_t _block, uint8_t _buffer[])
{
	SPI1_endTransmission();
	SPI1_write(0xFF);
	SPI1_beginTransmission();
	SPI1_write(0xFF);

	SD_Command(SD_CMD24, _block, SD_CMD24_CRC);
	SD_readTillSDOK();
	SPI1_write(0xFE);

	for(uint16_t i=0; i<512; i++)
	{
		SPI1_write(_buffer[i]);
	}
	SD_readWriteFinish();
	SD_readTillDataWriteComplete();
}
