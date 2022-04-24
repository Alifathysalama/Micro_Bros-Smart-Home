/*created by karim
24/4/2022
4:32 PM
*/

#ifndef temp_H_
#define temp_H_
#define degree_sysmbol 0xdf

   DDRA &=~(1<<0)	        /* Make ADC portA0 as input */
  DDRD |=(1<<1)           //make port D1 output
  ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
  ADMUX = 0x40;           /* Vref: Avcc, ADC channel: 0 */


#endif