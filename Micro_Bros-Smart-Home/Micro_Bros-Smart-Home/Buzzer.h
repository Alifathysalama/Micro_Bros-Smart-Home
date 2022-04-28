/*
 * Buzzer.h
 *
 *  Created on: Apr 28, 2022
 *      Author: abdelrhman
 */

#ifndef BUZZER_H_
#define BUZZER_H_

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

#endif /* BUZZER_H_ */
