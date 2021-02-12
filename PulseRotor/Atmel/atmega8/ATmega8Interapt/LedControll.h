/*
 * LedControll.h
 *
 * Created: 22.12.2020 11:05:23
 *  Author: Paul
 */ 


#ifndef LEDCONTROLL_H_
#define LEDCONTROLL_H_

void LedControll(){
	if (Rotor.Starting||Rotor.Stoping){
		BlueLed.On();
		RedLed.Off();
		GreenLed.Off();
		}else{
		BlueLed.Off();
	}
	
	if (Rotor.Started){
		if (!Rotor.Starting&&!Rotor.Stoping){GreenLed.On();}
		RedLed.Off();
		}else{
		GreenLed.Off();
		if (!Rotor.Starting&&!Rotor.Stoping){RedLed.On();}
	}
}



#endif /* LEDCONTROLL_H_ */