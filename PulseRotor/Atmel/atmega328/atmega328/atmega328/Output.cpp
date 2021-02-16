/* 
* Output.cpp
*
* Created: 16.02.2021 8:57:16
* Author: Paul
*/


#include "Output.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void Output::Init(char port, int pin, bool inv)
{
	_port = port;
	_pin = pin;
	_inv = inv;
	
	if (_inv){
		switch (_port){
			case 'B': PORTB |= (1<<(pin)); DDRB |= (1<<(pin)); break;
			case 'C': PORTC |= (1<<(pin)); DDRC |= (1<<(pin)); break;
			case 'D': PORTD |= (1<<(pin)); DDRD |= (1<<(pin)); break;
		}
		}else{
		switch (_port){
			case 'B': PORTB &= ~(1<<(pin)); DDRB |= (1<<(pin)); break;
			case 'C': PORTC &= ~(1<<(pin)); DDRC |= (1<<(pin)); break;
			case 'D': PORTD &= ~(1<<(pin)); DDRD |= (1<<(pin)); break;
		}
	}
	
}

void Output::Off(){
	cli();
	if (_inv){
		switch (_port){
			case 'B': PORTB |= (1<<(_pin)); break;
			case 'C': PORTC |= (1<<(_pin)); break;
			case 'D': PORTD |= (1<<(_pin)); break;
		}
		}else{
		switch (_port){
			case 'B': PORTB  &= ~(1<<(_pin)); break;
			case 'C': PORTC  &= ~(1<<(_pin)); break;
			case 'D': PORTD  &= ~(1<<(_pin)); break;
		}
	}
	status = false;
	sei();
}

void Output::On(){
	cli();
	if (!_inv){
		switch (_port){
			case 'B': PORTB |= (1<<(_pin)); break;
			case 'C': PORTC |= (1<<(_pin)); break;
			case 'D': PORTD |= (1<<(_pin)); break;
		}
		}else{
		switch (_port){
			case 'B': PORTB  &= ~(1<<(_pin)); break;
			case 'C': PORTC  &= ~(1<<(_pin)); break;
			case 'D': PORTD  &= ~(1<<(_pin)); break;
		}
	}
	status = true;
	sei();
}

void Output::Switch(){
	if(status){
		Off();
		}else{
		On();
	}
}