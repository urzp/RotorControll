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


void pin_init() {
	DDRB |= (1<<A_PD) | (1<<B_PD) | (1<<C_PD) | (1<<A_Derect) | (1<<B_Derect) | (1<<C_Derect);
	DDRD |= (1<<A_PD) | (1<<B_PD) | (1<<0);
	PORTB |= (1<<A_Derect) | (1<<B_Derect) | (1<<C_Derect);
}

void timer0_init(){
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
	TCCR0B |=  (1 << CS00);
	OCR0A = 0;
	OCR0B = 0;
}

void timer1_init() {
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK1 |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	TCCR1B |= (1<<CS10);//установим делитель. 1/8
	sei();
}

void timer2_init() {
	TCCR2A |= (1 << COM2A1);
	TCCR2B |=  (1 << CS20);
	TCNT2 = 0x00;
	OCR2A = 0;
}

void Rotor::PWM_On(){
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
}

void Rotor::PWM_Off(){
	TCCR0A &= ~ (1 << WGM01);
	TCCR0A &= ~ (1 << WGM00);
	TCCR2A &= ~ (1 << WGM21);
	TCCR2A &= ~ (1 << WGM20);
}

void Rotor::Init(){
	InitFreqTables();
	pin_init();
	timer0_init();
	timer1_init();
	timer2_init();
	workfrequency = 5;
	minfrequency = 1;
	maxfrequency = 150;
	minStartStopTime = 60;
	maxStartStopTime = 30000;
	SetFrequency(1);
	StaringTime =1000;
	StopingTime =1000;
	StaringTiming = 1;
	phasa=1;
	WorkCurrent = 30;	
}

void Rotor::InitFreqTables(){
	
	FrqTable[0]=65535;
	for(int i=2; i<=150; i++){
		FrqTable[i-1]=83333/i; //66666/ 16.000.000/8/30 = 66.666 Гц 
		FrqTableFast[i-1] = 166666 / i;
		if (i<50){		
			PerodTable[i-1]=41.66/i; //66666/2000=33.33  
		}else{			
			PerodTable[i-1]=83.33/i;
		}
	}
}

