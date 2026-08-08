/*
 * dma.c
 *
 *  Created on: Jan 13, 2026
 *      Author: Eric
 */

#define STM32F411xE
#include "stm32f4xx.h"
#include "global_var.h"

void DMA_Init(void){
	RCC -> AHB1ENR |= (1 << 22); // enable dma2 clock
	DMA2_Stream4 -> PAR = (uint32_t)(&ADC1 -> DR); // set address of input data register
	DMA2_Stream4 -> M0AR = (uint32_t)adc_buffer;


	DMA2_Stream4 -> CR = (0);
	while(DMA2_Stream4 -> CR);

	DMA2_Stream4 -> NDTR = BUFFER_LEN; // set size of buffer

	DMA2_Stream4 -> CR = (0);// select channel
	DMA2_Stream4 -> CR |= (1 << 13); // set memory size as 16 bit
	DMA2_Stream4 -> CR |= (1 << 11); // set peripheral size as 16 bit
	DMA2_Stream4 -> CR |= (1 << 10); // memory address increments
	DMA2_Stream4 -> CR |= (0 << 9); // peripheral address static
	DMA2_Stream4 -> CR |= (1 << 8); // enable circular mode
	DMA2_Stream4 -> CR |= (0 << 5); // set dma as flow controller
	DMA2_Stream4 -> CR |= (1 << 4); // interrupt when full transfer complete
	DMA2_Stream4 -> CR |= (1 << 3); // interrupt when half transfer complete
	DMA2_Stream4 -> CR |= (1); // enables stream

	NVIC_EnableIRQ(60); // setting NVIC to look at position 60 (dma2 stream4 flags)
	NVIC_SetPriority(60, 0); // setting priority 0 (highest prio)
}


void DMA2_Stream4_IRQHandler(void){
	if (DMA2 -> HISR & (1 << 4)){ // if half transfer complete
		DMA2 -> HIFCR |= (1 << 4); // clears half transfer flag
		data_ready_flag = 1;
		for (int i = 0; i < (BUFFER_LEN/2); i++){
			safe_buffer[i] = adc_buffer[i];
		}
	}
	if (DMA2 -> HISR & (1 << 5)) { // full transfer complete
		DMA2 -> HIFCR |= (1 << 5); // clears full transfer flag
		data_ready_flag = 1;
		for (int i = 0; i < BUFFER_LEN/2; i++){
			safe_buffer[i] = adc_buffer[i+(BUFFER_LEN/2)];
		}
	}
}

//uint32_t Find_Trigger(uint16_t* safe_buffer, int trigger_value) {
//	for(int i = 1; i < (BUFFER_LEN - 280); i++){
//		if(safe_buffer[i] > trigger_value){
//			if(safe_buffer[i-1] < trigger_value){
//				return i;
//			}
//		}
//	}
//	return -1;
//}


uint32_t Find_Trigger(uint16_t* safe_buffer, int trigger_value) {
    for(int i = 1; i < ((BUFFER_LEN/2) - 280); i++){
        if(safe_buffer[i] > trigger_value){
            if(safe_buffer[i-1] < trigger_value){
                return i;
            }
        }
    }
    return -1;
}
