/*
 * DA3A.c
 *
 * Created: 3/31/2019 11:38:46 AM
 * Author : David Flores
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Declaring Functions
void USART_send (char data);
void USART_putstring(char* StringPtr);
void USART_init(void);

char String[] = "BAM!"; //holds characters
char outs[20]; //20 character spaces
volatile float floating_var = 20; //floating point value

int main(void)
{
   TCCR1B = 5;				//Sets the prescalar to 1024
   TCNT1 = 49911;			//Resets the counter
   TIMSK1 = (1<<TOIE1);		//enables the overflow interrupt
   
   USART_init();
   sei();					//enables interrupt
    while (1) 
    {
	}
}

//Interrupt
ISR (TIMER1_OVF_vect)
{
	USART_putstring(String);
	USART_putstring("\n");
	USART_send('10');
	snprintf(outs, sizeof(outs), "%f\r\n", floating_var);
	USART_putstring("\n");
	USART_putstring(outs);
	TCNT1 = 49911;
}

void USART_init(void)
{
	UBRR0H = 0;
	UBRR0L = (F_CPU/16/BAUD - 1);
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}


//sends data to serial port
void USART_send(char data)
{
	while (!(UCSR0A & (1<< UDRE0)))
		UDR0 = data;
}

//sends data to serial port
void USART_putstring(char *stringPtr)
{
	while ((*stringPtr != '\0'))
	{
		while(!(UCSR0A & (1<< UDRE0)));
			UDR0 = *stringPtr;
				stringPtr++;
	}
}


	
