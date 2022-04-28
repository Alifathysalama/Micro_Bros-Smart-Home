/*
 * KeyPad.h
 *
 * Created: 4/24/2022 7:23:13 AM
 *  Author: Alloush
 */ 


#ifndef KeyPad_H_
#define KeyPad_H_
#define KEY_PRT 	PORTB
#define KEY_DDR		DDRB
#define KEY_PIN		PINB

void KeyPad_init(void) // function to set PORTB half of it as input and the other half as output to use keypad properly .
{
	KEY_DDR = 0x0F;
	KEY_PRT=0xFF; // to enable pull up resistor to take digital input.
}

char Get_Key_pressed(void) // the main function to get the character pressed on the keypad.
{
	//KEY_PRT|=(1<<KEY_PIN0);KEY_PRT&=~(1<<KEY_PIN1);KEY_PRT&=~(1<<KEY_PIN2);KEY_PRT&=~(1<<KEY_PIN3);
	KEY_PRT=0xF1; // equivalent to the above line ---> pin0 will be one and the other will be zero 
	_delay_ms(1);
	if((KEY_PIN & 0b00010000)) return '1';
	if((KEY_PIN & 0b00100000)) return '2';
	if((KEY_PIN & 0b01000000)) return '3';
	if((KEY_PIN & 0b10000000)) return 'A';
	//KEY_PRT&=~(1<<KEY_PIN0);KEY_PRT|=(1<<KEY_PIN1);KEY_PRT&=~(1<<KEY_PIN2);KEY_PRT&=~(1<<KEY_PIN3);
	KEY_PRT=0xF2;
	_delay_ms(1);
	if((KEY_PIN & 0b00010000)) return '4';
	if((KEY_PIN & 0b00100000)) return '5';
	if((KEY_PIN & 0b01000000)) return '6';
	if((KEY_PIN & 0b10000000)) return 'B';
	//KEY_PRT&=~(1<<KEY_PIN0);KEY_PRT&=~(1<<KEY_PIN1);KEY_PRT|=(1<<KEY_PIN2);KEY_PRT&=~(1<<KEY_PIN3);
	KEY_PRT=0xF4;
	_delay_ms(1);
	if((KEY_PIN & 0b00010000)) return '7';
	if((KEY_PIN & 0b00100000)) return '8';
	if((KEY_PIN & 0b01000000)) return '9';
	if((KEY_PIN & 0b10000000)) return 'C';
	//KEY_PRT&=~(1<<KEY_PIN0);KEY_PRT&=~(1<<KEY_PIN1);KEY_PRT&=~(1<<KEY_PIN2);KEY_PRT|=(1<<KEY_PIN3);
	KEY_PRT=0xF8;
	_delay_ms(1);
	if((KEY_PIN & 0b00010000)) return '*';
	if((KEY_PIN & 0b00100000)) return '0';
	if((KEY_PIN & 0b01000000)) return '#';
	if((KEY_PIN & 0b10000000)) return 'D';
	// if nothing was pressed then it will return N as a exiting character from any loop or if condition  
	return 'N'; 	
}
	#endif