/* 
* Output.h
*
* Created: 16.02.2021 8:57:16
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
	bool status;
	protected:
	private:

	//functions
	public:
	void Init(char port, int pin, bool inv);
	void On();
	void Off();
	void Switch();
	protected:
	private:


}; //Output

#endif //__OUTPUT_H__
