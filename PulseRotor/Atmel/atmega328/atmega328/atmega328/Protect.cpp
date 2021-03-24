/* 
* Protect.cpp
*
* Created: 10.03.2021 14:33:44
* Author: Paul
*/


#include "Protect.h"
#include <avr/io.h>

void Protect::Init()
{
	Power.Init('D',0, false);
	currentLimit = 250;
	
} 


void Protect::Check(int current){
	if (current >= currentLimit){
		Power.Off();
		Alarm = true;
	}
}

void Protect::Reset(){
	Alarm = false;
	Power.On();
}
