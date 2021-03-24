/* 
* Rotor.h
*
* Created: 16.02.2021 13:04:34
* Author: Paul
*/


#ifndef __ROTOR_H__
#define __ROTOR_H__

#define A_PD    6
#define A_PWM   OCR0A
#define B_PD   5
#define B_PWM  OCR0B
#define C_PD    3
#define C_PWM   OCR2A

#define A_Derect  0
#define A_DerectPort  PORTB

#define B_Derect  1
#define B_DerectPort  PORTB

#define C_Derect  2
#define C_DerectPort  PORTB

class Rotor
{
	//variables
	public:
	unsigned long frequency, workfrequency, minfrequency, maxfrequency, minStartStopTime, maxStartStopTime;
	bool Starting, Stoping, Reversing, FastFreq;
	bool Started, Reverse, ReversPause, Adjust, GetNewAdjust;
	float Timing, Period, TimingPanel;
	unsigned long StaringTime,StaringTiming, AtjustingTiming, StopingTime, TimeCoutPauseReverce, SummCurrentAdjust;
	int phasa,NPMW, WorkCurrent, Current, CounterStable, CurrentAverage;
	//int SinTable[30]={0,53,104,150,189,221,242,254,254,243,221,190,150,104,53,0,53,104,150,189,221,242,254,254,243,221,190,150,104,53};
	//int SinTable[30]={0,53,104,150,189,221,242,254,254,243,221,190,150,104,53,0,53,104,150,189,221,242,254,254,243,221,190,150,104,53};
	int SinTable[24]={0,66,127,180,221,246,255,246,221,181,128,66,0,66,127,180,221,246,255,246,221,181,128,66};
	float PowerTable[50]={0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};   
	int SinTableFast[6]={0,255,255,255,255,0};
	int FrqTable[150];
	int FrqTableFast[150];
	float PerodTable[150]={33.33,16.66,11.11,8.33,6.66,5.55,4.76,4.16,3.70,3.33,3.03,2.77,2.56,2.38,2.22,2.08,1.96,1.85,1.75,1.66,1.58,1.51,1.44,1.38,1.33,1.28,1.23,1.19,1.14,1.11,1.07,1.04,1.01,0.98,0.95,0.92,0.90,0.85,0.83,0.81,0.79,0.78,0.76,0.74,0.73,0.71,0.69,0.68,0.67,0.65};
	volatile int phasa_a;
	volatile int phasa_b;
	volatile int phasa_c;
	protected:
	private:

	//functions
	public:
	void Init();
	void InitFreqTables();
	void SetFrequency(int freq);
	void Activity();
	void FrequncyUp(int up);
	void FrequencyDown(int down);
	void StartimeUp(int TimeUp);
	void StartimeDown(int TimeDown);
	void StoptimeUp(int TimeUp);
	void StoptimeDown(int TimeDown);
	void WorkCurrentUp(int Up);
	void WorkCurrentDown(int Down);
	bool RotorStopped();
	void BeginStart();
	void BeginStop();
	void StopAlarm();
	void Off();
	void PWM_On();
	void PWM_Off();
	void set_A_PWM(int phasa);
	void set_B_PWM(int phasa);
	void set_C_PWM(int phasa);
	void tik();
	void set_A_PWMFast(int phasa);
	void set_B_PWMFast(int phasa);
	void set_C_PWMFast(int phasa);
	void tikFast();
	void StartAdjust();
	void Adjusting();
	protected:
	private:


}; //Rotor

#endif //__ROTOR_H__

