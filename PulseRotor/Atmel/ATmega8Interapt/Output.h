/* 
* Output.h
*
* Created: 10.12.2020 9:45:06
* Author: Paul
*/


#ifndef __OUTPUT_H__
#define __OUTPUT_H__


class Output
{
//variables
public:
	char _port;
	int _pin;
	bool _inv;
protected:
private:

//functions
public:
	void Init(char port, int pin, bool inv);
	void On();
	void Off();
protected:
private:


}; //Output

#endif //__OUTPUT_H__
