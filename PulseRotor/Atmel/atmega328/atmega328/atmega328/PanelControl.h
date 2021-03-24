/*
 * PanelControl.h
 *
 * Created: 17.02.2021 10:09:27
 *  Author: Paul
 */ 


#ifndef PANELCONTROL_H_
#define PANELCONTROL_H_

int slip;

void ReadButtons(){
	ButtonStop.Scan();
	ButtonStart.Scan();
	ButtonReverse.Scan();
	ButtonUp.Scan();
	ButtonDown.Scan();
	ButtonReset.Scan();
};

void StartControll(){
	if (ButtonStart.PressRead()&&!Rotor.Started&&!Protect.Alarm){  
		Rotor.BeginStart();
	}
}

void StopControll(){
	if(Protect.Alarm){Rotor.StopAlarm();Protect.Reset();}
	if (ButtonStop.PressRead()&&!Rotor.RotorStopped()){ 
		Rotor.BeginStop();
	}
}

void ReverseControll(){
	if(ButtonReverse.PressRead()){
		if (!Rotor.Reverse){eeprom_write_float(&Reverse,2);}else{eeprom_write_float(&Reverse,1);}
		Rotor.Reversing = true;
		
	}
}

void SpeedControll(){
	
	
	
	if (ButtonUp.getpressed){
		slip++;
		if (slip>=700){
			slip=700;
			if(Mode == ModeNo){Rotor.FrequncyUp(10);}
			//if(Mode == ModeSetPMW||Mode == ModeCurrent){Rotor.PMWUp(10);}
			ModeFeq = true;
			GetNewFreq = true;
			ModeFeqCount = 0;
			_delay_ms(600);
		}
	}
	
	if(ButtonUp.PressRead()){
		slip=1;
		if(Mode == ModeNo) {Rotor.FrequncyUp(1);}
		//if(Mode == ModeSetPMW||Mode == ModeCurrent){Rotor.PMWUp(1);}
		ModeFeq = true;
		GetNewFreq = true;
		ModeFeqCount = 0;
	}
	
	if (ButtonDown.getpressed){
		slip++;
		if (slip>=700){
			slip=700;
			if(Mode == ModeNo){Rotor.FrequencyDown(10);}
			//if(Mode == ModeSetPMW){Rotor.PMWDown(10);}
			ModeFeq = true;
			GetNewFreq = true;
			ModeFeqCount = 0;
			_delay_ms(600);
		}
	}
	
	if(ButtonDown.PressRead()){
		slip=1;
		if(Mode == ModeNo){Rotor.FrequencyDown(1);}
		//if(Mode == ModeSetPMW){Rotor.PMWDown(1);}
		ModeFeq = true;
		GetNewFreq = true;
		ModeFeqCount = 0;
	}
	
	if (GetNewFreq){eeprom_write_float (&WorkFrequnce,Rotor.workfrequency);GetNewFreq = false;}
}



#endif /* PANELCONTROL_H_ */