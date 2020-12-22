/*
 * ModeControll.h
 *
 * Created: 22.12.2020 10:53:31
 *  Author: Paul
 */ 


#ifndef MODECONTROLL_H_
#define MODECONTROLL_H_


void ModeStartTime(){
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonStart.getpressed)||Mode){
			Mode = true;
			BlueLed.On();
			RedLed.Off();
			GreenLed.Off();


			ButtonUp.Scan();
			if(ButtonUp.PressRead()){
				Rotor.StartimeUp(100);
				BlueLed.Off();
				_delay_ms(500);
			}
			
			ButtonDown.Scan();
			if(ButtonDown.PressRead()){
				Rotor.StartimeDown(100);
				BlueLed.Off();
				_delay_ms(500);
			}
			
			ButtonStart.Scan();
			ButtonStart.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonStart.getpressed){
				Mode = false;
			}
		}
	}
}

void ModeStopTime(){
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonStop.getpressed)||Mode){
			Mode = true;
			BlueLed.On();
			RedLed.Off();
			GreenLed.Off();


			ButtonUp.Scan();
			if(ButtonUp.PressRead()){
				Rotor.StoptimeUp(100);
				BlueLed.Off();
				_delay_ms(500);
			}
			
			ButtonDown.Scan();
			if(ButtonDown.PressRead()){
				Rotor.StoptimeDown(100);
				BlueLed.Off();
				_delay_ms(500);
			}
			
			ButtonStop.Scan();
			ButtonStop.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonStop.getpressed){
				Mode = false;
			}
		}
	}
}


#endif /* MODECONTROLL_H_ */