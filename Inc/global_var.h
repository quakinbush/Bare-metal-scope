/*
 * global_var.h
 *
 *  Created on: Jan 15, 2026
 *      Author: Eric
 */
#define STM32F411xE
#include "stm32f4xx.h"

#ifndef GLOBAL_VAR_H_
#define GLOBAL_VAR_H_

#define BUFFER_LEN 1600
extern volatile uint16_t adc_buffer[BUFFER_LEN];
extern volatile uint16_t safe_buffer[(BUFFER_LEN)/2];
extern volatile uint8_t data_ready_flag;

#endif /* GLOBAL_VAR_H_ */
