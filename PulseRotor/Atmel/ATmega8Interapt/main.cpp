/*
 * ATmega8Interapt.cpp
 *
 * Created: 22.10.2020 17:03:02
 * Author : Pavel
 */ 



#include <avr/io.h>
#include <avr/interrupt.h>



#include "delay.h"
#include "Input.h"
#include "Button.h"
#include "Output.h"
#include "Rotor.h"



const int VT1 = PB0;
const int VT2 = PB1;
const int VT3 = PB2;
const int VT4 = PB3;
const int VT5 = PB4;
const int VT6 = PB5;

const int CLK = PC3;
const int DataSPI = PC4;
const int LOAD = PC5;

const int timeCTRIN = 1;
const int timeCTR = 6;
char dg = 8;

volatile int Phasa;
int TimePhasa = 1680;
volatile bool go ;
bool  started, pause, button;
bool move;
int debounse;

int IntConter=1;
bool MovingPulse[51];
bool Mode, ModeFeq;
int  ModeFeqCount;

int countpulse;
int TruePulse;
int freq=1;

Input Protect;
Input PowerReady;

Button ButtonStop;
Button ButtonStart;
Button ButtonReverse;
Button ButtonUp;
Button ButtonDown;

Output Power;
Output GreenLed;
Output RedLed;
Output BlueLed;

Rotor Rotor;


#include  "SPI.h"
#include  "Display.h"

void SendInfDisplay(){
	if(!Rotor.RotorStopped()) {
		LED_DisplaySend(Rotor.frequency);
		}else{
		if(ModeFeq){
			LED_DisplaySend(Rotor.frequency);
			}else{
			LED_DisplaySend(0);
		}
			
	}
}


ISR (TIMER1_COMPA_vect)
{
	if (Rotor.Started||Rotor.Starting){
		
		if (!Rotor.Reverse){
			switch (Phasa){
				case 1: PORTB &= ~(1<<VT5);PORTB |=(1<<VT3);break;
				case 2: PORTB &= ~(1<<VT2);PORTB |=(1<<VT6);break;
				case 3: PORTB &= ~(1<<VT3);PORTB |=(1<<VT1);break;
				case 4: PORTB &= ~(1<<VT6);PORTB |=(1<<VT4);break;
				case 5: PORTB &= ~(1<<VT1);PORTB |= (1<<VT5);break;
				case 6: PORTB &= ~(1<<VT4);PORTB |= (1<<VT2);break;
			}
		}else{
			switch (Phasa){
				case 6: PORTB |=(1<<VT5);PORTB &= ~(1<<VT3);break;
				case 5: PORTB |=(1<<VT2);PORTB &= ~(1<<VT6);break;
				case 4: PORTB |=(1<<VT3);PORTB &= ~(1<<VT1);break;
				case 3: PORTB |=(1<<VT6);PORTB &= ~(1<<VT4);break;
				case 2: PORTB |=(1<<VT1);PORTB &= ~(1<<VT5);break;
				case 1: PORTB |=(1<<VT4);PORTB &= ~(1<<VT2);break;
			}	
		}

		Phasa++;
		
		if (Phasa>6){
			Phasa=1;
		}
		
	}else{
		PORTB &= ~(1<<VT1);
		PORTB &= ~(1<<VT2);
		PORTB &= ~(1<<VT3);
		PORTB &= ~(1<<VT4);
		PORTB &= ~(1<<VT5);
		PORTB &= ~(1<<VT6);
		Phasa=1;
	}
	Rotor.SetFrequency(Rotor.frequency);
	SendInfDisplay();
}





void initTimer(){
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	TCCR1B |= (1<<CS12);//установим делитель.
	sei();
}



void Init(){

	
	Protect.Init('C', 0);
	PowerReady.Init('C',1);
	
	ButtonStop.Init('D',0);
	ButtonStart.Init('D',1);
	ButtonReverse.Init('D',2);
	ButtonUp.Init('D',4);
	ButtonDown.Init('D',3);
	
	Power.Init('C',2, false);
	GreenLed.Init('B',6, true);
	RedLed.Init('B',7, true);
	BlueLed.Init('D',5,true);
	
	Rotor.Init();
	
	DDRB |= (1<<(PB0));
	DDRB |= (1<<(PB1));
	DDRB |= (1<<(PB2));
	DDRB |= (1<<(PB3));
	DDRB |= (1<<(PB4));
	DDRB |= (1<<(PB5));
	
	DDRD |= (1<<(PD7));
	
	SPI_init();
	LED_Display_Init();
	
	initTimer();
	_delay_ms(100);
	Power.On();
}

void ReadInputs(){
	ButtonStop.Scan();
	ButtonStart.Scan();
	ButtonReverse.Scan();
	ButtonUp.Scan();
	ButtonDown.Scan();
};

#include "RotorControll.h"
#include "ModeControll.h"
#include "ProtectControll.h"
#include "LedControll.h"






int main (void) { //главная цикл программы
	Init();

	
	while(1) {
		ReadInputs();
		
		StartControll();
		StopControll();
		ReverseControll();
		SpeedControll();
		
		ModeStartTime();
		ModeStopTime();
		
		ProtectControll();
		
		Rotor.Activity();

		LedControll();
		
		DidplayFeqSet();

		
		
	}
			
}