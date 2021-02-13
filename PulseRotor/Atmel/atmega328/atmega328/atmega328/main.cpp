/*
 * atmega328.cpp
 *
 * Created: 13.02.2021 12:41:22
 * Author : Paul
 */ 

#define F_CPU 16000000UL //16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define A_PD     0
#define A_PWM    OCR1A
#define B_PD   4
#define B_PWM  OCR1B
#define C_PD    5
#define C_PWM   OCR2A

const int A_Derect = PB0;
const int B_Derect = PB4;
const int C_Derect = PB5;

volatile int phasa_a=0;
volatile int phasa_b=19;
volatile int phasa_c=59;

//int SinTable[36]={0,44,87,128,164,195,221,240,251,255,251,240,221,195,164,128,87,44,0,-44,-87,-128,-164,-195,-221,-240,-251,-255,-251,-240,-221,-195,-164,-128,-87,-44};
//int SinTable[31]={0,53,104,150,189,221,242,254,254,243,221,190,150,104,53,0,-53,-103,-149,-189,-221,-242,-254,-243,-221,-190,-150,-104,-54,0};
int SinTable[60]={0,27,53,79,104,127,150,171,189,206,221,233,242,249,254,255,254,249,243,233,221,206,190,171,150,128,104,79,53,27,0,-26,-53,-78,-103,-127,-149,-170,-189,-206,-221,-233,-242,-249,-254,-255,-254,-250,-243,-233,-221,-207,-190,-171,-150,-128,-104,-80,-54,-27};

volatile int A_volume, B_volume, C_volume;


void set_A_PWM(){
	if (A_volume >= 0){
		PORTB |= (1<<A_Derect);
		A_PWM = A_volume;
	}
	if (A_volume<0){
		PORTB &= ~(1<<A_Derect);
		A_PWM = 255 + A_volume;
	}
}

void set_B_PWM(){
	if (B_volume >= 0){
		PORTB |= (1<<B_Derect);
		B_PWM = B_volume;
	}
	if (B_volume<0){
		PORTB &= ~(1<<B_Derect);
		B_PWM = 255 + B_volume;
	}
}

void set_C_PWM(){
	if (C_volume >= 0){
		PORTB |= (1<<C_Derect);
		C_PWM = C_volume;
	}
	if (C_volume<0){
		PORTB &= ~(1<<C_Derect);
		C_PWM = 255 + C_volume;
	}
}

void pin_init(void) {
	DDRB |= (1<<A_PD) | (1<<B_PD) | (1<<C_PD) | (1<<A_Derect) | (1<<B_Derect) | (1<<C_Derect);
	PORTB &= ~((1<<A_PD) | (1<<B_PD) | (1<<C_PD));
	PORTB |= (1<<A_Derect) | (1<<B_Derect) | (1<<C_Derect);
}

void timer1_init(void) {
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	TCNT1 = 0x00;
	ICR1 = 0xFF;
	OCR1A = 0x00;
	OCR1B = 0x00;
}

void timer2_init(void) {
	TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20) | (1 << CS21);
	TCNT2 = 0x00;
	OCR2A = 0x00;
}

void tik(){
	phasa_a++;
	phasa_b++;
	phasa_c++;
	
	if (phasa_a>59){phasa_a=0;}
	if (phasa_b>59){phasa_b=0;}
	if (phasa_c>59){phasa_c=0;}
	
	A_volume = SinTable[phasa_a];
	B_volume = SinTable[phasa_b];
	C_volume = SinTable[phasa_c];
	
	set_A_PWM();
	set_B_PWM();
	set_C_PWM();
	
	//if (phasa_a==0){PORTD |= (1<<PD1);}
	//if (phasa_a==29){PORTD  &= ~(1<<PD1);}
}

int main(void)
{
    pin_init();
	timer1_init();
	timer2_init();
	
	tik();
	
    while (1) 
    {
    }
}

