/*
 * musiQ-Player.cpp
 *
 * Created: 2/27/2024 5:43:38 AM
 * Author : Edwin Mwiti
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

// function prototypes
void GPIOInit();
void SDCardInit();
void displayInit();

int main(void)
{
    /* system init */
	void GPIOInit();
	void SDCardInit();
	void displayInit();
	
	
    while (1) 
    {
		_delay_ms(30);
    }
}

