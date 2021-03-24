/*
 * ADC.h
 *
 * Created: 09.03.2021 8:15:10
 *  Author: Paul
 */ 


#ifndef ADC_H_
#define ADC_H_

long unsigned int adc_value, adc_summ, adc_count, adc_avarage;

void ADC_Init(void)
{
	ADCSRA |= (1<<ADEN) // ���������� ������������� ���
	|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//�������� 128 = 64 ���
	ADMUX |= (1<<REFS0)|(1<<MUX0); //���������� �������� �� 2,56�, ���� ADC0
	ADCSRA |= (1<<ADSC);
}

void ADC_read(){
	if (ADCSRA & (1<<ADSC)){
		
		}else{
		adc_value = ADC;
		adc_value = adc_value * 1.174;
		adc_summ=adc_summ+adc_value;
		adc_count++;
		if (adc_count==250){
			adc_avarage = adc_summ/300;
			adc_count=0;
			adc_summ=0;
		}
		ADCSRA |= (1<<ADSC);
	}
}



#endif /* ADC_H_ */