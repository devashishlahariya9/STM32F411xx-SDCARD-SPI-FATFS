/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include <diskio.h>					/* Declarations of disk functions */
#include <ff.h>						/* Obtains integer types */
#include <STM32F411xx_SD_SPI.h>

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

/*------------------------------------------------*/
/*---------ACTUAL FUNCTIONS TO READ/WRITE---------*/
/*------------------------------------------------*/

static volatile DSTATUS Stat = STA_NOINIT;

DSTATUS disk_status(BYTE pdrv)
{
//	DSTATUS stat;

	if(pdrv) return STA_NOINIT;

	return Stat;			//Set Stat In SD_Init(), i.e disk_initialize();
}

/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(BYTE pdrv)
{
	BYTE result = SD_Init();

	if (result == 1)			//OK
	{
		Stat &= ~STA_NOINIT;	//Clear STA_NOINIT Flag
	}
	else						//Failed
	{
		Stat = STA_NOINIT;
	}
	return Stat;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (BYTE pdrv, BYTE* buff, LBA_t sector, UINT count)
{
//	DWORD sect = (DWORD)sector;

	if(pdrv || !count)	  return RES_PARERR;	//Check Parameter
	if(Stat & STA_NOINIT) return RES_NOTRDY;	//Check If Drive Is Ready

	if(count == 1)								//Single Sector Read
	{
		SD_readBlock(sector, buff);
		count = 0;
	}
	else										//Multi Sector Read (Currently Implemented Using Single Block Read APIs)
	{
		int cnt = count;

		for(int i=0; i<cnt; i++)
		{
			SD_readBlock(sector + i, buff);
			count--;
		}
	}
	return (count ? RES_ERROR : RES_OK);		//Return Result
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write(BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count)
{
//	DWORD sect = (DWORD)sector;

	if(pdrv || !count) 	  return RES_PARERR;	//Check parameter
	if(Stat & STA_NOINIT) return RES_NOTRDY;	//Check drive status

	if(count == 1)								//Single Sector Write
	{
		SD_writeBlock(sector, buff);
		count = 0;
	}
	else										//Multi Sector Write (Currently Implemented Using Single Block Write APIs)
	{
		int cnt = count;

		for(int i=0; i<cnt; i++)
		{
			SD_writeBlock(sector + i, buff);
			count--;
		}
	}
	return (count ? RES_ERROR : RES_OK);		//Return Result
}

#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
	DRESULT res;

	res = RES_OK;

	return res;
}
