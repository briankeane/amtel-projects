/*
 * LED_SWITCH_AND_TIMER.c
 *
 * Created: 12/7/2020 4:23:31 PM
 * Author : lones
 */ 

#define F_CPU 16000000UL   // 16 MHz -- Must be defined before imports

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"


int main(void)
{
	SysInit();
	
	TC1_Init();
	
	sei();   // enable interrupts
	
    while (1) 
    {
		CheckSWs();
	}
}

/**
 * Set up general environment
 */
void SysInit(void)
{
	// Set up i/o ports
	DDRB |= (1<<DDB5);			// B5 Output (LED)
	DDRB &= ~(1<<DDB7);			// B7 Input  (PushButton)
}

/**
 * Check status of switches and take action on press and release
 */
void CheckSWs(void)
{
	if (SW1Pressed_F && !SW1ActionTaken_F)
	{
		LED_OFF();
		SW1ActionTaken_F = TRUE;
	}
	else if ( !SW1Pressed_F && SW1ActionTaken_F)
	{
		
		LED_ON();
		SW1ActionTaken_F = FALSE;
	}
}


/**
* Set up timer counter 1
*/
void TC1_Init(void)
{
	// Set up the interrupt to "prescale" up to as close to 1ms as possible (1/64th)
	// We handle the count from there.
	// 
	// Set CTC Mode
	TCCR1B |= (1<<WGM12);
	
	// Via Datasheet, p.155 table 19-7, register TCCR1B determines the scale
	// For 1/64th, set CS10=1, CS11=1, CS12=0
	TCCR1B |= (1<<CS10) | (1<<CS11);
	TCCR1B &= ~(1<<CS12);    // (extraneous b/c it is already initialized with a 0)
	
	// Enable Output Compare.
	// TODO: Ask about this
	TIMSK1 |= (1<<OCIE1A);
	
	// TODO: Ask about this too
	// Set OCR1A to F_CPU/freq*2*n-1
	OCR1A = 124;    // (uint8_t)(F_CPU/(1000*2*64) - 1)
}

/**
* *** Interrupts: ***
*/

/**
* Timer 1
* 
* fires every millisec
*/
ISR(TIMER1_COMPA_vect)
{
	// IF above zero, then decrement
	if (msecTimer)
		msecTimer--;
		
	if ((TestTimer) && (TestTimer < TIMER_DISABLE))
		TestTimer--;
		
	if (SecsCounter == 1000)
	{
		
		SecsCounter = 0;
		
		// Handle 1 sec events here
		
		// LED_TOGGLE();
	}
	
	if (SW1 != SW_PRESSED)
	{
		SW1dbTimer = 0;
		SW1Pressed_F = FALSE;
	}
	else
	{
		if (SW1dbTimer < 255)
			++SW1dbTimer;
	}
	if (SW1dbTimer > DB_TIME)
		SW1Pressed_F = TRUE;
}



