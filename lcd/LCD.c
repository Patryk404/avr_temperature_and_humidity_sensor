/*
 * LCD.c
 *
 * Created: 29/08/2022 15:20:54
 *  Author: patryk
 */ 
#include "LCD.h";


void init_lcd(){
	_delay_ms(20);
	command(four_bit_mode);
	command(double_line_lcd_mode);
	command(blinking_cursor);	
	command(auto_increment_cursor);
	command(clear_display);
	command(cursor_to_home_position);	
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
	uint8_t ldata = ((cmd>>4)&0x0F);
	PORTD = ldata;
	enable();
	_delay_ms(5);
	ldata = cmd;
	PORTD = ldata;
	enable();
	_delay_ms(5);
}

void send_letter(unsigned char letter){
	enable_write_mode();
	uint8_t ldata = ((letter>>4)&0x0F);
	PORTD = ldata;
	enable();
	ldata = letter;
	PORTD = ldata;
	enable();
}

void write(const char *a){
	uint8_t i;
	for(i=0; a[i]!='\0';i++){
		send_letter(a[i]);
	}
}