/*
 * SPI.h
 *
 * Created: 22.12.2020 12:31:59
 *  Author: Paul
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_init(void)
{
	DDRC |= ((1<<CLK)|(1<<DataSPI)|(1<<LOAD)); //ножки SPI на выход
	PORTC &= ~((1<<CLK )|(1<<DataSPI)|(1<<LOAD)); //низкий уровень
	
}

void SPI_SendByte (char byte)
{
	PORTC |= (1<<DataSPI);
	
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
	PORTC |= (1<<DataSPI);
	
}

void Send_SPI(char rg, char dt)
{
	PORTC &= ~(1<<LOAD);
	SPI_SendByte(rg);
	SPI_SendByte(dt);
	PORTC |= (1<<LOAD);
}



#endif /* SPI_H_ */