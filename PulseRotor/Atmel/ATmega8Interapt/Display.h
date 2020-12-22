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
	Send_SPI(0x09, 0xFF); //включим режим декодировани€
	Send_SPI(0x0B, dg - 5); //сколько разр€дов используем
	Send_SPI(0x0A, 0x05); //€ркость
	Send_SPI(0x0C, 1); //включим индикатор
	Clear_Display();
	Send_SPI(0x01, 0);
	Send_SPI(0x02, 0);
	Send_SPI(0x03, 0);
	Send_SPI(0x04, 0);
}


void LED_DisplaySend(volatile long n)
{
	char ng = 0; //переменна€ дл€ минуса
	if (n < 0)
	{
		ng = 1;
		n *= -1;
	}
	Clear_Display();
	if (n == 0) {
		Send_SPI(0x01, 0); //в первый разр€д напишем 0
		return;
	}
	char i = 0;
	do {
		Send_SPI(++i, n%10);
		n /= 10;
	} while (n);
	if (ng) {
		Send_SPI(i+1, 0xA); //символ -
	}
}

void LED_DisplayNumberFull(volatile long n)
{
	int i;
	//Clear_7219();
	for(i=0;i<dg;i++)
	{
		Send_SPI(i+1,(n/((long)pow(10,i)))%10);
	}
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


#endif /* DISPLAY_H_ */