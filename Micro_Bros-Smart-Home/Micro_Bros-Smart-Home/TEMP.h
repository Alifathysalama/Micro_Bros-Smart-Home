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

//  void temp_do(float celsius, char Temperature[])
//  {
//	  LCD_String_xy(1, 0, "Temperature");
//	  celsius = (ADC_Read(0) * 4.88);
//	  celsius = (celsius / 10.00);
//	  sprintf(Temperature, "%d%cC  ", (int)celsius, degree_sysmbol);/* convert integer value to ASCII string */
//	  LCD_String_xy(2, 0, Temperature);/* send string data for printing */
//	  _delay_ms(1000);
//	  memset(Temperature, 0, 10);
//  }

#endif