/*
 * Task3 part1.c
 *
 * Created: 5/11/2019 10:12:17 PM
 * Author : user11
 */ 

//Task 3 Part1
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int main(void)
{
	DDRB |= (1<<2); //sets pb2 as an output
	PORTB |= (1<<2); //sets for pb2 led
	TCNT0 = 0;
	TCCR0A = (1<<WGM01); //CTC mode
	TCCR0B = (1<<CS00) | (1 << CS02); //sets prescaler to 2014
	TIMSK0 |= (1<<OCIE0A); //sets interrupt compare match
	sei(); //enables global interrupt
	while(1)
	{
	}
}
ISR(TIMER0_COMPA_vect)
{
	uint8_t OVFCount = 0;
	while(1)
	{
		while((TIFR0 & 0x01) == 0); //while flag is 0
		TCNT0 = 0x1D; //starts the count for TCNT0
		TIFR0 = 0x01; //resets the overflow flag
		//OVFCount++;
		if(OVFCount == 19 ) //overflow counter counts up to this
		{
			PORTB ^= (1<<2); //turns led off
		}
		else if(OVFCount == 49) //overflow counter counts up to this
		{
			PORTB ^= (1<<2); //keeps the led on
			OVFCount = 0; //resets the overflow count
		}
		OVFCount++; //increment overflow count
	}
}