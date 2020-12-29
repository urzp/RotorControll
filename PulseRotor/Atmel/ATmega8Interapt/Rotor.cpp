/* 
* Rotor.cpp
*
* Created: 10.12.2020 10:52:53
* Author: Paul
*/


#include "Rotor.h"
#include "delay.h"
#include <avr/interrupt.h>

#define C_PWM   OCR2

const int AH = PB0;
const int AL = PB1;
const int BH = PB2;
const int BL = PC2;
const int CH = PB4;
const int CL = PB5;



void Rotor::Init(){
	workfrequency = 40;
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
	
	if (frequency>=1&&frequency<5){C_PWM = 90;}
	if (frequency>=5&&frequency<10){C_PWM = 100;}
	if (frequency>=10&&frequency<20){C_PWM = 130;}
	if (frequency>=20&&frequency<30){C_PWM = 150;}
	if (frequency>=30&&frequency<40){C_PWM = 200;}
	if (frequency>=40&&frequency<50){C_PWM = 200;}
	if (frequency>=50){C_PWM = 255;}
	
	//if (frequency>=1&&frequency<5){C_PWM = 40;}
	//if (frequency>=5&&frequency<10){C_PWM = 50;}
	//if (frequency>=10&&frequency<20){C_PWM = 70;}	
	//if (frequency>=20&&frequency<30){C_PWM = 90;}
	//if (frequency>=30&&frequency<40){C_PWM = 110;}	
	//if (frequency>=40&&frequency<50){C_PWM = 130;}
	//if (frequency>=50){C_PWM = 255;}	

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
			if(Reversing){ _delay_ms(150); Starting=true;}
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
	if(workfrequency-down>minfrequency&&workfrequency>down){workfrequency=workfrequency-down;}else{workfrequency=minfrequency;}
	
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
		PORTC &= ~(1<<BL);
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
		case 4: PORTB &= ~(1<<CL);PORTC |=(1<<BL);break;
		case 5: PORTB &= ~(1<<AH);PORTB |= (1<<CH);break;
		case 6: PORTC &= ~(1<<BL);PORTB |= (1<<AL);break;
	}
	phasa++;
	if (phasa>6){phasa=1;}
}

void Rotor::MoveBack(){
	switch (phasa){
		case 6: PORTB |=(1<<CH);PORTB &= ~(1<<BH);break;
		case 5: PORTB |=(1<<AL);PORTB &= ~(1<<CL);break;
		case 4: PORTB |=(1<<BH);PORTB &= ~(1<<AH);break;
		case 3: PORTB |=(1<<CL);PORTC &= ~(1<<BL);break;
		case 2: PORTB |=(1<<AH);PORTB &= ~(1<<CH);break;
		case 1: PORTC |=(1<<BL);PORTB &= ~(1<<AL);break;
	}
	phasa++;
	if (phasa>6){phasa=1;}
}



		//case 1: PORTB &= ~(1<<CH);break;
		//case 2: break;
		//case 3: PORTB |=(1<<BH);break;
		//case 4: PORTB &= ~(1<<AL);PORTB |=(1<<CL);break;
		//case 5: PORTB &= ~(1<<BH);break;
		//case 6: break;
		//case 7: PORTB |=(1<<AH);break;
		//case 8: PORTB &= ~(1<<CL);PORTB |=(1<<BL);break;
		//case 9: PORTB &= ~(1<<AH);
		//case 10: break;
		//case 11: PORTB |= (1<<CH);break;
		//case 12: PORTB &= ~(1<<BL);PORTB |= (1<<AL);break;




		//case 1: PORTB &= ~(1<<CH);break;
		//case 2: break;
		//case 3: break;
		//case 4: PORTB &= ~(1<<AL);PORTB |=(1<<CL);PORTB |=(1<<BH);break;
		//case 5: PORTB &= ~(1<<BH);break;
		//case 6: break;
		//case 7: break;
		//case 8: PORTB &= ~(1<<CL);PORTB |=(1<<BL);PORTB |=(1<<AH);break;
		//case 9: PORTB &= ~(1<<AH);break;
		//case 10: break;
		//case 11: break;
		//case 12: PORTB &= ~(1<<BL);PORTB |= (1<<AL);PORTB |= (1<<CH);break;
		
				//case 1: PORTB &= ~(1<<CH); break;
				//case 2: break;
				//case 3: break;
				//case 4: break;
				//case 5: break;
				//case 6: PORTB |=(1<<BH);break;
				//case 7: PORTB &= ~(1<<AL);PORTB |=(1<<CL);break;
				//case 8: PORTB &= ~(1<<BH);break;
				//case 9: break;
				//case 10: break;
				//case 11: break;
				//case 12: break;
				//case 13: break;
				//case 14: PORTB |=(1<<AH);break;
				//case 15: PORTB &= ~(1<<CL);PORTB |=(1<<BL);break;
				//case 16: PORTB &= ~(1<<AH);break;
				//case 17: break;
				//case 18: break;
				//case 19: break;
				//case 20: break;
				//case 21: break;
				//case 22: PORTB |=(1<<CH);break;
				//case 23: PORTB &= ~(1<<BL);PORTB |=(1<<AL);break;
				//case 24: PORTB &= ~(1<<CH); break;