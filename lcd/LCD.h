/*
 * IncFile1.h
 *
 * Created: 29/08/2022 15:20:26
 *  Author: patryk
 */ 
#define _NOP() do { __asm__ __volatile__ ("nop"); } while (0)
#define BitSet(Port,Bit) (Port|=(1<<Bit))
#define BitClear(Port,Bit) (Port&=~(1<<Bit))
#include <util/delay.h>
#include <avr/io.h>

#define four_bit_mode 0x02
#define double_line_lcd_mode 0x28
#define blinking_cursor 0x0F
#define auto_increment_cursor 0x06
#define clear_display 0x01
#define cursor_to_home_position 0x80
#define jump_second_line 0xC0

#ifndef INCFILE1_H_
#define INCFILE1_H_

void init_lcd();

void enable(); 

void enable_write_mode();

void enable_command_mode();

void command(unsigned char cmd);

void write(const char *a);

void send_letter(unsigned char letter);

#endif /* INCFILE1_H_ */