/*
 * ProtectControll.h
 *
 * Created: 22.12.2020 10:55:09
 *  Author: Paul
 */ 


#ifndef PROTECTCONTROLL_H_
#define PROTECTCONTROLL_H_


void ProtectControll(){
	if(Protect.Read()){
		Rotor.Starting = false;
		Rotor.Stoping = false;
		Rotor.Started=0;
	}
	
	if (Protect.Read()){
		Power.Off();
		}else{
		Power.On();
	}
}


#endif /* PROTECTCONTROLL_H_ */