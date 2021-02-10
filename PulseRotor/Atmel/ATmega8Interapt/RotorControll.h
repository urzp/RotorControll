/*
 * RotorControll.h
 *
 * Created: 22.12.2020 10:51:37
 *  Author: Paul
 */ 


#ifndef ROTORCONTROLL_H_
#define ROTORCONTROLL_H_


void StartControll(){
	if (ButtonStart.PressRead()&&!Rotor.Started&&!Protect.Read()){
		Rotor.Starting = true;
	}
}

void StopControll(){
	if (ButtonStop.PressRead()&&!Protect.Read()){
		Rotor.Stoping = true;
	}
}

void ReverseControll(){
	if(ButtonReverse.PressRead()){
		Rotor.Reversing = true;
	}
}

void SpeedControll(){
	
	
	
	if (ButtonUp.getpressed){
		slip++;
		if (slip>=3000){
			slip=3000;
			if(Mode == ModeNo){Rotor.FrequncyUp(10);}
			if(Mode == ModeSetPMW||Mode == ModeCurrent){Rotor.PMWUp(10);}
			ModeFeq = true;
			ModeFeqCount = 0;
			_delay_ms(200);
		}
	}
	
	if(ButtonUp.PressRead()){
		slip=1;
		if(Mode == ModeNo) {Rotor.FrequncyUp(1);}
		if(Mode == ModeSetPMW||Mode == ModeCurrent){Rotor.PMWUp(1);}
		ModeFeq = true;
		ModeFeqCount = 0;
	}
	
	if (ButtonDown.getpressed){
		slip++;
		if (slip>=3000){
			slip=3000;
			if(Mode == ModeNo){Rotor.FrequencyDown(10);}
			if(Mode == ModeSetPMW){Rotor.PMWDown(10);}
			ModeFeq = true;
			ModeFeqCount = 0;
			_delay_ms(200);
		}
	}	
	
	if(ButtonDown.PressRead()){
		slip=1;
		if(Mode == ModeNo){Rotor.FrequencyDown(1);}
		if(Mode == ModeSetPMW){Rotor.PMWDown(1);}
		ModeFeq = true;		
		ModeFeqCount = 0;
	}
}


#endif /* ROTORCONTROLL_H_ */