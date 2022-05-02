/*
 * Micro_Bros-Smart-Home.c
 *
 * Created: 4/24/2022 2:37:59 AM
 * Author : Micro_Bros
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "KeyPad.h"
#include <string.h>
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

#define F_CPU 8000000UL

static unsigned char password[4]="0000";
static int curr_temp = 255; //just for help , 255 is init value
static int last_temp = 255; //just for help , 255 is init value

void Button_Led_initialize()
{	DDRD  |= (1<<0); //wrong password LED
	DDRD  |= (1<<6); //PIR LED
	DDRD  |= (1<<2); //KEYBAD interrupt
	DDRA  |= (1<<2); //right password LED
	MCUCR |= (1 << ISC01);
	GICR  |= (1 << INT0);
}

void enter_the_door()
{
	PORTD |=  (1<<2);
	PORTD &= ~(1<<2);
}

int main(void)
{
	//KeyPad_init();
	LCD_initialize();
	PIR_initialize();
	Temp_initialize();
	buzzer_initialize();
	Button_Led_initialize();
	sei();

	LCD_display_text("Welcome Home , ",0);
	_delay_ms(10);
	LCD_set_Cursor(1,0);
	LCD_display_text("Mr. abdelrhman",0);

	enter_the_door();
	_delay_ms(50);


	while (1)
	  	{
			PIR_DETECT_MOTION(); //led on if detect motion
			last_temp = curr_temp;
			curr_temp = Temp_GetInput();
			Temp_warning(curr_temp ,30);//led on if the curr_temp lager than 30
			if(last_temp == 255 || (curr_temp-last_temp) )
			{ //if it is first time to print or if the temp changes
				Temp_display(curr_temp);
			}
	  	}
 }

ISR(INT0_vect)
{
	_delay_ms(10);
	unsigned int  counter = 0;
	unsigned char entered_password[4]={' '};

	while( 1 )
	{
		LCD_clear();
		LCD_display_text("enter:",0);
		for(int i =0 ; i<4 ; i++)
		{
			entered_password[i]=Get_Key_pressed();
			LCD_display_char(entered_password[i]); //##change it to '*'
			_delay_ms(2);
		}

		if( (memcmp(entered_password, password, sizeof(entered_password)) != 0) )
		{
			counter++;
			PORTD|=(1<<0); 	//led on
			LCD_clear();
			LCD_display_text("Wrong password",0);
			LCD_set_Cursor(1,0);
			LCD_display_text("You have ",0);
			LCD_display_char( 3-counter+'0' );
			LCD_display_text(" left",0);
			_delay_ms(500);
			PORTD&=~(1<<0); //led off

			if(counter == 3)
			{
				LCD_clear();
				LCD_set_Cursor(1,3);
				LCD_display_text("a Thief !! ",0);
				LCD_set_Cursor(1,2);
				LCD_display_text("  go away !! ",0);
				buzzer_turn_on(1000); //time in ms
				counter = 0; //reset counter
				break;
			}
		}

		else
		{
			LCD_clear();
			PORTA  |=  (1<<2);	//led on
			opendoor();
			_delay_ms(500);
			PORTA  &= ~(1<<2);  //led off
			counter = 0;		//reset counter
			last_temp = 255;	//to print temp when return to main
			break;
		}
	}
}
