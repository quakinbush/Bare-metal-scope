/*
 * pwm.c
 *
 *  Created on: Jan 31, 2026
 *      Author: Eric
 */

#define STM32F411xE
#include "stm32f4xx.h"

//void PWM_Init(void){
//	RCC -> APB2ENR |= (1 << 16);
//	TIM9 -> ARR |= (19200); // configures frequency
//	TIM9 -> CCMR1 = (0);
//	TIM9 -> CCMR1 |= (0); // set cc1 as output
//	TIM9 -> CCR1 |= (38800); // configures duty cycle
//	TIM9 -> CCMR1 |= (6 << 4); // sets the pwm mode (on when reaches ccr1 value, off when hits arr)
//	TIM9 -> CR1 |= (1);
//	TIM9 -> CCER |= (1);
//}


void PWM_Init(void){
    RCC -> APB2ENR |= (1 << 16);
    TIM9 -> PSC = 9600 - 1;
    TIM9 -> ARR = 2500 - 1; //configures frequency
    TIM9 -> CCR1 = 1000; // configures duty cycle
    TIM9 -> CCMR1 = (6 << 4);
    TIM9 -> CCER |= (1);
    TIM9 -> CR1 |= (1);
}
