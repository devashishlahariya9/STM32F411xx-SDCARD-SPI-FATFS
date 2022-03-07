/*
 * STM32F411xx_GPIO.h
 *
 * Created on: 03-Nov-2021
 * Author: Devashish Lahariya
*/

#ifndef STM32F411XX_GPIO_H_
#define STM32F411XX_GPIO_H_

#include <stdint.h>
#include "STM32F411xx.h"

enum GPIO_SPEEDR_MODES
{
	GPIO_LOW_SPEED,
	GPIO_MEDIUM_SPEED,
	GPIO_FAST_SPEED,
	GPIO_HIGH_SPEED
};

enum GPIO_OTYPER_MODES
{
	GPIO_MODE_PUSH_PULL,
	GPIO_MODE_OPEN_DRAIN
};

enum GPIO_MODER_MODES
{
	GPIO_MODE_INPUT,
	GPIO_MODE_GPIO,
	GPIO_MODE_AFIO,
	GPIO_MODE_ANALOG
};

enum GPIO_STATES
{
	GPIO_STATE_LOW,
	GPIO_STATE_HIGH
};

enum AF
{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
};

/*---------------------------------------------------------------*/
/*--------------------SYSTEM CORE PERIPHERALS--------------------*/
/*---------------------------------------------------------------*/

#define FPU 			((FPU_PERIPHERALS_t*)      0xE000ED88)

#define RCC 			((RCC_PERIPHERALS_t*)      0x40023800)

#define STK				((SYSTICK_TIMER_t*)		   0xE000E010)

#define SYSCFG 			((SYSCFG_PERIPHERALS_t*)   0x40013800)

#define EXTI 			((EXTI_PERIPHERALS_t*)	   0x40013C00)

#define NVIC_ISER 		((NVIC_ISER_PERIPHERALS_t*)0xE000E100)
#define NVIC_ICER 		((NVIC_ICER_PERIPHERALS_t*)0xE000E180)
#define NVIC_ISPR 		((NVIC_ISPR_PERIPHERALS_t*)0xE000E200)
#define NVIC_ICPR 		((NVIC_ICPR_PERIPHERALS_t*)0xE000E280)
#define NVIC_IABR 		((NVIC_IABR_PERIPHERALS_t*)0xE000E300)
#define NVIC_IPR 		((NVIC_IPR_PERIPHERALS_t*) 0xE000E400)

/*---------------------------------------------------------*/
/*--------------------OTHER PERIPHERALS--------------------*/
/*---------------------------------------------------------*/

#define GPIOA 			((GPIO_PERIPHERALS_t*)     0x40020000)
#define GPIOB 			((GPIO_PERIPHERALS_t*)     0x40020400)
#define GPIOC 			((GPIO_PERIPHERALS_t*)	   0x40020800)
#define GPIOD 			((GPIO_PERIPHERALS_t*)	   0x40020C00)
#define GPIOE 			((GPIO_PERIPHERALS_t*)	   0x40021000)

#define UART1			((USART_PERIPHERALS_t*)	   0x40011000)
#define UART2			((USART_PERIPHERALS_t*)	   0x40004400)
#define UART6			((USART_PERIPHERALS_t*)	   0x40011400)

#define USART1			((USART_PERIPHERALS_t*)	   0x40011000)
#define USART2			((USART_PERIPHERALS_t*)	   0x40004400)
#define USART6			((USART_PERIPHERALS_t*)	   0x40011400)

#define SPI1			((SPI_PERIPHERALS_t*)	   0x40013000)
#define SPI2			((SPI_PERIPHERALS_t*)	   0x40003800)
#define SPI3			((SPI_PERIPHERALS_t*)	   0x40003C00)
#define SPI4			((SPI_PERIPHERALS_t*)	   0x40013400)

#define I2C1 			((I2C_PERIPHERALS_t*)	   0x40005400)
#define I2C2 			((I2C_PERIPHERALS_t*)	   0x40005800)
#define I2C3 			((I2C_PERIPHERALS_t*)	   0x40005C00)

#define ADC				((ADC_PERIPHERALS_t*)	   0x40012000)

