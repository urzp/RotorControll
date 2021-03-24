/*
 * LedControl.h
 *
 * Created: 17.02.2021 10:49:04
 *  Author: Paul
 */ 


#ifndef LEDCONTROL_H_
#define LEDCONTROL_H_


void LedControll(){
	if (Rotor.Starting||Rotor.Stoping){
		BlueLed.On();
		RedLed.Off();
		GreenLed.Off();
		}else{
		BlueLed.Off();
	}
	
	if (Rotor.Started){
		if (!Rotor.Starting&&!Rotor.Stoping){
			if(Rotor.Reverse){GreenLed.On();BlueLed.On();RedLed.On();}else{GreenLed.On();}
		}
		//RedLed.Off();
	}else{
		GreenLed.Off();
		if (!Rotor.Starting&&!Rotor.Stoping){RedLed.On();}
	}
}



#endif /* LEDCONTROL_H_ */