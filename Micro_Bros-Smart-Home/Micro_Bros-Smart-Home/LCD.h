/*
 * LCD.h
 *
 *  Created on: Apr 24, 2022
 *      Author: abdelrhman
 */

/*
 *	LCD is (Liquid Crystal Displays) are used for displaying status or
 *	parameters in embedded systems.
 *	it is 2 rows (0:1) and 16 column (0:15)
		._______________________________________________.
		|												|
		|												|
		|					LCD 16*2					|
		|												|
		|												|
		|_______________________________________________|
		   | | |	|  |  |		| | | | | | | | 	| |
		   V V V	R  R  E		D D D D D D D D		L L
		   S C E	S  W		0 1 2 3 4 5 6 7		E E
		   S C E									D D
		   	   	   	   	   	   	   	   	   	   	   	+ -

connection | | |	|  |  |		| | | | | | | |		| |
    to	   | | |	|  |  |		| | | | | | | |		| |
    our	   | | |	|  |  |		| | | | | | | |		| |
 ATmega16 31 30 29 16  17 21	29 28 ....... 22

 	 	  G	 5		P  P  P		P P ...       P		5 G
 	 	  N	 V		A  A  D		C C ...		  C		v N
 	 	  D			3  4  7		0 1 ...		  7		  D

* RS    : register select	 --> 1: data   , 0: command
* RW    : read/write  		 --> 1: write  , 0: read
* E	    : enable			 --> 1: enable , 0: disable
* D0-D7 : takes data or code
* VSS   : to ground
* VCC   : to source
* VEE   : screen brightness
*/


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

enum LCD_command
{
	LCD_clear_screen 	 		= 0x01 ,
	LCD_auto_increment_cursor 	= 0x06 ,
	LCD_display_on_cursor_off 	= 0X0C,
	LCD_move_cursor_left 		= 0X10 ,
	LCD_move_cursor_right 		= 0x14 ,
	LCD_shift_entire_left 		= 0x18,
	LCD_shift_entire_right 		= 0x1c,
	LCD_set_mode_8bit_2r 		= 0x38 ,
	LCD_set_cursor_r0 			= 0X80 ,
	 	 	 	 	 	 //set cursor to row 0 ,then set the position with "|"
	LCD_set_cursor_r1 			= 0xC0
						//set cursor to row 1 ,then set the position with "|"
};

void LCD_send_command( uint8_t command );

void LCD_initialize();

//row is in range (0:1)  .... pos is in range (0:15)
//if it is out of range ... it will print with current position
void LCD_set_Cursor( uint8_t row , uint8_t pos );

//display data on LCD
void LCD_display_char( uint8_t data );

void LCD_display_text( char *str , double delay  );

//dir : direction of shift ---> 0: left , 1: right
//num_shift : how many time you want to shift
// delay : the delay between every shift in ms
void LCD_shift_entire_display( uint8_t dir , uint8_t num_shift , double delay);

void LCD_clear();

#endif /* LCD_H_ */
