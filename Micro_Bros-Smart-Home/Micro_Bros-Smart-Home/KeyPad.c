/*
 * KeyPad.c
 *
 *  Created on: May 4, 2022
 *      Author: abdelrhman
 */

#include "KeyPad.h"

uint8_t Get_Key_pressed(void) // the main function to get the character pressed on the keypad.
{
	KEY_DDR = 0xF0;           /* set port direction as input-output */
	while (1)
	{
		KEY_PRT = 0xFF;
		do
		{
			KEY_PRT &= 0x0F;      		/* mask PORT for column read only */
			asm("NOP");					//is an assembly instruction that does nothing
			colloc = (KEY_PIN & 0x0F); 	/* read status of column */
		} while (colloc != 0x0F);

		do
		{
			do
			{
				_delay_ms(20);             	/* 20ms key debounce time */
				colloc = (KEY_PIN & 0x0F); 	/* read status of column */
			} while (colloc == 0x0F);       /* check for any key press */

			_delay_ms(40);	            	/* 20ms key debounce time */
			colloc = (KEY_PIN & 0x0F);
		} while (colloc == 0x0F);

		/* now check for rows */
		KEY_PRT = 0xEF;            			/* check for pressed key in 1st row */
		asm("NOP");							//is an assembly instruction that does nothing
		colloc = (KEY_PIN & 0x0F);
		if (colloc != 0x0F)
		{
			rowloc = 0;
			break;
		}

		KEY_PRT = 0xDF;						/* check for pressed key in 2nd row */
		asm("NOP");							//is an assembly instruction that does nothing
		colloc = (KEY_PIN & 0x0F);
		if (colloc != 0x0F)
		{
			rowloc = 1;
			break;
		}

		KEY_PRT = 0xBF;						/* check for pressed key in 3rd row */
		asm("NOP");							//is an assembly instruction that does nothing
		colloc = (KEY_PIN & 0x0F);
		if (colloc != 0x0F)
		{
			rowloc = 2;
			break;
		}

		KEY_PRT = 0x7F;						/* check for pressed key in 4th row */
		asm("NOP");							//is an assembly instruction that does nothing
		colloc = (KEY_PIN & 0x0F);
		if (colloc != 0x0F)
		{
			rowloc = 3;
			break;
		}
	}

	if (colloc == 0x0E)
		return(keypad[rowloc][0]);
	else if (colloc == 0x0D)
		return(keypad[rowloc][1]);
	else if (colloc == 0x0B)
		return(keypad[rowloc][2]);
	else
		return(keypad[rowloc][3]);
}

//uint8_t get_temp()
//{ 	uint8_t x ;
//	uint8_t tens , ones ;
//	LCD_clear();
//	LCD_display_text("Enter Temperature",700);
//	LCD_set_Cursor(1,0);
//	tens=Get_Key_Pressed();
//	_delay_ms(300);
//	LCD_display_char(tens);
//	ones=Get_Key_Pressed();
//	_delay_ms(300);
//	LCD_display_char(ones);
//	return tens*10 + ones ;
//	}
