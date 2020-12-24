/* 
* Rotor.cpp
*
* Created: 10.12.2020 10:52:53
* Author: Paul
*/


#include "Rotor.h"
#include "delay.h"
#include <avr/interrupt.h>

const int AH = PB0;
const int AL = PB1;
const int BH = PB2;
const int BL = PB3;
const int CH = PB4;
const int CL = PB5;



void Rotor::Init(){
	workfrequency = 50;
	minfrequency = 1;
	maxfrequency = 150;
	minStartStopTime = 100;
	maxStartStopTime = 30000;
	SetFrequency(workfrequency);
	StaringTime =1000;
	StopingTime =1000;
	StaringTiming = 1;
	phasa=1;
}

void Rotor::SetFrequency(int freq){
	frequency = freq; // 8.000.000/256/6 = 5208 Ãö 
	int OCR_dev;
	OCR_dev = 5208/frequency;
	OCR1A = OCR_dev;
	
}

void Rotor::Activity(){
	
	if (Starting&&Stoping){
		Starting=false;
	}
	
	if (Reversing&&!Started){
		if (!Reverse){
			 Reverse = true;
		}else{
			Reverse = false;
		}		
		Reversing = false;
	}
	
	if (Reversing&&Started){
		Stoping = true;
	}
	
	if (Starting){
		_delay_us(750);
		StaringTiming++;	
		frequency = (StaringTiming*(workfrequency-minfrequency))/StaringTime + minfrequency;			
		if (frequency == 0){frequency = minfrequency;}
	
		if (StaringTiming>StaringTime){
			StaringTiming = 1;
			Started = true;
			Starting =false;
		}
	}

	if (Stoping){
		_delay_us(750);
		StaringTiming++;
		frequency = workfrequency - ((StaringTiming*(workfrequency-minfrequency))/StopingTime);
		if (frequency == 0){frequency = minfrequency;}
		
		if (StaringTiming>StopingTime){
			StaringTiming = 1;
			Started = false;
			Stoping = false;
			if(Reversing){ _delay_ms(500); Starting=true;}
		}
	}	
	

}

void Rotor::FrequncyUp(int up){
	workfrequency=workfrequency+up;
	if(workfrequency<minfrequency){workfrequency=minfrequency;}
	if(workfrequency>maxfrequency){workfrequency=maxfrequency;}
	frequency = workfrequency;
};

void Rotor::FrequencyDown(int down){
	if(workfrequency>down){workfrequency=workfrequency-down;}else{workfrequency=minfrequency;}
	frequency=workfrequency;
};

void Rotor::StartimeUp(int TimeUp){
	StaringTime = StaringTime + TimeUp;
	if (StaringTime > maxStartStopTime){ StaringTime = maxStartStopTime;}
}

void Rotor::StartimeDown(int TimeDown){
	if(StaringTime>TimeDown){StaringTime = StaringTime - TimeDown;
	}else{ StaringTime = minStartStopTime;}
}


void Rotor::StoptimeUp(int TimeUp){
	StopingTime = StopingTime + TimeUp;
	if (StopingTime > maxStartStopTime){ StopingTime = maxStartStopTime;}
}

void Rotor::StoptimeDown(int TimeDown){
	if(StopingTime>TimeDown){StopingTime = StopingTime - TimeDown;
	}else{ StopingTime = minStartStopTime;}
}


bool Rotor::RotorStopped(){
	if(Started||Starting||Stoping){
		return false;
	}else{
		return true;
	}
}

void Rotor::Move(){
	if (Started||Starting){
		
		if (!Reverse){
			MoveForvard();
			}else{
			MoveBack();
		}
		
		}else{
		PORTB &= ~(1<<AH);
		PORTB &= ~(1<<AL);
		PORTB &= ~(1<<BH);
		PORTB &= ~(1<<BL);
		PORTB &= ~(1<<CH);
		PORTB &= ~(1<<CL);
		phasa=1;
	}	
}

void Rotor::MoveForvard(){
	switch (phasa){
		case 1: PORTB &= ~(1<<CH);PORTB |=(1<<BH);break;
		case 2: PORTB &= ~(1<<AL);PORTB |=(1<<CL);break;
		case 3: PORTB &= ~(1<<BH);PORTB |=(1<<AH);break;
		case 4: PORTB &= ~(1<<CL);PORTB |=(1<<BL);break;
		case 5: PORTB &= ~(1<<AH);PORTB |= (1<<CH);break;
		case 6: PORTB &= ~(1<<BL);PORTB |= (1<<AL);break;
	}
	phasa++;
	if (phasa>6){phasa=1;}
}

void Rotor::MoveBack(){
	switch (phasa){
		case 6: PORTB |=(1<<CH);PORTB &= ~(1<<BH);break;
		case 5: PORTB |=(1<<AL);PORTB &= ~(1<<CL);break;
		case 4: PORTB |=(1<<BH);PORTB &= ~(1<<AH);break;
		case 3: PORTB |=(1<<CL);PORTB &= ~(1<<BL);break;
		case 2: PORTB |=(1<<AH);PORTB &= ~(1<<CH);break;
		case 1: PORTB |=(1<<BL);PORTB &= ~(1<<AL);break;
	}
	phasa++;
	if (phasa>6){phasa=1;}
}

void Rotor::MoveTest(){
	switch (phasa){
		case 1: PORTB &= ~(1<<CH);PORTB |=(1<<BH);break;
		case 2: PORTB &= ~(1<<AL);PORTB |=(1<<CL);break;
		case 3: PORTB &= ~(1<<BH);PORTB |=(1<<AH);break;
		case 4: PORTB &= ~(1<<CL);PORTB |=(1<<BL);break;
		case 5: PORTB &= ~(1<<AH);PORTB |= (1<<CH);break;
		case 6: PORTB &= ~(1<<BL);PORTB |= (1<<AL);break;
	}
	phasa++;
	if (phasa>6){phasa=1;}	
	
}
