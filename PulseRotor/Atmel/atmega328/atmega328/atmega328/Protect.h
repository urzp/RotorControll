/* 
* Protect.h
*
* Created: 10.03.2021 14:33:44
* Author: Paul
*/


#ifndef __PROTECT_H__
#define __PROTECT_H__
#include "Output.h"

class Protect
{
//variables
public:
	Output Power;
	int currentLimit;
	bool Alarm;
protected:
private:

//functions
public:
	void Init();
	void Check(int Current);
	void Reset();
protected:
private:


}; //Protect

#endif //__PROTECT_H__
