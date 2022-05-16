/*
 * main.h
 *
 *  Created on: May 4, 2022
 *      Author: abdelrhman
 */

#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <string.h>

//#include "KeyPad.h"
/*
********************   KEYPAD FUNCTIONS   ********************
keypad has two function one was not necessary but made it only to ease it on main for us which is
1-KeyPad_init() which is made only for initializing portb for keypad and and enable pull up resistor
2- char Get_Key_Pressed(void) which take no input and return the character pressed from the user and if there no character pressed from the user it will return the character N
*/

#include "TEMP.h"   //temp.h has two functions ADC_init() & ADC_Read()
#include "PIR.h"
#include "Buzzer.h"
#include "motor.h"
#include "TEMP.h"
#include "LCD.h"
/*
********************   LCD functions   ********************
 * LCD_initialize() : to  initialize the LCD
 		takes no parameters and return Void
 		it is set Cursor to home position
 		it is auto increment cursor

 *- LCD_send_command( uint8_t command ) : to do an event
		takes 8 bit (in command section below) number and return Void.

 *- LCD_set_Cursor( uint8_t row , uint8_t pos )
		takes : row is in range (0:1)  .... pos is in range (0:15)
		and return Void.
		if it is out of range ... it will be at current position

 *- LCD_display_char( uint8_t data )
		takes 8 bit char and print it

 *- LCD_display_text( uint8_t *str , uint16_t delay  )
		takes pointer to char (array of char) and print it
		delay is time between every char in ms

 *- LCD_shift_entire_display( uint8_t dir , uint8_t num_shift , uint16_t delay)
		takes
		dir : direction of shift ---> 0: left , 1: right
		num_shift : how many time you want to shift
		delay : the delay between every shift in ms
		and return void.

*- LCD_clear() : to clear the hole screen and return to home position
		takes no parameters and return Void

********************   LCD commands   ********************
	LCD_clear_screen 	 		= 0x01 ,
	LCD_auto_Increment_cursor 	= 0x06 ,
	LCD_display_on_cursor_off 	= 0X0C,
	LCD_move_cursor_left 		= 0X10 ,
	LCD_move_cursor_right 		= 0x14 ,
	LCD_shift_entire_left 		= 0x18,
	LCD_shift_entire_right 		= 0x1c,
	LCD_set_mode_8bit_2r 		= 0x38 ,
	LCD_set_Cursor_r0 			= 0X80 ,
	 	 	 	 	 	 //set cursor to row 0 ,then set the position with "|"
	LCD_set_Cursor_r1 			= 0xC0
						//set cursor to row 1 ,then set the position with "|"
*/

void Button_Led_initialize();

#endif /* MAIN_H_ */
