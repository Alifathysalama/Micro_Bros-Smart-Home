/*
 * Micro_Bros-Smart-Home.c
 *
 * Created: 4/24/2022 2:37:59 AM
 * Author : Micro_Bros
 */

#include "main.h"

static unsigned char password[4]="0000";
static int curr_temp = 255; //just for help , 255 is init value
static int last_temp = 255; //just for help , 255 is init value
//static unsigned char air_condition[2] = {' '};
uint8_t get_temp();
void Button_Led_initialize()
{	DDRD  |= (1<<0); //wrong password LED
	DDRD  |= (1<<6); //PIR LED
	DDRD  |= (1<<2); //KEYBAD interrupt
	DDRA  |= (1<<2); //right password LED
	MCUCR |= (1 << ISC01);
	GICR  |= (1 << INT0);
}

void enter_the_door()	//first time password enter
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
	uint8_t requierd_temp=28;

	LCD_display_text("Welcome Home , ",700);
	_delay_ms(200);
	LCD_set_Cursor(1,0);
	LCD_display_text("Mr. abdelrhman",700);

	enter_the_door(); //first time password enter
	_delay_ms(500);


	while (1)
	  	{
			PIR_DETECT_MOTION(); //led on if detect motion
			last_temp = curr_temp;
			curr_temp = Temp_GetInput();
//			if(Get_Key_Pressed()=='D')
//			{
//				requierd_temp=get_temp();
//				LCD_clear();
//			}
			Temp_warning(curr_temp ,(int)requierd_temp);//led on if the curr_temp lager than 30
			if(last_temp == 255 || (curr_temp-last_temp) )
			{ //if it is first time to print or if the temp changes
				Temp_display(curr_temp);
			}

	  	}
 }

ISR(INT0_vect)
{
	_delay_ms(500);
	unsigned int  counter = 0;
	unsigned char entered_password[4]={' '};

	while( 1 )
	{
		LCD_clear();
		LCD_display_text("enter password:",700);
		LCD_set_Cursor(1,0);
		for(int i =0 ; i<4 ; i++)
		{
			entered_password[i]=Get_Key_pressed();
			LCD_display_char(entered_password[i]); //##change it to '*'
			_delay_ms(500);
		}
		_delay_ms(500);
		if( (memcmp(entered_password, password, sizeof(entered_password)) != 0) )
		{
			counter++;
			PORTD|=(1<<0); 	//led on
			LCD_clear();
			LCD_display_text("Wrong password",700);
			LCD_set_Cursor(1,0);
			LCD_display_text("You have ",700);
			LCD_display_char( 3-counter+'0' );
			LCD_display_text(" left",700);
			_delay_ms(500);
			PORTD&=~(1<<0); //led off

			if(counter == 3)
			{
				LCD_clear();
				LCD_set_Cursor(1,3);
				LCD_display_text("a Thief !! ",700);
				LCD_set_Cursor(1,2);
				LCD_display_text("  go away !! ",700);
				buzzer_turn_on(10000); //time in ms
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

//uint8_t get_temp()
//{   uint8_t x = 0;
//	unsigned char tens , ones ;
//	LCD_clear();
//	LCD_display_text("Enter Temperature",700);
//	LCD_set_Cursor(1,0);
//	while(x<2)
//	{	if(x==0)
//		{ ones=Get_key_Pressed();
//			LCD_display_char(ones);
//			_delay_ms(300);
//		}
//	else if (x==1)
//	{
//		tens=Get_Key_Pressed();
//		LCD_display_char(ones);
//		_delay_ms(300);
//	}
//	x++;
//	}
//	//return tens*10 + ones ;
//}
