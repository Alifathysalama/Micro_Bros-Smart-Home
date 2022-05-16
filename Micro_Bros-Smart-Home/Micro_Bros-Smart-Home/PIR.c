/*
 * PIR.c
 *
 *  Created on: May 4, 2022
 *      Author: abdelrhman
 */

#include "PIR.h"

void PIR_initialize()
{
	DDRA &= ~(1<<1); // define pin A1 as input
	DDRD |= (1<<6) ; // define pin D6 as led output
}

void PIR_DETECT_MOTION()
{
	if ( PINA & (1<<1) )
	PORTD |= (1<<6); //PIR led on
	else
	PORTD &=~ (1<<6); //PIR led off
}
