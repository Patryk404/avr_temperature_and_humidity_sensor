/*
 * sensor.h
 *
 * Created: 29/08/2022 15:58:19
 *  Author: patryk
 */ 



#define _NOP() do { __asm__ __volatile__ ("nop"); } while (0)
#define F_CPU 16000000
#define BitSet(Port,Bit) (Port|=(1<<Bit))
#define BitClear(Port,Bit) (Port&=~(1<<Bit))
#include <util/delay.h>
#include <avr/io.h>

#ifndef SENSOR_H_
#define SENSOR_H_

void init_sensor();

#endif /* SENSOR_H_ */