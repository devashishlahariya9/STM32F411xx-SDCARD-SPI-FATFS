/*
 * STM32F411xx_GPIO.c
 *
 * Created on: 03-Nov-2021
 * Author: Devashish Lahariya
*/

#include "STM32F411xx_GPIO.h"

#define STK_COUNTFLAG	16U
#define STK_CLKSOURCE	2U
#define STK_TICKINT		1U
#define STK_ENABLE		0U

#define STK_RELOAD		0U

#define STK_CURRENT		0U

#define STK_TENMS		0U
#define STK_SKEW		30U
#define STK_NOREF		31U

void FPU_Init(void)
{
	FPU -> CPACR = (0xF << 20);

	while(!(FPU -> CPACR & (0xF << 20)));
}

void Sys_Delay_ms(uint32_t _delay)
{
	FPU_Init();

	double SYS_CLK = (double)F_CPU / (double)8;
	double time_period = (double)1 / (double)SYS_CLK;
	double delay_time_ms = (double)_delay / (double)1000;

	int value = (double)delay_time_ms / (double)time_period;

	STK -> CTRL &= ~(1 << STK_CLKSOURCE);
	STK -> LOAD = (value + 12400);
	STK -> CTRL |= (1 << STK_ENABLE);

	while((STK -> VAL) != 0);

	STK -> LOAD = 0;
	STK -> CTRL &= ~(1 << STK_ENABLE);
}

void GPIO_SetMode(GPIO_PERIPHERALS_t* _port, uint8_t _pin, uint8_t _speed, uint8_t _type, uint8_t _mode)
{
	_port -> MODER   &= ~(3 << (_pin * 2));
	_port -> OSPEEDR &= ~(3 << (_pin * 2));
	_port -> OTYPER  &= ~(1 << _pin);

	if(_mode > GPIO_MODE_INPUT)
	{
		_port -> MODER |= (_mode << (_pin * 2));
	}

	if(_speed > GPIO_LOW_SPEED)
	{
		_port -> OSPEEDR |= (_speed << (_pin * 2));
	}

	if(_type > GPIO_MODE_PUSH_PULL)
	{
		_port -> OTYPER  |= (_type << _pin);
	}
}

void GPIO_Pin(GPIO_PERIPHERALS_t* _port, uint8_t _pin, uint8_t _state)
{
	if(_state == GPIO_STATE_LOW)
	{
		_port -> ODR &= ~(1 << _pin);
	}
	else
	{
		_port -> ODR |= (1 << _pin);
	}
}

void GPIO_Toggle(GPIO_PERIPHERALS_t* _port, uint8_t _pin)
{
	_port -> ODR ^= (1 << _pin);
}

void GPIO_WriteToPort(GPIO_PERIPHERALS_t* _port, uint16_t _value)
{
	_port -> ODR = _value;
}

uint8_t GPIO_GetStatus(GPIO_PERIPHERALS_t* _port, uint8_t _pin)
{
	if((_port -> IDR & (1 << _pin))) return 1;
	else return 0;
}

uint16_t GPIO_ReadPort(GPIO_PERIPHERALS_t* _port)
{
	return (_port -> IDR);
}
