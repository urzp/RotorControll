/*
 * SPI.h
 *
 * Created: 22.12.2020 12:31:59
 *  Author: Paul
 */ 


#ifndef SPI_H_
#define SPI_H_

const int timeCTRIN = 1;
//const int timeCTR = 6;
const int timeCTR = 2;


void SPI_init(void)
{
	DDRC |= ((1<<CLK)|(1<<DataSPI)|(1<<LOAD)); //ножки SPI на выход
	PORTC &= ~((1<<CLK )|(1<<DataSPI)|(1<<LOAD)); //низкий уровень
	
}

void SPI_SendByte (char byte)
{
	
	
	PORTC &= ~(1<<CLK);
	if ((byte & (1<<7)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC |= (1<<CLK);
	_delay_us(timeCTR);
	
	PORTC &= ~(1<<CLK);
	if ((byte & (1<<6)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC |= (1<<CLK);
	_delay_us(timeCTR);
	
	PORTC &= ~(1<<CLK);
	if ((byte & (1<<5)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC |= (1<<CLK);
	_delay_us(timeCTR);
	
	PORTC &= ~(1<<CLK);
	if ((byte & (1<<4)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC |= (1<<CLK);
	_delay_us(timeCTR);
	
	PORTC &= ~(1<<CLK);
	if ((byte & (1<<3)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC |= (1<<CLK);
	_delay_us(timeCTR);
	
	PORTC &= ~(1<<CLK);
	if ((byte & (1<<2)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC |= (1<<CLK);
	_delay_us(timeCTR);
	
	PORTC &= ~(1<<CLK);
	if ((byte & (1<<1)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC |= (1<<CLK);
	_delay_us(timeCTR);
	
	PORTC &= ~(1<<CLK);
	if ((byte & (1<<0)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC |= (1<<CLK);
	_delay_us(timeCTR);

	PORTC &= ~(1<<CLK);
	
	
}

void Send_SPI(char rg, char dt)
{
	
	PORTC &= ~(1<<LOAD);
	PORTC |= (1<<DataSPI);
	SPI_SendByte(rg);
	SPI_SendByte(dt);
	PORTC |= (1<<DataSPI);
	PORTC |= (1<<LOAD);
}



void SPI_SendByte_SHD0032 (char byte)
{
	
	
	PORTC |= (1<<CLK);
	_delay_us(timeCTRIN);
	if ((byte & (1<<7)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC &= ~(1<<CLK);
	_delay_us(timeCTR);
	
	PORTC |= (1<<CLK);
	_delay_us(timeCTRIN);
	if ((byte & (1<<6)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC &= ~(1<<CLK);
	_delay_us(timeCTR);
	
	PORTC |= (1<<CLK);
	_delay_us(timeCTRIN);
	if ((byte & (1<<5)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC &= ~(1<<CLK);
	_delay_us(timeCTR);
	
	PORTC |= (1<<CLK);
	_delay_us(timeCTRIN);
	if ((byte & (1<<4)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC &= ~ (1<<CLK);
	_delay_us(timeCTR);
	
	PORTC |= (1<<CLK);
	_delay_us(timeCTRIN);
	if ((byte & (1<<3)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC &= ~(1<<CLK);
	_delay_us(timeCTR);
	
	PORTC |= (1<<CLK);
	_delay_us(timeCTRIN);
	if ((byte & (1<<2)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC &= ~(1<<CLK);
	_delay_us(timeCTR);
	
	PORTC |= (1<<CLK);
	_delay_us(timeCTRIN);
	if ((byte & (1<<1)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC &= ~(1<<CLK);
	_delay_us(timeCTR);
	
	PORTC |= (1<<CLK);
	_delay_us(timeCTRIN);
	if ((byte & (1<<0)) != 0 ){PORTC |= (1<<DataSPI);}else{PORTC &= ~(1<<DataSPI);}
	_delay_us(timeCTRIN);
	PORTC &= ~ (1<<CLK);
	_delay_us(timeCTR);

	PORTC &= ~(1<<CLK);
	
	
}

void Send_SPI_SHD0032(char symbol_1,char symbol_2,char symbol_3,char symbol_4){
	PORTC &= ~(1<<LOAD);
	PORTC &= ~(1<<DataSPI);
	SPI_SendByte_SHD0032(symbol_1);
	SPI_SendByte_SHD0032(symbol_2);
	SPI_SendByte_SHD0032(symbol_3);
	SPI_SendByte_SHD0032(symbol_4);
	PORTC &= ~(1<<DataSPI);
	PORTC |= (1<<LOAD);
	_delay_us(5);
	PORTC &= ~(1<<LOAD);
	
}

#endif /* SPI_H_ */