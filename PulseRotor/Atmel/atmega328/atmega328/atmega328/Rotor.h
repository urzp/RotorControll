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
	bool Starting, Stoping, Reversing;
	bool Started, Reverse, Adjust;
	unsigned long StaringTime,StaringTiming, StopingTime, Timing;
	int phasa,NPMW, WorkCurrent, Current, CounterStable;
	int SinTable[30]={0,104,150,189,221,242,254,254,243,221,190,150,104,53,0,0,103,149,189,221,242,254,254,243,221,190,150,104,54,0};
	volatile int phasa_a=0;
	volatile int phasa_b=10;
	volatile int phasa_c=20;
	protected:
	private:

	//functions
	public:
	void Init();
	void SetFrequency(int freq);
	void Activity();
	void FrequncyUp(int up);
	void FrequencyDown(int down);
	void StartimeUp(int TimeUp);
	void StartimeDown(int TimeDown);
	void StoptimeUp(int TimeUp);
	void StoptimeDown(int TimeDown);
	bool RotorStopped();
	void PortsOff();
	void set_A_PWM(int phasa);
	void set_B_PWM(int phasa);
	void set_C_PWM(int phasa);
	void tik();
	void Move();
	void MoveForvard();
	void MoveBack();
	protected:
	private:


}; //Rotor

#endif //__ROTOR_H__

