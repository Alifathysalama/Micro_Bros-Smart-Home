/*
 * PIR_sensor.h
 *
 * Created: 4/25/2022 5:33:56 PM
 *  Author: Dell
 */


#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

void PIR_initialize();

void PIR_DETECT_MOTION();

#endif /* PIR_SENSOR_H_ */
