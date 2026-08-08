/*
 * clock.c
 *
 *  Created on: Jan 11, 2026
 *      Author: Eric
 */
#define STM32F411xE
#include "stm32f4xx.h"

void RCC_Init(void){
	RCC -> APB1ENR |= (1 << 28); // turns on APB1 clock (pwren)
	PWR -> CR &= ~(3 << 14);
	PWR -> CR |= (2 << 14);
	FLASH -> ACR |= (3);
	FLASH -> ACR |= (7 << 8);
	RCC -> CFGR |= (4 << 10);
	RCC -> CR |= (RCC_CR_HSEON);
	while(!(RCC_CR_HSERDY & RCC -> CR));

	// setting PLL multipliers/dividers
	RCC -> PLLCFGR = 0;
	RCC -> PLLCFGR |= (25);
	RCC -> PLLCFGR |= (192 << 6);
	RCC -> PLLCFGR |= (0 << 16);
	RCC -> PLLCFGR |= (1 << 22);
	RCC -> PLLCFGR |= (4 << 24);

	RCC -> CR |= RCC_CR_PLLON;

	while(!(RCC_CR_PLLRDY & RCC -> CR));
	RCC -> CFGR |= RCC_CFGR_SW_PLL;

	while((RCC -> CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}


