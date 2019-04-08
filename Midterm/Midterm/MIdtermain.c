
/*
* Created: 4/5/2019 3:02:41 PM
* Author : David Flores
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#define F_CPU 16000000UL
#define BAUD 115200
#define FOSC 16000000
#define THEUBRR FOSC/8/BAUD -1

volatile uint8_t ADCvalue;
volatile unsigned char ADCtemp[5];
volatile unsigned char CWMODE[] = "AT+CWMODE=3\r\n"; //Set to three for the wifi
volatile unsigned char WIFI[] = "AT+CWJAP=\"EC4234\", \"G2C26B2B89582\"\r\n"; //Connects to Internet
volatile unsigned char ENABLE[] = "AT+CIPMUX=0\r\n"; //Connect to WiFi
volatile unsigned char CIPSTART[] = "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n"; //TCP strip remote IP, 80 is the port
volatile unsigned char CIPSEND[] = "AT+CIPSEND=45\r\n"; //Length of data
volatile unsigned char SEND_DATA[] = "GET /update?key=AHDBMTLB6ZCBMG40&field1="; //Writes API key
volatile unsigned char PAUSE[] = "\r\n\r\n";

void send_AT (volatile unsigned char c[]); //sends the arrays to this function

int main( void )
{
/* ADC */
ADMUX = 0; // uses ADC0
ADMUX |= (1 << REFS0); // use AVcc as the reference
ADMUX |= (1 << ADLAR); // Right adjusts for 8 bit resolution

ADCSRA |= (1 << ADATE); // Set ADC Auto Trigger Enable THEUBRR
ADCSRB = 0; // 0 for free running ode
ADCSRA |= (1 << ADEN); // Enable ADC
ADCSRA |= (1 << ADIE); // Enables Interrupts
ADCSRA |= (1 << ADSC); // Start ADC conversion
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescaler for 16Mhz


/* UART */
UBRR0H = ((THEUBRR) >> 8); //Shift right to store upper 8 bits
UBRR0L = THEUBRR; //Store lower bits

UCSR0A |= (1 << U2X0); //Double the USART transmission speed
UCSR0B |= (1 << TXEN0); // Enables USART transmitter
UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Set frame: 8data, 1 stop, no parity bit

_delay_ms(1000);
send_AT(CWMODE);

_delay_ms(1000);
send_AT(WIFI);

_delay_ms(2000);
send_AT(ENABLE);

sei();

while(1)
{
_delay_ms(1000);
send_AT(CIPSTART); //Connect to thingspeak, port 80

_delay_ms(1000);
send_AT(CIPSEND);

_delay_ms(1000);
send_AT(SEND_DATA);

send_AT(ADCtemp); //Sends the temperature data

send_AT(PAUSE); //A break in the data display
}
}


ISR(ADC_vect)
{
volatile unsigned int j=0;
char temp[5];

ADCvalue = (ADCH << 1);			//Shifts the value left one place

itoa(ADCvalue, temp, 10);		//Converts integers to string

while (j<5) {					//This transfers the temprature string from itoa() to ADCtemp
ADCtemp[j] = temp[j];
j++;
}
}


void send_AT(volatile unsigned char c[]) {
volatile unsigned int i=0, j=0;

j = 0;					//initialize the counter

while (c[j] != 0x00) { //while not at end of string
j++;
}

while (i<j) {
while(!(UCSR0A & (1 << UDRE0))); //If UDRE0 is 1, buffer is empty an can be written to
UDR0 = c[i];
i++;
}
}


