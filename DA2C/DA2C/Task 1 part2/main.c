/*
 * Task 1 part2.c
 *
 * Created: 5/10/2019 8:45:32 AM
 * Author : user11
 */ 


// Task 1 part2
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB |= (1<<2); //sets pb2 as an input
	PORTB |= (1<<2); //sets pb2 high for LED
	DDRC &= (0<<2); //sets PC2 as an input
	PORTC |= (0<<2); //sets PC2 low
	TCCR0A = 0;
	TCCR0B = (1<<CS00) | (1<<CS02); //sets the prescaler to 1024
	int OVFCount = 0;
	while (1)
	{
		if (!(PINC & (1<<PINC2))) //checks if the pushbutton is pressed
		{
			OVFCount = 0;
			TCNT0 = 0;
		}
		while ((TIFR0 & 0x01) == 0);
		TCNT0 = 0x05; //starts count at this value
		TIFR0 = 0x01; //rests the overflow flag
		OVFCount++; //overflow flag counter increment
		if (OVFCount <= 78) //when the overflow counter is less than or equal to 78
		{
			PORTB = (0<<2); //portb2 led is on
		}
		else
		{
			PORTB = (1<<2); //portb2 led is off
		}
	}
	return 0;
}
