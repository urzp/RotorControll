/*
 * atmega328.cpp
 *
 * Created: 13.02.2021 12:41:22
 * Author : Paul
 */ 

#define F_CPU 8000000UL //16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Input.h"
#include "Button.h"
#include "Output.h"
#include "Rotor.h"

Button ButtonStop;
Button ButtonStart;
Button ButtonReverse;
Button ButtonUp;
Button ButtonDown;
Button ButtonReset;

Output GreenLed;
Output RedLed;
Output BlueLed;
Output Power;

Input Protect;

Rotor Rotor;

ISR (TIMER1_COMPA_vect)
{
	Rotor.tik();
	
}

void Init(){
	
	ButtonReset.Init('C',0);
	ButtonStop.Init('C',1);
	ButtonStart.Init('C',2);
	ButtonReverse.Init('C',3);
	ButtonUp.Init('C',4);
	ButtonDown.Init('C',5);
	
	GreenLed.Init('B',5, true);
	RedLed.Init('B',4, true);
	BlueLed.Init('B',6,true);
	
	Protect.Init('D', 1);
	Power.Init('D',0, false);
	
	Rotor.Init();
	
		
}

int main(void)
{
	Init();
	
    while (1) 
    {
		Rotor.SetFrequency(Rotor.frequency);
		
    }
}

