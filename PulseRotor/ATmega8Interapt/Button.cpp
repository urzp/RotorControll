/* 
* Button.cpp
*
* Created: 10.12.2020 7:47:33
* Author: Paul
*/


#include "Button.h"
#include <avr/io.h>


void Button::Init(char port, int pin)
{
	_port = port;
	_pin = pin;
	debounce = 10;
	switch (_port){
		case 'B': DDRB &= ~(1<<(pin)); PORTB |= (1<<(pin)); break;
		case 'C': DDRC &= ~(1<<(pin)); PORTC |= (1<<(pin)); break;
		case 'D': DDRD &= ~(1<<(pin)); PORTD |= (1<<(pin)); break;
	}
	
}

void Button::Scan(){
	bool read_pin = ReadPin();
	
	if (read_pin){
		countDebounce++;
		if (countDebounce>debounce){
			countDebounce = debounce;
			getpressed = true;
		}
	}else{
		countDebounce = 0;
		if (getpressed){pressed=true;}
		getpressed = false;	
	}
	

}

bool Button::PressRead(){
	if (pressed){
		pressed =false;
		return true;
	}else{
		return false;
	}
}

bool Button::ReadPin(){
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
