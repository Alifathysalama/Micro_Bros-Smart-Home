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


void LCD_send_command( uint8_t command )
{
	PORTA &= ~(1<<3);	//set RS to 0 to send command
	PORTA &= ~(1<<4); 	//set RW t0 0 to write
	_delay_ms(20);
	PORTD |= (1<<7);	//enable LCD by set E
	_delay_ms(20);
	PORTC = command;	 //write the command to port
	_delay_ms(20);
	PORTD &= ~(1<<7);	//disable LCD by reset E
	_delay_ms(10);
}


void LCD_initialize()
{
	DDRC = 0xff; 						//make all port as output
	DDRA |= (1<<3)|(1<<4);						//make RS,RW as output
	DDRD |= (1<<7);						//make E as output
	LCD_send_command(LCD_set_mode_8bit_2r);	//set the mode to 8 bit , 2 row
	LCD_send_command(LCD_display_on_cursor_off);
	LCD_send_command(LCD_auto_increment_cursor);
	LCD_send_command(LCD_clear_screen);
	LCD_send_command(LCD_set_cursor_r0 | 0 ); //set Cursor to home position
}

//row is in range (0:1)  .... pos is in range (0:15)
//if it is out of range ... it will print with current position
void LCD_set_Cursor( uint8_t row , uint8_t pos )
{
	if (row == 0 && pos<16)
		LCD_send_command((pos & 0x0F) | LCD_set_cursor_r0);
	else if (row == 1 && pos<16)
		LCD_send_command((pos & 0x0F) | LCD_set_cursor_r1);
}

//display data on LCD
void LCD_display_char( uint8_t data )
{
	PORTA |=  (1<<3); 	//set RS to 1 to send data
	PORTD &= ~(1<<3);	//set RW t0 0 to write
	_delay_ms(5);
	PORTD |= (1<<7);	//enable LCD by set E
	_delay_ms(5);
	PORTC = data;		//write data to port (set data)
	_delay_ms(5);
	PORTD &= ~(1<<7);	//disable LCD by reset E
	_delay_ms(5);
}

void LCD_display_text( char *str , double delay  )
{
	uint8_t i;
	for(i = 0 ; str[i] ; i++ )
	{
		LCD_display_char( str[i] );
		_delay_ms(delay);
	}
}

//dir : direction of shift ---> 0: left , 1: right
//num_shift : how many time you want to shift
// delay : the delay between every shift in ms
void LCD_shift_entire_display( uint8_t dir , uint8_t num_shift , double delay)
{
	uint8_t i;
	for(i = 0 ; i< num_shift ; i++)
	{
		if(dir == 0)
		{
			LCD_send_command(LCD_shift_entire_left);/* shift entire display left */
			_delay_ms(delay);
		}
		else
		{
			LCD_send_command(LCD_shift_entire_right);/* shift entire display right */
			_delay_ms(delay);
		}
	}
}

void LCD_clear()
{
	LCD_send_command(LCD_clear_screen);
	LCD_send_command(LCD_set_cursor_r0 | 0 ); //set Cursor to home postion
}

#endif /* LCD_H_ */
