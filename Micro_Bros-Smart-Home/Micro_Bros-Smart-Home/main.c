/*
 * Micro_Bros-Smart-Home.c
 *
 * Created: 4/24/2022 2:37:59 AM
 * Author : Micro_Bros
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "KeyPad.h" // KeyPad has only one function Get_Key() that takes no i/p and return the pressed key 
#include "open_door.h" 
#include "temp.h"   //temp.h has two functions ADC_init() & ADC_Read()


int main(void)
{
  	//there is no need for making fun. in this part of pir motion sensor as it will be as interrupt so i didn't do header file..
  	DDRA= ~(1<<1); // define pin A1 as input
  	DDRD |= (1<<6) ; // define pin D6 as led output
  	while (1)
  	{
	  	if ( PINA &(1<<1))
	  	PORTD |=(1<<6);
	  	else
	  	PORTD &=~(1<<6);
	  	
	  	
  	}
 }

