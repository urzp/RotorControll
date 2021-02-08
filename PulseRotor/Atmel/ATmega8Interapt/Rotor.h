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
	int phasa,NPMW;
	bool LowFreq;       // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49
	int FreqPower[50] = {170,170,170,170,170,170,170,170,170,170,170,180,180,180,180,180,180,180,180,180,190,190,190,190,190,190,190,190,190,190,190,200,200,200,200,200,200,200,210,210,210,220,220,230,230,240,240,250,250,255};

	//bool LowFreq;       // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49
	//int FreqPower[50] = {170,170,170,170,170,170,170,170,180,180,190,190,190,200,200,200,200,200,200,200,210,210,210,210,210,210,210,220,220,220,220,220,220,220,220,220,220,230,230,230,230,230,230,240,240,240,240,250,250,255};

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
	void Move();
	void MoveForvard();
	void MoveBack();
	void MoveTest();
protected:
private:


}; //Rotor

#endif //__ROTOR_H__
