/*
 * STM32F411xx.h
 *
 * Created on: Sep 1, 2021
 * Author: Devashish Lahariya
*/


#ifndef _STM32F411XX_H_
#define _STM32F411XX_H_
#include <stdint.h>

#define F_CPU 16000000UL

//RCC -> AHB1ENR
#define GPIOAEN  0U
#define GPIOBEN  1U
#define GPIOCEN  2U
#define GPIODEN  3U
#define GPIOEEN  4U
#define GPIOHEN  7U
#define CRCEN    12U
#define DMA1EN   21U
#define DMA2EN   22U

//RCC -> AHB2ENR
#define OTGFSEN  7U

//RCC -> APB1ENR
#define TIM2EN   0U
#define TIM3EN   1U
#define TIM4EN   2U
#define TIM5EN   3U
#define WWDGEN   11U
#define SPI2EN   14U
#define SPI3EN   15U
#define USART2EN 17U
#define I2C1EN   21U
#define I2C2EN   22U
#define I2C3EN   23U
#define PWREN    28U

//RCC -> APB2ENR
#define TIM1EN   0U
#define USART1EN 4U
#define USART6EN 5U
#define ADC1EN   8U
#define SDIOEN   11U
#define SPI1EN   12U
#define SPI4EN   13U
#define SYSCFGEN 14U
#define TIM9EN   16U
#define TIM10EN  17U
#define TIM11EN  18U
#define SPI5EN   20U

//RCC -> APB1RSTR
#define TIM2RST   0U
#define TIM3RST   1U
#define TIM4RST   2U
#define TIM5RST   3U
#define WWDGRST   11U
#define SPI2RST   14U
#define SPI3RST   15U
#define USART2RST 17U
#define I2C1RST   21U
#define I2C2RST   22U
#define I2C3RST   23U
#define PWRRST    28U

//RCC -> APB2RSTR
#define TIM1RST   0U
#define USART1RST 4U
#define USART6RST 5U
#define ADC1RST   8U
#define SDIORST   11U
#define SPI1RST   12U
#define SPI4RST   13U
#define SYSCFGRST 14U
#define TIM9RST   16U
#define TIM10RST  17U
#define TIM11RST  18U
#define SPI5RST   20U

//SYSCFG
#define EXTI0  	 0U
#define EXTI1  	 4U
#define EXTI2  	 8U
#define EXTI3  	 12U

#define EXTI4  	 0U
#define EXTI5    4U
#define EXTI6    8U
#define EXTI7  	 12U

#define EXTI8  	 0U
#define EXTI9  	 4U
#define EXTI10 	 8U
#define EXTI11 	 12U

#define EXTI12 	 0U
#define EXTI13 	 4U
#define EXTI14 	 8U
#define EXTI15 	 12U

typedef struct 	 //RCC_POINTERS
{
	uint32_t CR;
	uint32_t PLLCFGR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;
	uint32_t RESERVED1;
	uint32_t RESERVED2;
	uint32_t APB1RSTR;
	uint32_t APB2RSTR;
	uint32_t RESERVED3;
	uint32_t RESERVED4;
	uint32_t AHB1ENR;
	uint32_t AHB2ENR;
	uint32_t RESERVED5;
	uint32_t RESERVED6;
	uint32_t APB1ENR;
	uint32_t APB2ENR;
	uint32_t RESERVED7;
	uint32_t RESERVED8;
	uint32_t AHB1LPENR;
	uint32_t AHB2LPENR;
	uint32_t RESERVED9;
	uint32_t RESERVED10;
	uint32_t APB1LPENR;
	uint32_t APB2LPENR;
	uint32_t RESERVED11;
	uint32_t RESERVED12;
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t RESERVED13;
	uint32_t RESERVED14;
	uint32_t SSCGR;
	uint32_t PLLI2SCFGR;
	uint32_t RESERVED15;
	uint32_t DCKCFGR;
}RCC_PERIPHERALS_t;

typedef struct 	//GPIO_POINTERS
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
}GPIO_PERIPHERALS_t;

typedef struct	//SYSTICK_POINTERS
{
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;
}SYSTICK_TIMER_t;

typedef struct 	//SPI_POINTERS
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SR;
	uint32_t DR;
	uint32_t CRCPR;
	uint32_t RXCRCR;
	uint32_t TXCRCR;
	uint32_t I2SCFGR;
	uint32_t I2SPR;
}SPI_PERIPHERALS_t;

typedef struct 	//FPU_POINTERS
{
	uint32_t CPACR;
	uint32_t FPCCR;
	uint32_t FPCAR;
	uint32_t FPSCR;
	uint32_t FPDSCR;
}FPU_PERIPHERALS_t;

typedef struct 	 //I2C_POINTERS
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t OAR1;
	uint32_t OAR2;
	uint32_t DR;
	uint32_t SR1;
	uint32_t SR2;
	uint32_t CCR;
	uint32_t TRISE;
	uint32_t FLTR;
}I2C_PERIPHERALS_t;

typedef struct 	  //EXTI_POINTERS
{
	uint32_t IMR;
	uint32_t EMR;
	uint32_t RTSR;
	uint32_t FTSR;
	uint32_t SWIER;
	uint32_t PR;
}EXTI_PERIPHERALS_t;

typedef struct 	 //NVIC_ISER_POINTERS
{
	uint32_t ISER[8];
}NVIC_ISER_PERIPHERALS_t;

typedef struct 	 //NVIC_ICER_POINTERS
{
	uint32_t ICER[8];
}NVIC_ICER_PERIPHERALS_t;

typedef struct 	 // NVIC_ISPR_POINTERS
{
	uint32_t ISPR[8];
}NVIC_ISPR_PERIPHERALS_t;

typedef struct 	 //NVIC_ICPR_POINTERS
{
	uint32_t ICPR[8];
}NVIC_ICPR_PERIPHERALS_t;

typedef struct 	 //NVIC_IABR_POINTERS
{
	uint32_t IABR[8];
}NVIC_IABR_PERIPHERALS_t;

typedef struct 	 // NVIC_IPR_POINTERS
{
	uint32_t IPR[60];
}NVIC_IPR_PERIPHERALS_t;

typedef struct 	 //SYSCFG_POINTERS
{
	uint32_t MEMRMP;
	uint32_t PMC;
	uint32_t EXTICR[4];
	uint32_t CMPCR;
}SYSCFG_PERIPHERALS_t;

typedef struct	//ADC POINTERS
{
	uint32_t SR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMPR1;
	uint32_t SMPR2;
	uint32_t JOFR1;
	uint32_t JOFR2;
	uint32_t JOFR3;
	uint32_t JOFR4;
	uint32_t HTR;
	uint32_t LTR;
	uint32_t SQR1;
	uint32_t SQR2;
	uint32_t SQR3;
	uint32_t JSQR;
	uint32_t JDR1;
	uint32_t JDR2;
	uint32_t JDR3;
	uint32_t JDR4;
	uint32_t DR;
}ADC_PERIPHERALS_t;

typedef struct	//DMA_POINTERS
{
	uint32_t LISR;
	uint32_t HISR;
	uint32_t LIFCR;
	uint32_t HIFCR;
}DMA_PERIPHERALS_t;

typedef struct	//DMA_STREAM_POINTERS
{
	uint32_t CR;
	uint32_t NDTR;
	uint32_t PAR;
	uint32_t M0AR;
	uint32_t M1AR;
	uint32_t FCR;
}DMA_STREAM_t;

#endif /* STM32F411XX_H_ */
