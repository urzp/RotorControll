/*
 * RotorControll.h
 *
 * Created: 22.12.2020 10:51:37
 *  Author: Paul
 */ 


#ifndef ROTORCONTROLL_H_
#define ROTORCONTROLL_H_


void StartControll(){
	if (ButtonStart.PressRead()&&!Rotor.Started&&!Protect.Read()&&PowerReady.Read()){
		Rotor.Starting = true;
	}
}

void StopControll(){
	if (ButtonStop.PressRead()&&!Protect.Read()&&PowerReady.Read()){
		Rotor.Stoping = true;
	}
}

void ReverseControll(){
	if(ButtonReverse.PressRead()){
		Rotor.Reversing = true;
	}
}

void SpeedControll(){
	if(ButtonUp.PressRead()){
		Rotor.FrequncyUp();
		ModeFeq = true;
		ModeFeqCount = 0;
	}
	
	if(ButtonDown.PressRead()){
		Rotor.FrequencyDown();
		ModeFeq = true;		
		ModeFeqCount = 0;
	}
}


#endif /* ROTORCONTROLL_H_ */