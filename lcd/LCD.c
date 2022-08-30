/*
 * LCD.c
 *
 * Created: 29/08/2022 15:20:54
 *  Author: patryk
 */ 
#include "LCD.h";


void init_lcd(){
	_delay_ms(20);
	command(four_bit_mode);	/* 4bit mode */
	command(double_line_lcd_mode);	/* Initialization of 16X2 LCD in 4bit mode */
	command(blinking_cursor);	/* Display ON Cursor OFF */
	command(auto_increment_cursor);	/* Auto Increment cursor */
	command(clear_display);	/* clear display */
	command(cursor_to_home_position);	/* cursor at home position */
	write("Hello! :)");
	_delay_ms(1000);
	command(clear_display);
}

void enable(){
	BitSet(PORTC,PORTC5);
	_delay_ms(5);
	BitClear(PORTC,PORTC5);
}

void enable_write_mode(){
	BitSet(PORTC,PORTC4);
}

void enable_command_mode(){
	BitClear(PORTC,PORTC4);
}

void command(unsigned char cmd){
	enable_command_mode();
	uint8_t ldata = cmd;
	PORTD = ldata;
	enable();
	_delay_ms(5);
	ldata = ((cmd<<4)&0xF0);
	PORTD = ldata;
	enable();
	_delay_ms(5);
}

void letter(unsigned char letter){
	enable_write_mode();
	uint8_t ldata = letter;   /*Send higher nibble of command first to PORTC*/
	PORTD = ldata;
	enable();
	ldata = ((letter<<4)&0xF0);  // send lower
	PORTD = ldata;
	enable();
}

void write(const char *a){
	uint8_t i;
	for(i=0; a[i]!='\0';i++){
		letter(a[i]);
	}
}