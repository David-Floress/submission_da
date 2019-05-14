/*
 * DA2C.c
 *
 * Created: 5/10/2019 7:42:49 AM
 * Author : user11
 */ 

//Task 1 Part1
#define F_CPU 16000000L
#include <avr/io.h>
int main()
{
	uint8_t OVFCount = 0; //overflow flag counter
	DDRB |= (1<<2); //set pb2 as an output
	PORTB |= (1<<2); //led output
	TCNT0 = 0x1D; //starts the counter
	TCCR0B = (1<<CS00) | (1 << CS02); //sets the prescaler to 1024
	while(1)
	{
		while((TIFR0 & 0x01) == 0); //while flag is 0
		TCNT0 = 0x1D; //starting counter for tcnt0
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
	return 0;
}

