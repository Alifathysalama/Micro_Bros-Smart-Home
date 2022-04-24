/*created by karim
24/4/2022
4:32 PM
*/
#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "LCD_16x2_H_file.h"

#define degree_sysmbol 0xdf


void ADC_Init(){
	DDRA &=~(1<<0)	        /* Make ADC portA0 as input */
	DDRD |=(1<<1)           //make port D1 output
	ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX = 0x40;           /* Vref: Avcc, ADC channel: 0 */
}

int ADC_Read(char channel)
{
	ADMUX = 0x40 | (channel & 0x07);   /* set input channel to read */
	ADCSRA |= (1<<ADSC);               /* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));     /* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);               /* Clear interrupt flag */
	_delay_ms(1);                      /* Wait a little bit */
	return ADCW;                       /* Return ADC word */
}