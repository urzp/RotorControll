/* 
* Rotor.cpp
*
* Created: 16.02.2021 13:04:34
* Author: Paul
*/


#include "Rotor.h"
#include "delay.h"
#include <avr/interrupt.h>

#define C_PWM   OCR2A

const int AH = PB0;
const int AL = PB1;
const int BH = PB2;
const int BL = PC2;
const int CH = PB4;
const int CL = PB5;



void pin_init() {
	DDRB |= (1<<A_PD) | (1<<B_PD) | (1<<C_PD) | (1<<A_Derect) | (1<<B_Derect) | (1<<C_Derect);
	DDRD |= (1<<A_PD) | (1<<B_PD) | (1<<0);
	PORTB |= (1<<A_Derect) | (1<<B_Derect) | (1<<C_Derect);
}

void timer0_init(){
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |=  (1 << CS00);
	OCR0A = 0;
	OCR0B = 0;
}

void timer1_init() {
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK1 |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	TCCR1B |= (1<<CS10);//установим делитель.
	sei();
}

void timer2_init() {
	TCCR2A |= (1 << COM2A1)  | (1 << WGM21) | (1 << WGM20);
	TCCR2B |=  (1 << CS20);
	TCNT2 = 0x00;
	OCR2A = 0;
}



void Rotor::Init(){
	pin_init();
	timer0_init();
	timer1_init();
	timer2_init();
	workfrequency = 70;
	minfrequency = 1;
	maxfrequency = 150;
	minStartStopTime = 100;
	maxStartStopTime = 30000;
	SetFrequency(workfrequency);
	StaringTime =200;
	StopingTime =200;
	StaringTiming = 1;
	phasa=1;
	WorkCurrent = 30;	
}


void Rotor::SetFrequency(int freq){
	frequency = freq; // 8.000.000/8/30 = 5208 Гц
	int OCR_dev;
	//if(!LowFreq){OCR_dev = 5208/frequency;}else{OCR_dev = 1302/frequency;}
	OCR_dev = 33333/frequency;
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
			Adjust = false;
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



void Rotor::set_A_PWM(int phasa){
	
	A_PWM = SinTable[phasa];
	
	if (phasa >= 0 && phasa < 14){
		A_DerectPort |= (1<<A_Derect);
	}
	if (phasa >= 14 && phasa < 30){
		A_DerectPort &= ~(1<<A_Derect);
	}
}

void Rotor::set_B_PWM(int phasa){
	
	B_PWM = SinTable[phasa];
	
	if (phasa >= 0 && phasa < 14){
		B_DerectPort |= (1<<B_Derect);
	}
	if (phasa >= 14 && phasa < 30){
		B_DerectPort &= ~(1<<B_Derect);
	}
}

void Rotor::set_C_PWM(int phasa){

	C_PWM = SinTable[phasa];
	
	if (phasa >= 0 && phasa < 14){
		C_DerectPort |= (1<<C_Derect);
	}
	if (phasa >= 14 && phasa < 30){
		C_DerectPort &= ~(1<<C_Derect);
	}
}

void Rotor::tik(){
	phasa_a++;
	phasa_b++;
	phasa_c++;
	
	if (phasa_a>29){phasa_a=0;}
	if (phasa_b>29){phasa_b=0;}
	if (phasa_c>29){phasa_c=0;}
	
	set_A_PWM(phasa_a);
	set_B_PWM(phasa_b);
	set_C_PWM(phasa_c);
	
	if (phasa_a==0){PORTD |= (1<<0);Timing = Timing + 10 * frequency/2 ;}
	if (phasa_a==15){PORTD  &= ~(1<<0);} 
}



void Rotor::Move(){	
	if (Started||Starting){	
		if (!Reverse){
			MoveForvard();
		}else{
			MoveBack();
		}	
	}else{
		PortsOff();
		phasa=1;
		NPMW=0;
	}
}

			void Rotor::PortsOff(){
				PORTB &= ~(1<<AH);
				PORTB &= ~(1<<AL);
				PORTB &= ~(1<<BH);
				PORTC &= ~(1<<BL);
				PORTB &= ~(1<<CH);
				PORTB &= ~(1<<CL);
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
