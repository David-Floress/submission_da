/*
 * DA4Bp2.c
 *
 * Created: 4/20/2019 7:03:04 PM
 * Author : user11
 */ 


//DA4B part 2
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
void adc_init(void);
int main(void)
{
	while(1)
	{
		//Timer1
		TCCR1A = (1 << COM1A1) | (1<<COM1B1) | (1<<WGM11);
		TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10); //set the prescalar to 64
		adc_init();

		ICR1=4999; //sets to 50Hz
		DDRB |= (1<<PB1); //output pin to the servo motor
		OCR1A = ADC; //for potentiometer
		_delay_ms(50); //delay between pot input and output of servo motor
	}
}
void adc_init (void)
{
	ADMUX = (1<<REFS0); //reference selection; AVcc
	ADCSRA |= (1<<ADEN) | //enable ADC
	(1<<ADSC) |
	(1<<ADPS2) | //prescalar 128
	(1<<ADPS1) |
	(1<<ADPS0);
	ADCSRB = 0x0; //adc control and status register free running mode
}