/*
 * ModeControll.h
 *
 * Created: 22.12.2020 10:53:31
 *  Author: Paul
 */ 



#ifndef MODECONTROLL_H_
#define MODECONTROLL_H_


int slipTimes = 1000;


void LedMode(){
		BlueLed.On();
		RedLed.Off();
		GreenLed.Off();	
}

void IfSetUp(){
	ButtonUp.Scan();
	if(ButtonUp.getpressed){
		slip++;
		if(slip>=slipTimes){
			slip = slipTimes;
			switch(Mode){
				case ModeSetStartTime:Rotor.StartimeUp(1000);break;
				case ModeSetStopTime:Rotor.StoptimeUp(1000);break;
				case ModeSetWorkCarrent:Rotor.WorkCurrentUp(10);break;
			}
			_delay_ms(100);
		}
	}
	if(ButtonUp.PressRead()){
		slip = 0;
		switch(Mode){
			case ModeSetStartTime:Rotor.StartimeUp(100);break;
			case ModeSetStopTime:Rotor.StoptimeUp(100);break;
			case ModeSetWorkCarrent:Rotor.WorkCurrentUp(1);break;
		}
		BlueLed.Off();
		_delay_ms(100);
	}
}

void IfSetDown(){
	ButtonDown.Scan();
	if(ButtonDown.getpressed){
		slip++;
		if(slip>=slipTimes){
			slip = slipTimes;
			switch(Mode){
				case ModeSetStartTime:Rotor.StartimeDown(1000);break;
				case ModeSetStopTime:Rotor.StoptimeDown(1000);break;
				case ModeSetWorkCarrent:Rotor.WorkCurrentDown(10);break;
			}
			_delay_ms(100);
		}
	}
	if(ButtonDown.PressRead()){
		slip = 0;
		switch(Mode){
			case ModeSetStartTime:Rotor.StartimeDown(100);break;
			case ModeSetStopTime:Rotor.StoptimeDown(100);break;
			case ModeSetWorkCarrent:Rotor.WorkCurrentDown(1);break;
		}
		BlueLed.Off();
		_delay_ms(100);
	}	
}


void ModeStartTime(){
	
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonStart.getpressed)||Mode==ModeSetStartTime){
			Mode = ModeSetStartTime;
			LedMode();
			
			IfSetUp();
			IfSetDown();
			
			LED_DisplayTime_ms(Rotor.StaringTime);		
	
			ButtonStart.Scan();
			ButtonStart.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonStart.getpressed){
				Mode = ModeNo;
			}
		}
	}
}

void ModeStopTime(){
	
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonStop.getpressed)||Mode==ModeSetStopTime){
			Mode = ModeSetStopTime;
			LedMode();
			
			IfSetUp();
			IfSetDown();
			
			LED_DisplayTime_ms(Rotor.StopingTime);
			
			ButtonStop.Scan();
			ButtonStop.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonStop.getpressed){
				Mode = ModeNo;
			}
		}
	}
}

void ModeSetCurrent(){
	
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonReset.getpressed)||Mode==ModeSetWorkCarrent){
			Mode = ModeSetWorkCarrent;
			LedMode();
			
			IfSetUp();
			IfSetDown();
			
			LED_DisplayCurrent(Rotor.WorkCurrent);
			
			ButtonReset.Scan();
			ButtonReset.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonReset.getpressed){
				Mode = ModeNo;
			}					
			
		}
	}
}

void ModeAdjustRotor(){
	if (Rotor.RotorStopped()){
		while(ButtonStart.getpressed&&ButtonReset.getpressed){
			Rotor.StartAdjust();	
			ButtonReset.Scan();
			ButtonReset.PressRead();
		}
	}
}

void ModeSettingPMW(){
	
	if (ButtonReset.PressRead()){
		switch (Mode){
			case ModeNo:  Mode = ModeSetPMW; break;
			case ModeSetPMW:  Mode = ModeCurrent; break;
			case ModeCurrent:  Mode = ModeNo; break;		
		}
	}
}

#endif /* MODECONTROLL_H_ */