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

#define A_PD    6
#define A_PWM   OCR0A
#define B_PD   5
#define B_PWM  OCR0B
#define C_PD    3
#define C_PWM   OCR2A

#define A_Derect  0
#define A_DerectPort  PORTB

#define B_Derect  1
#define B_DerectPort  PORTB

#define C_Derect  2
#define C_DerectPort  PORTB

volatile int phasa_a=0;
volatile int phasa_b=10;
volatile int phasa_c=20;

//int SinTable[36]={0,44,87,128,164,195,221,240,251,255,251,240,221,195,164,128,87,44,0,-44,-87,-128,-164,-195,-221,-240,-251,-255,-251,-240,-221,-195,-164,-128,-87,-44};
int SinTable[30]={53,104,150,189,221,242,254,254,243,221,190,150,104,53,0,-53,-103,-149,-189,-221,-242,-254,-254,-243,-221,-190,-150,-104,-54,0};
//int SinTable[30]={53,104,150,189,221,242,254,254,243,221,190,150,104,53,0,-53,-103,-149,-189,-221,-242,-254,-254,-243,-221,-190,-150,-104,-54,0};
//int SinTable[60]={0,27,53,79,104,127,150,171,189,206,221,233,242,249,254,255,254,249,243,233,221,206,190,171,150,128,104,79,53,27,0,-26,-53,-78,-103,-127,-149,-170,-189,-206,-221,-233,-242,-249,-254,-255,-254,-250,-243,-233,-221,-207,-190,-171,-150,-128,-104,-80,-54,-27};

volatile int A_volume, B_volume, C_volume;


void set_A_PWM(){
	if (A_volume >= 0){
		A_DerectPort |= (1<<A_Derect);
		A_PWM = A_volume;
	}
	if (A_volume<0){
		PORTB &= ~(1<<A_Derect);
		A_PWM = -1 * A_volume;
	}
}

void set_B_PWM(){
	if (B_volume >= 0){
		B_DerectPort |= (1<<B_Derect);
		B_PWM = B_volume;
	}
	if (B_volume<0){
		B_DerectPort &= ~(1<<B_Derect);
		B_PWM = -1 * B_volume;
	}
}

void set_C_PWM(){
	if (C_volume >= 0){
		C_DerectPort |= (1<<C_Derect);
		C_PWM = C_volume;
	}
	if (C_volume<0){
		C_DerectPort &= ~(1<<C_Derect);
		C_PWM = -1 * C_volume;
	}
}



void pin_init(void) {

	DDRB |= (1<<A_PD) | (1<<B_PD) | (1<<C_PD) | (1<<A_Derect) | (1<<B_Derect) | (1<<C_Derect);
	DDRD |= (1<<A_PD) | (1<<B_PD) | (1<<0);

	PORTB |= (1<<A_Derect) | (1<<B_Derect) | (1<<C_Derect);
	
}

void timer0_init(){
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |=  (1 << CS00);

	OCR0A = 0;
	OCR0B = 0;
}

void timer1_init(void) {
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK1 |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	TCCR1B |= (1<<CS10);//установим делитель.
	sei();
}

void timer2_init(void) {
	TCCR2A |= (1 << COM2A1)  | (1 << WGM21) | (1 << WGM20);
	TCCR2B |=  (1 << CS20);
	TCNT2 = 0x00;
	OCR2A = 0;
}



void tik(){
	phasa_a++;
	phasa_b++;
	phasa_c++;
	
	if (phasa_a>29){phasa_a=0;}
	if (phasa_b>29){phasa_b=0;}
	if (phasa_c>29){phasa_c=0;}
	
	A_volume = SinTable[phasa_a];
	B_volume = SinTable[phasa_b];
	C_volume = SinTable[phasa_c];
	
	set_A_PWM();
	set_B_PWM();
	set_C_PWM();
	
	if (phasa_a==0){PORTD |= (1<<0);}
	if (phasa_a==15){PORTD  &= ~(1<<0);}
}

ISR (TIMER1_COMPA_vect)
{
	tik();
	OCR1A = 33333/10;
}

int main(void)
{
    pin_init();
	timer0_init();
	timer1_init();
	timer2_init();
	
	tik();
	
    while (1) 
    {
    }
}

