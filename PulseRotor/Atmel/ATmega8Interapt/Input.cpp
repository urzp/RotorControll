/* 
* Input.cpp
*
* Created: 14.12.2020 15:14:15
* Author: Paul
*/


#include "Input.h"
#include <avr/io.h>

void Input::Init(char port, int pin)
{
	_port = port;
	_pin = pin;
	switch (_port){
		case 'B': DDRB &= ~(1<<(pin)); PORTB |= (1<<(pin)); break;
		case 'C': DDRC &= ~(1<<(pin)); PORTC |= (1<<(pin)); break;
		case 'D': DDRD &= ~(1<<(pin)); PORTD |= (1<<(pin)); break;
	}
	
}

bool Input::Read(){
	bool read_pin;
	switch (_port){
		case 'B': read_pin = ((1 << _pin) & PINB); break;
		case 'C': read_pin = ((1 << _pin) & PINC); break;
		case 'D': read_pin = ((1 << _pin) & PIND); break;
		default: return false;
	}
	if (!read_pin){
		return true;
		}else{return false;}
	}