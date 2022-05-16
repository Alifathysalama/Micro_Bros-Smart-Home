/*created by karim
24/4/2022
4:32 PM
*/

#ifndef temp_H_
#define temp_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"

#define degree_sysmbol 0xdf
void Temp_initialize();

int Temp_Read(char channel);

int Temp_GetInput(); //return integer number for temp

void Temp_display(int temp );

void Temp_warning(int curr_temp , int max_temp);

#endif/* temp_H*/
