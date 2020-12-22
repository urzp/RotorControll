/* 
* Rotor.h
*
* Created: 10.12.2020 10:52:53
* Author: Paul
*/


#ifndef __ROTOR_H__
#define __ROTOR_H__


class Rotor
{
//variables
public:
	unsigned long frequency, workfrequency, minfrequency, maxfrequency, minStartStopTime, maxStartStopTime;
	bool Starting, Stoping, Reversing;
	bool Started, Reverse;
	unsigned long StaringTime,StaringTiming, StopingTime;
protected:
private:

//functions
public:
	void Init();
	void SetFrequency(int freq);
	void Activity();
	void FrequncyUp();
	void FrequencyDown();
	void StartimeUp(int TimeUp);
	void StartimeDown(int TimeDown);
	void StoptimeUp(int TimeUp);
	void StoptimeDown(int TimeDown);
	bool RotorStopped();
protected:
private:


}; //Rotor

#endif //__ROTOR_H__
