/*
 * ILI9341.c
 *
 *  Created on: Jan 12, 2026
 *      Author: Eric
 */
#define STM32F411xE

#include "stm32f4xx.h"
#define CS 4
#define RST 3
#define DC 6
#define MOSI 7

uint16_t digits[11] = {31599, 29850, 29671, 31207, 23497, 31183, 31215, 29257, 31727, 31689, 8192};

void Send_Command(uint8_t cmd){
	GPIOA -> BSRR = (1 << (DC + 16)); // turns dc low
	GPIOA -> BSRR = (1 << (CS + 16)); // turns cs low
	SPI1 -> DR = cmd;
	while(!(SPI1 -> SR & (1 << 1)));
	while(SPI1 -> SR & (1 << 7));
	GPIOA -> BSRR = (1 << CS);
}

void Send_Data(uint8_t data) {
	GPIOA -> BSRR = (1 << (DC));
	GPIOA -> BSRR = (1 << (CS + 16));
	SPI1 -> DR = data;
	while(!(SPI1 -> SR & (1 << 1)));
	while(SPI1 -> SR & (1 << 7));
	GPIOA -> BSRR = (1 << CS);
}

void ILI9341_Init(void){
	GPIOA -> BSRR = (1 << (RST + 16));
	for(int i = 0; i < 50000; i++);
	GPIOA -> BSRR = (1 << RST);
	for(int i = 0; i < 50000; i++);
	Send_Command(0x01);
	for(int i = 0; i < 50000; i++);
	Send_Command(0x3A);
	Send_Data(5); // sets pixel format as 16 bit
	Send_Command(0x11); // sleepout command
	for(volatile int i = 0; i < 3000000; i++);
	Send_Command(0X36);
	Send_Data(40);

	Send_Command(0x29); // turns display on
}

void ILI9341_Set_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {

    Send_Command(0x2A); // set columns
    Send_Data(x1 >> 8);
    Send_Data(x1 & 0xFF);
    Send_Data(x2 >> 8);
    Send_Data(x2 & 0xFF);

    Send_Command(0x2B); // set rows
    Send_Data(y1 >> 8);
    Send_Data(y1 & 0xFF);
    Send_Data(y2 >> 8);
    Send_Data(y2 & 0xFF);

    Send_Command(0x2C); // memory write
}

void draw_num(uint16_t num, int x, int y){
	ILI9341_Set_Address(x, y, (x + 2), (y + 4));
	for(int i = 0; i < 15; i++){
		if((num >> i) & (1)){
			Send_Data(0xFF); Send_Data(0xFF);
		} else {
			Send_Data(0x00); Send_Data(0x00);
		}
	}
}

void draw_line(int x1, int y1, int x2, int y2){
	ILI9341_Set_Address(x1, y1, x2, y2);
	for(int i = 0; i < ((x2 - x1) + (y2 - y1)); i++){
		Send_Data(0xFF); Send_Data(0xFF);
	}
}

void ILI9341_Borders(void) {
	draw_line(19, 22, 19, 220); // y axis line
	draw_line(19, 220, 300, 220); // x axis line
	draw_line(15, 22, 19, 22); // 3.3v
	draw_num(digits[3], 3, 20); draw_num(digits[10], 7, 20); draw_num(digits[3], 11, 20); // 3.3

	draw_line(15, 40, 19, 40); // 3v
	draw_num(digits[3], 3, 38); draw_num(digits[10], 7, 38); draw_num(digits[0], 11, 38); // 3.0

	draw_line(15, 70, 19, 70); // 2.5v
	draw_num(digits[2], 3, 68); draw_num(digits[10], 7, 68); draw_num(digits[5], 11, 68); // 2.5

	draw_line(15, 100, 19, 100); // 2v
	draw_num(digits[2], 3, 98); draw_num(digits[10], 7, 98); draw_num(digits[0], 11, 98); // 2.0

	draw_line(15, 130, 19, 130); // 1.5v
	draw_num(digits[1], 3, 128); draw_num(digits[10], 7, 128); draw_num(digits[5], 11, 128); // 1.5

	draw_line(15, 160, 19, 160); // 1v
	draw_num(digits[1], 3, 158); draw_num(digits[10], 7, 158); draw_num(digits[0], 11, 158); // 1.0

	draw_line(15, 190, 19, 190); // 0.5v
	draw_num(digits[0], 3, 188); draw_num(digits[10], 7, 188); draw_num(digits[5], 11, 188); // 0.5
}

