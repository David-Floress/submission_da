/*
 * GccApplication1.c
 *
 * Created: 3/4/2019 8:19:41 PM
 * Author : David Flores
 */ 

#include <avr/io.h>


//C Code Part 1
#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB = (1<<2);					//PB2 sets to 1
	TCCR1B = 5;						//prescaler set to 5			
	
	while(1)						//loops continously forever
	{
		TCNT1 = 0;					//T count equals 0
		while (TCNT1 != 4530){}		//T count till 40%
		PORTB ^= (1<<2);			//Produces toggle
		TCNT1 = 0;					//T count equals 0
		while (TCNT1 != 6796){}		//T count till 60%
		PORTB ^= (1<<2);			//Produces toggle
	}
	
	return 0;						
}

