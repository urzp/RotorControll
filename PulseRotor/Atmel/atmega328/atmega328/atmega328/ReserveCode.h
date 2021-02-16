/*
 * ReserveCode.h
 *
 * Created: 16.02.2021 9:35:35
 *  Author: Paul
 */ 


#ifndef RESERVECODE_H_
#define RESERVECODE_H_


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
int SinTable[30]={0,104,150,189,221,242,254,254,243,221,190,150,104,53,0,0,103,149,189,221,242,254,254,243,221,190,150,104,54,0};
//int SinTable[30]={53,104,150,189,221,242,254,254,243,221,190,150,104,53,0,-53,-103,-149,-189,-221,-242,-254,-254,-243,-221,-190,-150,-104,-54,0};
//int SinTable[60]={0,27,53,79,104,127,150,171,189,206,221,233,242,249,254,255,254,249,243,233,221,206,190,171,150,128,104,79,53,27,0,-26,-53,-78,-103,-127,-149,-170,-189,-206,-221,-233,-242,-249,-254,-255,-254,-250,-243,-233,-221,-207,-190,-171,-150,-128,-104,-80,-54,-27};

volatile int A_volume, B_volume, C_volume;


void set_A_PWM(int phasa){
	
	A_PWM = SinTable[phasa];
	
	if (phasa >= 0 && phasa < 14){
		A_DerectPort |= (1<<A_Derect);
	}
	if (phasa >= 14 && phasa < 30){
		A_DerectPort &= ~(1<<A_Derect);
	}
}

void set_B_PWM(int phasa){
	
	B_PWM = SinTable[phasa];
	
	if (phasa >= 0 && phasa < 14){
		B_DerectPort |= (1<<B_Derect);
	}
	if (phasa >= 14 && phasa < 30){
		B_DerectPort &= ~(1<<B_Derect);
	}
}

void set_C_PWM(int phasa){

	C_PWM = SinTable[phasa];
	
	if (phasa >= 0 && phasa < 14){
		C_DerectPort |= (1<<C_Derect);
	}
	if (phasa >= 14 && phasa < 30){
		C_DerectPort &= ~(1<<C_Derect);
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
	
	set_A_PWM(phasa_a);
	set_B_PWM(phasa_b);
	set_C_PWM(phasa_c);
	
	if (phasa_a==0){PORTD |= (1<<0);}
	if (phasa_a==15){PORTD  &= ~(1<<0);}
}

ISR (TIMER1_COMPA_vect)
{
	tik();
	OCR1A = 33333/10;
}



#endif /* RESERVECODE_H_ */