
/* GccApplication2.c
 *
 * Created: 3/4/2019 7:24:13 PM
 * Author : David Flores
 */

//C Code Part 2
#define F_CPU 16000000ul
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
int main(void){
	DDRB |= (1<<2);
	PORTB |= (1<<2);					//sets PORTB2 as an input
	DDRC &= (0<<2);						//
	PORTC |= (0<<2);					//sets push button to zero
	while (1)
	{
		if (!(PINC & (1 << PINC2)))
		{
			PORTB &= ~(1<<2);
			_delay_ms(1250);
		}
		else
		{
			PORTB |= (1<<2);
		}
	}
	return 0;
}


