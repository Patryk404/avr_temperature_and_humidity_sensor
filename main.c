/*
 * main.c
 *
 * Created: 8/28/2022 7:04:40 PM
 *  Author: patryk
 */ 
#define _NOP() do { __asm__ __volatile__ ("nop"); } while (0)
#define F_CPU 16000000
#define BitSet(Port,Bit) (Port|=(1<<Bit))
#define BitClear(Port,Bit) (Port&=~(1<<Bit))


#include <xc.h>
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	init_pins(); 
	initialize_lcd();
    while(1)
    {
    }
}

void enable(){
	PORTC |= (1<<PORTC5);
	_delay_ms(5);
	PORTC ^= (1<<PORTC5);
}


void init_pins(){
	DDRC = 0xFF;
	DDRD = 0b11110000;
}

void switch_to_write_mode(){ // 1
	BitSet(PORTC,PORTC0);
	_delay_ms(5);
}

void switch_to_command_mode(){ //0
	BitClear(PORTC,PORTC0);
	_delay_ms(5);
}

void LCD_Command(unsigned char cmd )
{
	uint8_t ldata = cmd; 
	PORTD = ldata;
	enable();
	_delay_ms(5);
	ldata = ((cmd<<4)&0xF0);
	PORTD = ldata;
	enable();
	_delay_ms(5);
}

void send_letter(unsigned char letter){
	uint8_t ldata = letter;   /*Send higher nibble of command first to PORTC*/
	PORTD = ldata;
	enable();
	ldata = ((letter<<4)&0xF0);  // send lower
	PORTD = ldata;
	enable();
}
// https://stackoverflow.com/questions/47981/how-do-i-set-clear-and-toggle-a-single-bit 
// I AM FUCKING DUMB 

void send_string(const char *a){
	uint8_t i;
	for(i=0; a[i]!='\0';i++){
		send_letter(a[i]);
	}
}

void initialize_lcd(){
		_delay_ms(20);
		switch_to_command_mode();
		LCD_Command (0x02);	/* 4bit mode */
		LCD_Command (0x28);	/* Initialization of 16X2 LCD in 4bit mode */
		LCD_Command (0x0F);	/* Display ON Cursor OFF */
		LCD_Command (0x06);	/* Auto Increment cursor */
		LCD_Command (0x01);	/* clear display */
		LCD_Command (0x80);	/* cursor at home position */
		switch_to_write_mode();
		send_string("Hello World!");
}