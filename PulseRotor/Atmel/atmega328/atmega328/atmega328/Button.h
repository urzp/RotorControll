/* 
* Button.h
*
* Created: 16.02.2021 8:53:34
* Author: Paul
*/


#ifndef __BUTTON_H__
#define __BUTTON_H__


class Button
{
	//variables
	public:
	char _port;
	int _pin;
	int debounce,countDebounce;
	int pressed, getpressed;
	protected:
	private:
	

	//functions
	public:
	void Init(char port, int pin);
	bool PressRead();
	void Scan();
	protected:
	private:
	bool ReadPin();

}; //Button

#endif //__BUTTON_H__
