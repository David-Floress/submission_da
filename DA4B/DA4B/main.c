/*
 * DA4B.c
 *
 * Created: 4/20/2019 2:11:59 PM
 * Author : David Flores
 */ 

#define F_CPU 16000000UL /* Define CPU Frequency 16MHz */
#include <avr/io.h> /* Include AVR std. library file */
#include <util/delay.h> /* Include delay header file */

volatile unsigned int ADCVal;

int main(void)
{
	int period;
	timer_init();
	ADC_init();
	
	while(1)
	{
		ADCSRA |= (1<< ADSC);					//starts the conversion
		while((ADCSRA&(1<<ADIF))==0);			//waits for the conversion
		ADCVal = ADC & 0x03FF;					//takes right 10bits of ADC register
		OCR1A = 10*ADCVal;						//Duty Cycle
		
		PORTB = 0x09;
		while (!(TIFR1 & (1<<OCF1A)));
		TIFR1 |= (1<<OCF1A);
		PORTB = 0x03;
		while (!(TIFR1 & (1<<OCF1A)));
		TIFR1 |= (1<<OCF1A);
		PORTB = 0x06;
		while (!(TIFR1 & (1<<OCF1A)));
		TIFR1 |= (1<<OCF1A);
		PORTB = 0x0C;
		while (!(TIFR1 & (1<<OCF1A)));
		TIFR1 |= (1<<OCF1A);
	}
}


void timer_init(void)
{
	DDRB = 0x0F;						//Sets the lower bits of portb as outputs
	DDRC = 0;							//PortC is as an input
	PORTB = 0;							//Turns off all PB5 initially
	
	TCCR1B = (1<< WGM12) | (1<<CS11);	//Prescalar = 8
}
void ADC_init(void)
{
	// Analog to digital converter initialization
	DIDR0 = 0x1;
	ADMUX = (1<<REFS0);
	
	//right justified data
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|	//system clock used for ADC
	(1<<ADPS1)|(1<<ADPS0);				//free running
	ADCSRB = 0x0;
}
