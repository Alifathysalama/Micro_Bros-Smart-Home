/*
 * KeyPad.h
 *
 * Created: 4/24/2022 7:23:13 AM
 *  Author: Alloush
 */
#ifndef KeyPad_H_
#define KeyPad_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define KEY_PRT 	PORTC
#define KEY_DDR		DDRC
#define KEY_PIN		PINC
unsigned char keypad[4][4] = {
				{'1','4','7','*'},
				{'2','5','6','0'},
				{'3','8','9','#'},
				{'A','B','C','D'} };

unsigned char colloc, rowloc;

uint8_t Get_Key_pressed(); // the main function to get the character pressed on the keypad.

#endif/*KeyPad_H_*/
