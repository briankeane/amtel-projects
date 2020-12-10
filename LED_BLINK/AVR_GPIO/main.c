/*
 * AVR_GPIO.c
 *
 * Created: 12/7/2020 4:23:31 PM
 * Author : lones
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL   // 16 MHz
#define LED_ON PORTB |= (1<<PORTB5)
#define LED_OFF PORTB |= (0<<PORTB5)
#define TOGGLE_LED PINB |= (1<<PINB5)

int main(void)
{
    DDRB |= (1<<DDB5);
    while (1) 
    {
		LED_ON;
		
		_delay_ms(1000);
		
		LED_OFF;
	}
}

