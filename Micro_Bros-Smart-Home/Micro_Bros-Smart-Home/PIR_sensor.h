/*
 * PIR_sensor.h
 *
 * Created: 4/25/2022 5:33:56 PM
 *  Author: Dell
 */ 


#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_
DDRA &= ~(1<<1); // define pin A1 as input
DDRD |= (1<<6) ; // define pin D6 as led output
void PIR_DETECT_MOTION ()
{
	if ( PINA &(1<<1))
	PORTD |=(1<<6);
	else
	PORTD &=~(1<<6);

}


#endif /* PIR_SENSOR_H_ */