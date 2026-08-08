/*
 * adc.c
 *
 *  Created on: Jan 14, 2026
 *      Author: Eric
 */

#define STM32F411xE
#include "stm32f4xx.h"

//void ADC_Init(void){
//	RCC -> APB2ENR |= (1 << 8); // enable ADC1 clock
//	ADC -> CCR |= (1 << 16); // set prescaler to 4 (divide 96MHz to 24MHz)
//
//	ADC1 -> CR1 |= (0 << 24); // set resolution
//	ADC1 -> SMPR2 |= (7 << 3);
//	ADC1 -> CR2 |= (0 << 11); // sets L/R data alignment *double check*, currently set to right
//    ADC1 -> CR2 |= (1 << 9);
//	ADC1 -> CR2 |= (1 << 8); // enables dma
//	ADC1 -> CR2 |= (1 << 1); // set continuous conversion
//	ADC1 -> SQR3 |= (1 << 0);  // SQ1 = Channel 1
//
//	ADC1 -> CR2 |= (1);
//	for(int i = 0; i < 10000; i++);
//	ADC1 -> CR2 |= (1 << 30); // STARTS ADC
//}


void ADC_Init(void){
    RCC -> APB2ENR |= (1 << 8); // enable ADC1 clock
    ADC -> CCR |= (1 << 16);    // set prescaler to 4

    ADC1 -> CR1 |= (0 << 24);   // set resolution
    ADC1 -> SMPR2 |= (7 << 3);
    ADC1 -> CR2 |= (0 << 11);   // Right alignment
    ADC1 -> CR2 |= (1 << 9);    // DMA enable
    ADC1 -> CR2 |= (1 << 8);    // DMA mode


    ADC1 -> SQR3 |= (1 << 0); // channel 1
    ADC1 -> CR2 |= (1 << 28);
    ADC1 -> CR2 |= (6 << 24);
    ADC1 -> CR2 |= (1);
    for(int i = 0; i < 10000; i++);
}

void TIM2_Init(void) {
    RCC -> APB1ENR |= (1 << 0); // enable clock
    TIM2 -> PSC = 96 - 1; // set prescaler
    TIM2 -> ARR = 10 - 1;
    TIM2 -> CR2 &= ~(7 << 4);
    TIM2 -> CR2 |= (2 << 4);
    TIM2 -> CR1 |= (1 << 0); // enable tim2
}
