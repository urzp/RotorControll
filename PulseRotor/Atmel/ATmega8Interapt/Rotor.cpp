/* 
* Rotor.cpp
*
* Created: 10.12.2020 10:52:53
* Author: Paul
*/


#include "Rotor.h"
#include "delay.h"
#include <avr/interrupt.h>




void Rotor::Init(){
	workfrequency = 50;
	minfrequency = 40;
	maxfrequency = 200;
	minStartStopTime = 100;
	maxStartStopTime = 30000;
	SetFrequency(workfrequency);
	StaringTime =1000;
	StopingTime =1000;
	StaringTiming = 1;
}

void Rotor::SetFrequency(int freq){
	frequency = freq; // 8.000.000/256/6 = 5.208 Ãö  
	int OCR_dev;
	OCR_dev =5208/frequency;
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

void Rotor::FrequncyUp(){
	workfrequency++;
	if(workfrequency<minfrequency){workfrequency=minfrequency;}
	if(workfrequency>maxfrequency){workfrequency=maxfrequency;}
	frequency = workfrequency;
};

void Rotor::FrequencyDown(){
	workfrequency--;
	if(workfrequency<minfrequency){workfrequency=minfrequency;}
	if(workfrequency>maxfrequency){workfrequency=maxfrequency;}
	frequency=workfrequency;
};

void Rotor::StartimeUp(int TimeUp){
	StaringTime = StaringTime + TimeUp;
	if (StaringTime > maxStartStopTime){ StaringTime = maxStartStopTime;}
}

void Rotor::StartimeDown(int TimeDown){
	StaringTime = StaringTime - TimeDown;
	if (StaringTime ==  0){ StaringTime = minStartStopTime;}
}


void Rotor::StoptimeUp(int TimeUp){
	StopingTime = StopingTime + TimeUp;
	if (StopingTime > maxStartStopTime){ StopingTime = maxStartStopTime;}
}

void Rotor::StoptimeDown(int TimeDown){
	StopingTime = StopingTime - TimeDown;
	if (StopingTime ==  0){ StopingTime = minStartStopTime;}
}


bool Rotor::RotorStopped(){
	if(Started||Starting||Stoping){
		return false;
	}else{
		return true;
	}
}