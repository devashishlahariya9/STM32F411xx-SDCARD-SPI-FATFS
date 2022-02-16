/*
 * STM32F411xx_GPIO.c
 *
 * Created on: 03-Nov-2021
 * Author: Devashish Lahariya
*/

#include <STM32F411xx_GPIO.h>

void GPIO_setMode(uint8_t _port, uint8_t _pin, uint8_t _speed, uint8_t _type, uint8_t _mode)
{
	switch(_port)
	{
		case PORTA:
			RCC   -> AHB1ENR |= (1 << GPIOAEN);
			GPIOA -> MODER &= ~(3 << (_pin * 2));
			GPIOA -> OSPEEDR |= (_speed << (_pin * 2));
			GPIOA -> OTYPER  |= (_type << _pin);
			GPIOA -> MODER   |= (_mode << (_pin * 2));
			break;

		case PORTB:
			RCC   -> AHB1ENR |= (1 << GPIOBEN);
			GPIOB -> MODER &= ~(3 << (_pin * 2));
			GPIOB -> OSPEEDR |= (_speed << (_pin * 2));
			GPIOB -> OTYPER  |= (_type << _pin);
			GPIOB -> MODER   |= (_mode << (_pin * 2));
			break;

		case PORTC:
			RCC   -> AHB1ENR |= (1 << GPIOCEN);
			GPIOC -> MODER &= ~(3 << (_pin * 2));
			GPIOC -> OSPEEDR |= (_speed << (_pin * 2));
			GPIOC -> OTYPER  |= (_type << _pin);
			GPIOC -> MODER   |= (_mode << (_pin * 2));
			break;

		case PORTD:
			RCC   -> AHB1ENR |= (1 << GPIODEN);
			GPIOD -> MODER &= ~(3 << (_pin * 2));
			GPIOD -> OSPEEDR |= (_speed << (_pin * 2));
			GPIOD -> OTYPER  |= (_type << _pin);
			GPIOD -> MODER   |= (_mode << (_pin * 2));
			break;

		case PORTE:
			RCC   -> AHB1ENR |= (1 << GPIOEEN);
			GPIOE -> MODER &= ~(3 << (_pin * 2));
			GPIOE -> OSPEEDR |= (_speed << (_pin * 2));
			GPIOE -> OTYPER  |= (_type << _pin);
			GPIOE -> MODER   |= (_mode << (_pin * 2));
			break;
	}
}

void GPIO_pin(uint8_t _port, uint8_t _pin, uint8_t _state)
{
	switch(_port)
	{
		case PORTA:
			switch(_state)
			{
			case LOW:
				GPIOA -> ODR &= ~(1 << _pin);
				break;

			case HIGH:
				GPIOA -> ODR |= (1 << _pin);
				break;
			}
			break;

		case PORTB:
			switch(_state)
			{
			case LOW:
				GPIOB -> ODR &= ~(1 << _pin);
				break;

			case HIGH:
				GPIOB -> ODR |= (1 << _pin);
				break;
			}
			break;

		case PORTC:
			switch(_state)
			{
			case LOW:
				GPIOC -> ODR &= ~(1 << _pin);
			break;

			case HIGH:
				GPIOC -> ODR |= (1 << _pin);
			break;
			}
			break;

		case PORTD:
			switch(_state)
			{
			case LOW:
				GPIOD -> ODR &= ~(1 << _pin);
				break;

			case HIGH:
				GPIOD -> ODR |= (1 << _pin);
				break;
			}
			break;

		case PORTE:
			switch(_state)
			{
			case LOW:
				GPIOE -> ODR &= ~(1 << _pin);
				break;

			case HIGH:
				GPIOE -> ODR |= (1 << _pin);
				break;
			}
			break;
	}
}

void GPIO_toggle(uint8_t _port, uint8_t _pin)
{
	switch(_port)
	{
		case PORTA:
			GPIOA -> ODR ^= (1 << _pin);
			break;

		case PORTB:
			GPIOB -> ODR ^= (1 << _pin);
			break;

		case PORTC:
			GPIOC -> ODR ^= (1 << _pin);
			break;

		case PORTD:
			GPIOD -> ODR ^= (1 << _pin);
			break;

		case PORTE:
			GPIOE -> ODR ^= (1 << _pin);
			break;
	}
}
