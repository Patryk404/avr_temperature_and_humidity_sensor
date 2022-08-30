/*
 * main.c
 *
 * Created: 8/28/2022 7:04:40 PM
 *  Author: patryk
 */ 


#include <xc.h>
#include "lcd/LCD.h";
int main(void)
{
	init_pins(); 
	init_lcd();
    while(1)
    {
    }
}

void init_pins(){
	DDRC = 0b00111000;
	DDRD = 0xF0;
}	
