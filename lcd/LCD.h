/*
 * IncFile1.h
 *
 * Created: 29/08/2022 15:20:26
 *  Author: patryk
 */ 
#define _NOP() do { __asm__ __volatile__ ("nop"); } while (0)
#define F_CPU 16000000
#define BitSet(Port,Bit) (Port|=(1<<Bit))
#define BitClear(Port,Bit) (Port&=~(1<<Bit))
#include <util/delay.h>
#include <avr/io.h>

#ifndef INCFILE1_H_
#define INCFILE1_H_

void init_lcd();

void enable(); 

void enable_write_mode();

void enable_command_mode();

void command(unsigned char cmd);

void write(const char *a);

#endif /* INCFILE1_H_ */