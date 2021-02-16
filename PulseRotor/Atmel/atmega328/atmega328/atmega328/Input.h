/* 
* Input.h
*
* Created: 16.02.2021 8:55:35
* Author: Paul
*/


#ifndef __INPUT_H__
#define __INPUT_H__


class Input
{
	//variables
	public:
	char _port;
	int _pin;
	protected:
	private:

	//functions
	public:
	void Init(char port, int pin);
	bool Read();
	protected:
	private:


}; //Input

#endif //__INPUT_H__
