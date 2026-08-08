/*
 * gpio.c
 *
 *  Created on: Jan 11, 2026
 *      Author: Eric
 */
#define STM32F411xE

#include "stm32f4xx.h"

void SPI_GPIO_Init(void){
	RCC -> AHB1ENR |= (1); // turns on gpioa clock

	// spi pin setup
	GPIOA -> MODER |= (2 << 10); // PA5 is clk
	GPIOA -> MODER |= (2 << 14); // PA7 is MOSI
	GPIOA -> AFR[0] |= (5 << 20);
	GPIOA -> AFR[0] |= (5 << 28);

	GPIOA -> MODER |= (1 << 8); // PA4 is ss
	GPIOA -> MODER |= (1 << 12); // PA6 is dc
	GPIOA -> MODER |= (1 << 6); // PA3 is reset

	GPIOA -> OSPEEDR |= (3 << 10); // turns on very high speed
	GPIOA -> OSPEEDR |= (3 << 14);
}

void ADC_GPIO_Init(void){
	RCC -> AHB1ENR |= (1); // turns on gpioa clock
	GPIOA -> MODER |= (3 << 2); // pa1 is input pin
}

void PWM_GPIO_Init(void){
	GPIOA->MODER &= ~(3U << 4);
	RCC -> AHB1ENR |= (1); // turns on gpioa clock
	GPIOA -> MODER |= (2 << 4); // PA2 is tim9_CH1
	GPIOA -> AFR[0] |= (3 << 8);
	GPIOA -> OSPEEDR |= (2 << 4);
}

void GPIO_Init(void){
	SPI_GPIO_Init();
	ADC_GPIO_Init();
	PWM_GPIO_Init();
}
