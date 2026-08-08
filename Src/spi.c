/*
 * spi.c
 *
 *  Created on: Jan 10, 2026
 *      Author: Eric
 */
#define STM32F411xE

#include "stm32f4xx.h"

void SPI_Init(void){
//	RCC -> APB2ENR |= (1 << 12);
//	SPI1 -> CR1 |= (0 << 3); // redundant for now, but can change to be useful
	RCC -> APB2ENR |= (1 << 12);
	SPI1 -> CR1 |= (2 << 3); // SET PRESCALER TO /8 (12MHz)
	SPI1 -> CR1 |= (0 << 1); // polarity of clock
	SPI1 -> CR1 |= (0 << 11); // package size, cannot be changed before spi is enabled
	SPI1 -> CR1 |= (0 << 0); // which edge data is read on
	SPI1 -> CR1 |= (0 << 7); // which bit is most significant
	SPI1 -> CR1 |= (1 << 9); // controlling SS pin thru software, otherwise if not held high will shut off master
	SPI1 -> CR1 |= (1 << 2); // sets stm as master
	SPI1 -> CR1 |= (1 << 8); // internal ss set as master
	SPI1 -> CR1 |= (1 << 6); // ENABLES SPI
}
