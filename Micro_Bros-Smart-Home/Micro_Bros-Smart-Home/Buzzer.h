/*
 * Buzzer.h
 *
 *  Created on: Apr 28, 2022
 *      Author: abdelrhman
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

void buzzer_initialize();

//function to turn on buzzer for a certain time
//time in ms
void buzzer_turn_on(double time);

#endif /* BUZZER_H_ */
