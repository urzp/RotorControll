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

#define C_PWM   OCR2


const int VT1 = PB0;
const int VT2 = PB1;
const int VT3 = PB2;
const int VT4 = PB3;
const int VT5 = PB4;
const int VT6 = PB5;

const int CLK = PC3;
const int DataSPI = PC4;
const int LOAD = PC5;

const int ModeNo = 0;
const int ModeSetTime = 1;
const int ModeSetPMW = 2;
const int ModeCurrent = 3;
const int ModeSetStartTime = 10;
const int ModeSetStopTime = 11;
const int ModeSetWorkCarrent = 12;

char dg = 8;

volatile int Phasa;
int TimePhasa = 1680;
volatile bool go ;
bool  started, pause, button;
bool move;
int debounse;

int IntConter=1;
bool MovingPulse[51];
int Mode;
bool  ModeFeq;
int  ModeFeqCount;

int countpulse;
int TruePulse;
int freq=1;
volatile int PMWCount, SetPower;
long unsigned int adc_value, adc_summ, adc_count, adc_avarage;

int slip;

Input Protect;


Button ButtonStop;
Button ButtonStart;
Button ButtonReverse;
Button ButtonUp;
Button ButtonDown;
Button ButtonReset;

Output Power;
Output PMW;
Output GreenLed;
Output RedLed;
Output BlueLed;

Rotor Rotor;


#include  "SPI.h"
#include  "Display.h"


void initTimer(){
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	TCCR1B |= (1<<CS12);//установим делитель.
	sei();
}





ISR (TIMER1_COMPA_vect)
{
	Rotor.Move();
	Rotor.SetFrequency(Rotor.frequency);
	SendInfDisplay();
}






void PMW_init(void) {
	DDRB |= (1<<PB3);
	PORTB &= ~(1<<PB3);
	
	TCCR2 |= (1 << COM21) | (1 << WGM21) | (1 << WGM20)| (1 << CS21);
	TCNT2 = 0x00;
	C_PWM = 0;
	
}


void ADC_Init(void)
{
	ADCSRA |= (1<<ADEN) // Разрешение использования АЦП
	|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//Делитель 128 = 64 кГц
	ADMUX |= (1<<REFS0)|(1<<MUX0); //Внутренний Источник ОН 2,56в, вход ADC0
	ADCSRA |= (1<<ADSC);
}

void ADC_read(){
	if (ADCSRA & (1<<ADSC)){
		
		}else{
		adc_value = ADC;
		adc_value = adc_value / 2;
		adc_summ=adc_summ+adc_value;
		adc_count++;
		if (adc_count==250){
			adc_avarage = adc_summ/300;
			adc_count=0;
			adc_summ=0;
		}
		ADCSRA |= (1<<ADSC);
	}
}

void Init(){
	
	
	Protect.Init('C', 0);
	
	
	ButtonStop.Init('D',0);
	ButtonStart.Init('D',1);
	ButtonReverse.Init('D',2);
	ButtonUp.Init('D',4);
	ButtonDown.Init('D',3);
	ButtonReset.Init('D',6);
	
	Power.Init('D',7, false);
	
	GreenLed.Init('B',6, true);
	RedLed.Init('B',7, true);
	BlueLed.Init('D',5,true);
	
	Rotor.Init();
	
	DDRB |= (1<<(PB0));
	DDRB |= (1<<(PB1));
	DDRB |= (1<<(PB2));
	DDRC |= (1<<(PC2));
	DDRB |= (1<<(PB4));
	DDRB |= (1<<(PB5));	
	DDRD |= (1<<(PD7));
	
	SPI_init();
	//LED_Display_Init();
	
	initTimer();
	PMW_init();
	ADC_Init();
	_delay_ms(100);
	Power.On();
}

void ReadInputs(){
	ButtonStop.Scan();
	ButtonStart.Scan();
	ButtonReverse.Scan();
	ButtonUp.Scan();
	ButtonDown.Scan();
	ButtonReset.Scan();
	ADC_read();
	Rotor.Current = adc_avarage;
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
		ModeSetCurrent();
		ModeAdjustRotor();
		ModeSettingPMW();
		
		ProtectControll();
		
		Rotor.Activity();

		LedControll();
		
		DidplayFeqSet();

		
		
	}
			
}