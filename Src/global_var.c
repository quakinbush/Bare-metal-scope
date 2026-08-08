/*
 * global_var.c
 *
 *  Created on: Jan 15, 2026
 *      Author: Eric
 */
#define STM32F411xE
#include "stm32f4xx.h"

#define BUFFER_LEN 1600
volatile uint16_t adc_buffer[BUFFER_LEN];
volatile uint16_t safe_buffer[BUFFER_LEN/2];
volatile uint8_t data_ready_flag = 0;
