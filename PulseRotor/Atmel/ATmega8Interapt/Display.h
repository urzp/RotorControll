/*
 * Display.h
 *
 * Created: 22.12.2020 12:36:00
 *  Author: Paul
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_


void Clear_Display(void)
{
	char i = dg;
	// Loop until 0, but don't run for zero
	do {
		// Set each display in use to blank
		Send_SPI(i, 0xF); //CHAR BLANK
	} while (--i);
}





void LED_Display_Init(){
	Send_SPI(0x09, 0xFF); //������� ����� �������������
	Send_SPI(0x0B, dg - 5); //������� �������� ����������
	Send_SPI(0x0A, 0x05); //�������
	Send_SPI(0x0C, 1); //������� ���������
	Clear_Display();
	Send_SPI(0x01, 0);
	Send_SPI(0x02, 0);
	Send_SPI(0x03, 0);
	Send_SPI(0x04, 0);
}

char SHD0032G(volatile long n ){
	char symbol;

	switch(n){
		case 0: symbol=0b01111110; break;
		case 1: symbol=0b00001100; break;
		case 2: symbol=0b10110110; break;
		case 3: symbol=0b10011110; break;
		case 4: symbol=0b11001100; break;
		case 5: symbol=0b11011010; break;
		case 6: symbol=0b11111010; break;
		case 7: symbol=0b00001110; break;
		case 8: symbol=0b11111110; break;
		case 9: symbol=0b11011110; break;
	}
	
	return symbol;
	
}

void LED_DisplaySend(volatile long n, int point)
{
	char ng = 0; //���������� ��� ������
	if (n < 0)
	{
		ng = 1;
		n *= -1;
	}
	Clear_Display();
	if (n == 0) {
		Send_SPI(0x01, 0); //� ������ ������ ������� 0
		return;
	}
	char i = 0;
	do {
		if(i==point&&i>0){Send_SPI(++i, n%10+0x080);}else{Send_SPI(++i, n%10);}
		n /= 10;
	} while (n);
	if (ng) {
		Send_SPI(i+1, 0xA); //������ -
	}
}

void LED_DisplaySend_(volatile long n, int point){
	
	char symbol_1, symbol_2, symbol_3, symbol_4;
	char SHDsymbol_1, SHDsymbol_2, SHDsymbol_3, SHDsymbol_4;
	
	
	if (n == 0) {
		SHDsymbol_1 = SHD0032G(0);
		SHDsymbol_2 = 0b00000000;
		SHDsymbol_3 = 0b00000000;
		SHDsymbol_4 = 0b00000000;
		Send_SPI_SHD0032(SHDsymbol_1,SHDsymbol_2,SHDsymbol_3,SHDsymbol_4);
		return;
	}
	
	
	symbol_1 = n%10;
	symbol_2 = n/10%10;
	symbol_3 = n/100%10;
	symbol_4 = n/1000%10;
	
	SHDsymbol_1 = SHD0032G(symbol_1);
	SHDsymbol_2 = SHD0032G(symbol_2);
	SHDsymbol_3 = SHD0032G(symbol_3);
	SHDsymbol_4 = SHD0032G(symbol_4);
	

	
	if(n<1000){SHDsymbol_4 = 0b00000000;}
	if(n<100 ){SHDsymbol_3 = 0b00000000;}
	if(n<10&&point==0){SHDsymbol_2 = 0b00000000;}
	
	
	switch(point){
		case 1: SHDsymbol_1 |=(1<<0);break;
		case 2: SHDsymbol_2 |=(1<<0);break;
		case 3: SHDsymbol_3 |=(1<<0);break;
		case 4: SHDsymbol_4 |=(1<<0);break;
	}
	
	Send_SPI_SHD0032(SHDsymbol_1,SHDsymbol_2,SHDsymbol_3,SHDsymbol_4); 
	
	}


void LED_DisplayTime_ms(volatile long n)
{
	LED_DisplaySend(n/100, 1);
}

void DidplayFeqSet(){
	if(ModeFeq){
		ModeFeqCount++;
		if(ModeFeqCount>10000){
			ModeFeq=false;
			ModeFeqCount = 0;
		}
	}
}


void SendInfDisplay(){
	if (!Mode){
		if(!Rotor.RotorStopped()) {
			LED_DisplaySend(Rotor.frequency, 0);
			}else{
			if(ModeFeq){
				LED_DisplaySend(Rotor.frequency, 0);
				}else{
				LED_DisplaySend(0, 0);
			}
			
		}
	}
}

#endif /* DISPLAY_H_ */