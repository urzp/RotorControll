/*
 * ModeControll.h
 *
 * Created: 22.12.2020 10:53:31
 *  Author: Paul
 */ 


#ifndef MODECONTROLL_H_
#define MODECONTROLL_H_
int slipTimes = 1000;

void ModeStartTime(){
	int slip;
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonStart.getpressed)||Mode){
			Mode = true;
			BlueLed.On();
			RedLed.Off();
			GreenLed.Off();


			ButtonUp.Scan();
			if(ButtonUp.getpressed){
				slip++;
				if(slip>=slipTimes){
					slip = slipTimes;
					Rotor.StartimeUp(1000);
					_delay_ms(100);
				}
			}	
			if(ButtonUp.PressRead()){
				slip = 0;
				Rotor.StartimeUp(100);
				BlueLed.Off();
				_delay_ms(100);
			}
			
			
			
			
			
			
			ButtonDown.Scan();
			if(ButtonDown.getpressed){
				slip++;
				if(slip>=slipTimes){
					slip = slipTimes;
					Rotor.StartimeDown(1000);
					_delay_ms(100);
				}
			}
			if(ButtonDown.PressRead()){
				slip = 0;
				Rotor.StartimeDown(100);
				BlueLed.Off();
				_delay_ms(100);
			}
			
			LED_DisplayTime_ms(Rotor.StaringTime);
			
			
			ButtonStart.Scan();
			ButtonStart.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonStart.getpressed){
				Mode = false;
			}
		}
	}
}

void ModeStopTime(){
	int slip;
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonStop.getpressed)||Mode){
			Mode = true;
			BlueLed.On();
			RedLed.Off();
			GreenLed.Off();


			ButtonUp.Scan();
			if(ButtonUp.getpressed){
				slip++;
				if(slip>=slipTimes){
					slip = slipTimes;
					Rotor.StoptimeUp(1000);
					_delay_ms(100);
				}
			}
			if(ButtonUp.PressRead()){
				slip = 0;
				Rotor.StoptimeUp(100);
				BlueLed.Off();
				_delay_ms(100);
			}
			
			
			
			
			
			
			ButtonDown.Scan();
			ButtonUp.Scan();
			if(ButtonDown.getpressed){
				slip++;
				if(slip>=slipTimes){
					slip = slipTimes;
					Rotor.StoptimeDown(1000);
					_delay_ms(100);
				}
			}
			
			
			if(ButtonDown.PressRead()){
				slip = 0;
				Rotor.StoptimeDown(100);
				BlueLed.Off();
				_delay_ms(100);
			}
			
			LED_DisplayTime_ms(Rotor.StopingTime);
			
			ButtonStop.Scan();
			ButtonStop.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonStop.getpressed){
				Mode = false;
			}
		}
	}
}


#endif /* MODECONTROLL_H_ */