/*
 * ModeControll.h
 *
 * Created: 25.02.2021 11:44:06
 *  Author: Paul
 */ 


#ifndef MODECONTROLL_H_
#define MODECONTROLL_H_

int slipTimes = 100;


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
			_delay_ms(300);
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
		_delay_ms(300);
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
			_delay_ms(300);
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
		_delay_ms(300);
	}
}


void ModeStartTime(){
	
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonStart.getpressed)||Mode==ModeSetStartTime){
			Mode = ModeSetStartTime;
			LedMode();
			
			IfSetUp();
			IfSetDown();
			
			LED_DisplayTime_ms(Rotor.StaringTime);GetNewStartime = true;
			
			ButtonStart.Scan();
			ButtonStart.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonStart.getpressed){
				Mode = ModeNo;
			}
		}
	}
	
	if(GetNewStartime){eeprom_write_float(&StaringTime, Rotor.StaringTime);GetNewStartime = false;}
}

void ModeStopTime(){
	
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonStop.getpressed)||Mode==ModeSetStopTime){
			Mode = ModeSetStopTime;
			LedMode();
			
			IfSetUp();
			IfSetDown();
			
			LED_DisplayTime_ms(Rotor.StopingTime);GetNewStoptime = true;
			
			ButtonStop.Scan();
			ButtonStop.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonStop.getpressed){
				Mode = ModeNo;
			}
		}
	}
	
	if(GetNewStoptime){eeprom_write_float(&StopingTime, Rotor.StopingTime);GetNewStoptime = false;}
}

void ModeSetCurrent(){
	
	if (Rotor.RotorStopped()){
		while(((ButtonUp.getpressed||ButtonDown.getpressed)&&ButtonReset.getpressed)||Mode==ModeSetWorkCarrent){
			Mode = ModeSetWorkCarrent;
			LedMode();
			
			IfSetUp();
			IfSetDown();
			
			LED_DisplayCurrent(Rotor.WorkCurrent); GetNewWorkCurrent = true;
			
			ButtonReset.Scan();
			ButtonReset.PressRead();
			
			if (!ButtonUp.getpressed&&!ButtonReset.getpressed){
				Mode = ModeNo;
			}
			
		}
	}
	
	if(GetNewWorkCurrent){eeprom_write_float(&WorkCurrent, Rotor.WorkCurrent);GetNewWorkCurrent = false;}
}

void ModeAdjustRotor(){
	if (Rotor.RotorStopped()){
		while(ButtonStart.getpressed&&ButtonReset.getpressed){
			Rotor.StartAdjust();
			ButtonReset.Scan();
			ButtonReset.PressRead();
		}
	}
	
	if (Rotor.GetNewAdjust&&Rotor.RotorStopped()){
		Rotor.GetNewAdjust = false;
		eeprom_write_float(&UsePowerTable, 1);
		for(int i =0; i<50; i++){
			eeprom_write_float(&PowerTable[i],Rotor.PowerTable[i]);
		}
	}
}

void ModeSettingMode(){
	
	if (ButtonReset.PressRead()){
		switch (Mode){
			case ModeNo:  Mode = ModeCurrent; break;
			case ModeSetPMW:  Mode = ModeCurrent; break;
			case ModeCurrent:  Mode = ModeNo; break;
		}
	}
}



#endif /* MODECONTROLL_H_ */