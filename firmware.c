/*
 * firmware.c
 *
 * Created: 11/27/2016 7:38:49 PM
 *  Author: Tigran
 */ 

#define F_CPU 128000UL
#include <avr/io.h>

int main(void)
{
	// output pins
	DDRB |= (1 << PB0); // Up signal
	DDRB |= (1 << PB1); // Down signal
	PORTB &= ~(1 << PB0);
	PORTB &= ~(1 << PB1);
	
	volatile char fwd_btn = 0; // «Up» button pressed
	volatile char bwd_btn = 0; // «Down» button pressed
	
	// input pins
	DDRB &= ~(1 << PB2);    // Reed switch
	PORTB |= (1 << PB2);
	
	DDRB &= ~(1 << PB3);    // «Up» button
	PORTB |= (1 << PB3);
	
	DDRB &= ~(1 << PB4);    // «Down» button
	PORTB |= (1 << PB4);
	
	while(1)
	{
		if ((PINB & (1 << PB4))) { bwd_btn = 0; }
		if ((PINB & (1 << PB3))) { fwd_btn = 0; }
		
		if (!(PINB & (1 << PB4)) && !bwd_btn) {
			bwd_btn = 1;
			PORTB &= ~(1 << PB0);
			PORTB ^= 1 << PINB1;
		}
		else if (!(PINB & (1 << PB3)) && !fwd_btn) {
			fwd_btn = 1;
			PORTB &= ~(1 << PB1);
			PORTB ^= 1 << PINB0;
		}
		else if (!(PINB & (1 << PB2)) && !fwd_btn && !bwd_btn) {
			PORTB &= ~(1 << PB0);
			PORTB &= ~(1 << PB1);
		}
	}															
}
