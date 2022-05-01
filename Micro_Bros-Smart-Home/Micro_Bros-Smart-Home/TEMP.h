/*created by karim
24/4/2022
4:32 PM
*/

#ifndef temp_H_
#define temp_H_
#define degree_sysmbol 0xdf
void Temp_initialize()
{
	DDRA &= ~(1 << 0);	        /* Make ADC portA0 as input */
	DDRD |= (1 << 1);           //make port D1 output
	ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX = 0x40;          /* Vref: Avcc, ADC channel: 0 */
}

  int Temp_Read(char channel)
  {
	  ADMUX = 0x40 | (channel & 0x07);   /* set input channel to read */
	  ADCSRA |= (1 << ADSC);               /* Start ADC conversion */
	  while (!(ADCSRA & (1 << ADIF)));     /* Wait until end of conversion by polling ADC interrupt flag */
	  ADCSRA |= (1 << ADIF);               /* Clear interrupt flag */
	  _delay_ms(1);                      /* Wait a little bit */
	  return ADCW;                       /* Return ADC word */
  }

  int Temp_GetInput() //return integer number for temp
  {
	int16_t celisius;
	_delay_ms(100);
	celisius = (Temp_Read(0)*4.88);
	celisius=(celisius/10.00);
	return (int)celisius;
  }

  void Temp_display(int temp )
  {
	char tempe_to_print[10];
	sprintf(tempe_to_print,"%d%cC  ", (int)temp, degree_sysmbol);
	LCD_clear();
	LCD_set_Cursor(0,0);
	LCD_display_text("temperature is :",0);
	LCD_set_Cursor(1,0);
	LCD_display_text(tempe_to_print,0);
	//memset(temperature,0,10);
  }

  void Temp_warning(int curr_temp , int max_temp)
  {
	  if(curr_temp >= max_temp )
	  {
		  PORTD |=(1<<1); //led on
	  }
	  else if ( PIND & (1<<1) )
	  {
		  PORTD &= ~(1<<1); //led off
	  }
  }

#endif/* temp_H*/
