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
#include <avr/eeprom.h>

#include "Input.h"
#include "Button.h"
#include "Output.h"
#include "Rotor.h"
#include "Protect.h"

int Mode;
bool  ModeFeq, GetNewFreq, GetNewStoptime, GetNewStartime, GetNewWorkCurrent, GetNewAdjust;
int  ModeFeqCount;
const int ModeNo = 0;
const int ModeSetTime = 1;
const int ModeSetPMW = 2;
const int ModeCurrent = 3;
const int ModeSetStartTime = 10;
const int ModeSetStopTime = 11;
const int ModeSetWorkCarrent = 12;

int UseVariable;
float WorkFrequnce EEMEM;
float StaringTime EEMEM;
float StopingTime EEMEM;
float WorkCurrent EEMEM;
float Reverse EEMEM;
float UsePowerTable EEMEM;
float PowerTable[50] EEMEM;

Button ButtonStop;
Button ButtonStart;
Button ButtonReverse;
Button ButtonUp;
Button ButtonDown;
Button ButtonReset;

Output GreenLed;
Output RedLed;
Output BlueLed;


Protect Protect;

Rotor Rotor;

#include  "SPI.h"
#include "ADC.h"
#include  "Display.h"

#include "PanelControl.h"
#include "ModeControll.h""
#include "LedControl.h"



ISR (TIMER1_COMPA_vect)
{
	if (Rotor.FastFreq){
		Rotor.tikFast();
	}else{
		Rotor.tik();
	}
	
	//SendInfDisplay();
	//if(Rotor.TimingPanel > 100){SendInfDisplay();Rotor.TimingPanel=0;}
	//PORTD ^= (1<<0);
	//if(Rotor.TimingPanel > 100){LED_DisplaySend(Rotor.frequency, 0, 11);Rotor.TimingPanel=0;}
}

void Init(){
	
	ButtonReset.Init('D',1);
	ButtonStop.Init('C',0);
	ButtonStart.Init('C',2);
	ButtonReverse.Init('C',3);
	ButtonUp.Init('C',5);
	ButtonDown.Init('C',4);
	
	GreenLed.Init('B',5, true);
	RedLed.Init('B',4, true);
	BlueLed.Init('D',7,true);
	
	Protect.Init();
	
	
	
	ADC_Init();
	SPI_init();
	Rotor.Init();
	
	
	
	UseVariable = eeprom_read_float(&WorkFrequnce);
	if(UseVariable>0&&UseVariable<150){Rotor.workfrequency = UseVariable;}
		
	UseVariable = eeprom_read_float(&StopingTime);
	if(UseVariable>0&&UseVariable<30000){Rotor.StopingTime = UseVariable;}
	UseVariable = eeprom_read_float(&StaringTime);
	if(UseVariable>0&&UseVariable<30000){Rotor.StaringTime = UseVariable;}
		
	UseVariable = eeprom_read_float(&WorkCurrent);
	if(UseVariable>0&&UseVariable<1500){Rotor.WorkCurrent = UseVariable;}
	
	UseVariable = eeprom_read_float(&Reverse);
	if(UseVariable==1){Rotor.Reverse = false;}	
	if(UseVariable==2){Rotor.Reverse = true;}	
	
		
	UseVariable = eeprom_read_float(&UsePowerTable);
	if( UseVariable == 1){
		for (int i=0; i<50; i++){
			Rotor.PowerTable[i] = eeprom_read_float(&PowerTable[i]);
		}
	}
}

void ReadInputs(){
	ADC_read();
	Rotor.Current = adc_avarage;
	Protect.Check(adc_avarage);
}

int main(void)
{
	Init();
	
    while (1)
    {
		
	    ReadButtons();
	    ReadInputs();
	    StartControll();
	    StopControll();
	    ReverseControll();
	    SpeedControll();
		
		ModeStartTime();
		ModeStopTime();
		ModeSetCurrent();
		ModeAdjustRotor();
		
		ModeSettingMode();
		
	    
	    LedControll();
	    
	    
	    Rotor.Activity();
		DidplayFeqSet();
		SendInfDisplay();
		
	    
    }
}