#define DMA1			((DMA_PERIPHERALS_t*)	   0x40026000)
#define DMA1_STREAM0	((DMA_STREAM_t*)		   0x40026010)
#define DMA1_STREAM1	((DMA_STREAM_t*)		   0x40026028)
#define DMA1_STREAM2	((DMA_STREAM_t*)		   0x40026040)
#define DMA1_STREAM3	((DMA_STREAM_t*)		   0x40026058)
#define DMA1_STREAM4	((DMA_STREAM_t*)		   0x40026070)
#define DMA1_STREAM5	((DMA_STREAM_t*)		   0x40026088)
#define DMA1_STREAM6	((DMA_STREAM_t*)		   0x400260A0)
#define DMA1_STREAM7	((DMA_STREAM_t*)		   0x400260B8)

#define DMA2			((DMA_PERIPHERALS_t*)	   0x40026400)
#define DMA2_STREAM0	((DMA_STREAM_t*)		   0x40026410)
#define DMA2_STREAM1	((DMA_STREAM_t*)		   0x40026428)
#define DMA2_STREAM2	((DMA_STREAM_t*)		   0x40026440)
#define DMA2_STREAM3	((DMA_STREAM_t*)		   0x40026458)
#define DMA2_STREAM4	((DMA_STREAM_t*)		   0x40026470)
#define DMA2_STREAM5	((DMA_STREAM_t*)		   0x40026488)
#define DMA2_STREAM6	((DMA_STREAM_t*)		   0x400264A0)
#define DMA2_STREAM7	((DMA_STREAM_t*)		   0x400264B8)

/*------------------------------------------------------------*/
/*--------------------GPIO CLOCK FUNCTIONS--------------------*/
/*------------------------------------------------------------*/

#define GPIOA_CLK_ENABLE() (RCC -> AHB1ENR |= (1 << GPIOAEN))
#define GPIOB_CLK_ENABLE() (RCC -> AHB1ENR |= (1 << GPIOBEN))
#define GPIOC_CLK_ENABLE() (RCC -> AHB1ENR |= (1 << GPIOCEN))
#define GPIOD_CLK_ENABLE() (RCC -> AHB1ENR |= (1 << GPIODEN))
#define GPIOE_CLK_ENABLE() (RCC -> AHB1ENR |= (1 << GPIOEEN))

#define GPIOA_CLK_DISABLE() (RCC -> AHB1ENR &= ~(1 << GPIOAEN))
#define GPIOB_CLK_DISABLE() (RCC -> AHB1ENR &= ~(1 << GPIOBEN))
#define GPIOC_CLK_DISABLE() (RCC -> AHB1ENR &= ~(1 << GPIOCEN))
#define GPIOD_CLK_DISABLE() (RCC -> AHB1ENR &= ~(1 << GPIODEN))
#define GPIOE_CLK_DISABLE() (RCC -> AHB1ENR &= ~(1 << GPIOEEN))

/*-------------------------------------------------------------*/
/*--------------------SYSTEM CORE FUNCTIONS--------------------*/
/*-------------------------------------------------------------*/

void FPU_Init();
void Sys_Delay_ms(uint32_t _delay);

/*-----------------------------------------------------------*/
/*--------------------GPIO PORT FUNCTIONS--------------------*/
/*-----------------------------------------------------------*/

void GPIO_SetMode(GPIO_PERIPHERALS_t* _port, uint8_t _pin, uint8_t _speed, uint8_t _type, uint8_t _mode);
void GPIO_Pin(GPIO_PERIPHERALS_t* _port, uint8_t _pin, uint8_t _state);
void GPIO_Toggle(GPIO_PERIPHERALS_t* _port, uint8_t _pin);
void GPIO_WriteToPort(GPIO_PERIPHERALS_t* _port, uint16_t _value);

uint8_t GPIO_GetStatus(GPIO_PERIPHERALS_t* _port, uint8_t _pin);
uint16_t GPIO_ReadPort(GPIO_PERIPHERALS_t* _port);

#endif /* STM32F411XX_GPIO_H_ */