void Rotor::SetFrequency(int freq){
	frequency = freq; // 16.000.000/8/30 = 66.666 Гц   в одном минимальном прирывании 
	int OCR_dev;
	
	if (FastFreq){
		OCR1A = FrqTableFast[frequency-1];
		
	}else{
		OCR1A = FrqTable[frequency-1];
	}
	
	Period = PerodTable[frequency-1];

	

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
	
	if (Reversing&&Started&&!Stoping){
		BeginStop();
	}
	
	if (Starting){
		StaringTiming = Timing;
		frequency = (StaringTiming*(workfrequency-minfrequency))/StaringTime + minfrequency;
		if (frequency == 0){frequency = minfrequency;}
		
		if (StaringTiming>=StaringTime){
			StaringTiming = 1;
			frequency = workfrequency;
			Started = true;
			Starting =false;
			Timing = 0;
		}
	}

	if (Stoping){
		
		StaringTiming = Timing;
		frequency = workfrequency - ((StaringTiming*(workfrequency-minfrequency))/StopingTime);
		if (frequency == 0){frequency = minfrequency;}
		
		if (StaringTiming>StopingTime){
			StaringTiming = 1;
			Started = false;
			Adjust = false;
			Stoping = false;
			Off();
			if(Reversing){ ReversPause = true;Timing=0;}
		}
	}
	
	if (ReversPause){
		TimeCoutPauseReverce++;
		if (TimeCoutPauseReverce>1000){
			BeginStart();
			ReversPause = false;
			TimeCoutPauseReverce =0;
		}	
	}
	
	if (Adjust&&Started){
		AtjustingTiming = Timing;
		if (AtjustingTiming>500){
			
			Adjusting();
			
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

void Rotor::WorkCurrentUp(int Up){
	WorkCurrent = WorkCurrent + Up;
	if (WorkCurrent > 1000){ WorkCurrent = 10000;}
}

void Rotor::WorkCurrentDown(int Down){
	if(WorkCurrent>Down){WorkCurrent = WorkCurrent - Down;
		}else{ WorkCurrent = 1;}
	}



bool Rotor::RotorStopped(){
	if(Started||Starting||Stoping){
		return false;
		}else{
		return true;
	}
}



void Rotor::set_A_PWM(int phasa){
	
	A_PWM = SinTable[phasa]*PowerTable[frequency-1];
	
	if (phasa >= 0 && phasa <= 12){
		A_DerectPort &= ~(1<<A_Derect);	
	}
	if (phasa > 12 && phasa < 24){
		A_DerectPort |= (1<<A_Derect);
	}
}

void Rotor::set_B_PWM(int phasa){
	
	B_PWM = SinTable[phasa]*PowerTable[frequency-1];
	
	if (phasa >= 0 && phasa <= 12){
		B_DerectPort &= ~(1<<B_Derect);
	}
	if (phasa > 12 && phasa < 24){
		B_DerectPort |= (1<<B_Derect);
	}
}

void Rotor::set_C_PWM(int phasa){
	
	C_PWM = SinTable[phasa]*PowerTable[frequency-1];
	
	if (phasa >= 0 && phasa <= 12){
		C_DerectPort &= ~(1<<C_Derect);
	}
	if (phasa > 12 && phasa < 24){	
		C_DerectPort |= (1<<C_Derect);
	}
}



void Rotor::tik(){
	if (Started||Starting){
		phasa_a++;
		phasa_b++;
		phasa_c++;
		
		if (phasa_a>23){phasa_a=0;}
		if (phasa_b>23){phasa_b=0;}
		if (phasa_c>23){phasa_c=0;}
		
		set_A_PWM(phasa_a);
		if(!Reverse){set_B_PWM(phasa_b);}else{set_B_PWM(phasa_c);}
		if(!Reverse){set_C_PWM(phasa_c);}else{set_C_PWM(phasa_b);}
		
		
		//if (phasa_a==1){PORTD |= (1<<0);}
		//if (phasa_a==15){PORTD  &= ~(1<<0);}
		Timing = Timing + Period;
		if ((phasa_a == 0)&&(frequency>=50)){FastFreq = true; phasa_b = 3; phasa_c = 7;};
		SetFrequency(frequency);
		
	}
	
	TimingPanel = TimingPanel + Period;
}
 
void Rotor::set_A_PWMFast(int phasa){
	
	if (phasa >= 0 && phasa < 6){
		A_DerectPort &= ~(1<<A_Derect);
		A_PWM = SinTableFast[phasa];
	}
	if (phasa >= 6 && phasa < 12){
		A_DerectPort |= (1<<A_Derect);
		A_PWM = SinTableFast[phasa - 6];
	}
}

void Rotor::set_B_PWMFast(int phasa){
	
	if (phasa >= 0 && phasa < 6){
		B_DerectPort &= ~(1<<B_Derect);
		B_PWM = SinTableFast[phasa];
	}
	if (phasa >= 6 && phasa < 12){
		B_DerectPort |= (1<<B_Derect);
		B_PWM = SinTableFast[phasa - 6];
	}
}

void Rotor::set_C_PWMFast(int phasa){
	
	if (phasa >= 0 && phasa < 6){
		C_DerectPort &= ~(1<<C_Derect);
		C_PWM = SinTableFast[phasa];
	}
	if (phasa >= 6 && phasa < 12){
		C_DerectPort |= (1<<C_Derect);
		C_PWM = SinTableFast[phasa - 6];
	}
}

void Rotor::tikFast(){
	if (Started||Starting){
		phasa_a++;
		phasa_b++;
		phasa_c++;
		
		if (phasa_a>11){phasa_a=0;}
		if (phasa_b>11){phasa_b=0;}
		if (phasa_c>11){phasa_c=0;}
		
		
		set_A_PWMFast(phasa_a);
		if(!Reverse){set_B_PWMFast(phasa_b);}else{set_B_PWMFast(phasa_c);}
		if(!Reverse){set_C_PWMFast(phasa_c);}else{set_C_PWMFast(phasa_b);}
		
		//if (phasa_a==1){PORTD |= (1<<0);}
		//if (phasa_a==6){PORTD  &= ~(1<<0);}
		Timing = Timing + Period;
		if ((phasa_a == 0)&&(frequency<50)){FastFreq = false;phasa_b = 7;phasa_c = 15;};
		SetFrequency(frequency);
		
		
	}	
	
	TimingPanel = TimingPanel + Period;
}



void Rotor::BeginStart(){
	phasa_a = 0;
	phasa_b = 7;//9
	phasa_c = 15;//19
	set_A_PWM(phasa_a);
	set_B_PWM(phasa_b);
	set_C_PWM(phasa_c);
	PWM_On();
	Starting = true;
	Timing = 0;
	
	//Started = true;
	//frequency = workfrequency;
}

void Rotor::BeginStop(){
	Timing = 0;
	Stoping = true;
	
}

void Rotor::StopAlarm(){
	Started = false;
	Stoping = false;
	Off();
}

void Rotor::Off(){
	set_A_PWM(0);
	set_B_PWM(0);
	set_C_PWM(0);
	PWM_Off();	
}


void Rotor::StartAdjust(){
	workfrequency = 1;
	BeginStart();
	Adjust = true;
	for(int i=0; i<50; i++){
		PowerTable[i]=0.5;
	}
}

void Rotor::Adjusting(){
	float err;
	CounterStable++;
	SummCurrentAdjust = SummCurrentAdjust + Current;
	if(CounterStable>=50){
		CurrentAverage = SummCurrentAdjust/50;
		SummCurrentAdjust = 0;
		CounterStable=0;
		if (CurrentAverage<WorkCurrent-2&&frequency<50&&PowerTable[frequency -1]<1){
			err = WorkCurrent - CurrentAverage;
			if(frequency<15){err = err/10000;}else{err = err/1000;}
			PowerTable[frequency-1] = PowerTable[frequency-1] + err;
			if (PowerTable[frequency-1] > 1){ PowerTable[frequency-1] = 1;}
		}else{
			if(frequency==50){
				Adjust = false;
				BeginStop();
				workfrequency = 50;
				GetNewAdjust = true;
			}else{
				Timing = 0;
				frequency = frequency + 1;
				PowerTable[frequency-1] = PowerTable[frequency - 2] - 0.05;	
			}		
		}
	}
}