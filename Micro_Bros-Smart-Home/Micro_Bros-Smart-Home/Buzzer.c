/*
 * Buzzer.c
 *
 *  Created on: May 4, 2022
 *      Author: abdelrhman
 */

#include "Buzzer.h"

void buzzer_initialize()
{
	DDRD |= (1<<4);
	PORTD &= ~(1<<4);
}

//function to turn on buzzer for a certain time
//time in ms
void buzzer_turn_on(double time)
{
	PORTD |= (1<<4);
	_delay_ms(time);
	PORTD &= ~(1<<4);
}
