/*
 * sensor.c
 *
 * Created: 29/08/2022 15:58:03
 *  Author: patryk
 */ 
#include "sensor.h";

uint8_t read_pin(){
	uint8_t result = PINC & (1 << PINC3);
	return result;
}

void set_pin_input(){
	DDRC =0b00110000;
	BitClear(PORTC,PORTC3);
}

void reset(){
	DDRC = 0b00111000;
	BitClear(PORTC,PORTC3);
	_delay_ms(18);
	BitSet(PORTC,PORTC3);
	_delay_us(40);
}

uint8_t check(){
	uint8_t retry=0;
	set_pin_input();
	while(read_pin()&&retry<100){
		retry++;
		_delay_us(1);
	}
	if(retry>=100){
		return 1;
	}
	else {
		retry=0;
	}
	while(!read_pin()&&retry<100){
		retry++;
		_delay_us(1);
	}
	if(retry>=100){
		return 1;
	}
	return 0;
}

uint8_t read_bit(){
	uint8_t retry =0;
	while(read_pin()&&retry<100){
		retry++;
		_delay_us(1);
	}
	retry=0;
	while(!read_pin()&&retry<100){
		retry++;
		_delay_us(1);
	}
	_delay_us(40);
	if(read_pin()){
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t read_byte(){
	uint8_t i,dat;
	dat = 0;
	for(i=0;i<8;i++){
		dat<<=1;
		dat|=read_bit();
	}
	return dat;
}

uint8_t read_data(uint8_t *temperature,uint8_t *humidity){
	uint8_t buffer[5];
	uint8_t i;
	reset();
	if(check()==0){
		for(i=0;i<5;i++){
			buffer[i]= read_byte();
		}
		if((buffer[0]+buffer[1]+buffer[2]+buffer[3])==buffer[4]){ 
			*humidity = buffer[0];
			*temperature = buffer[2];
		}
	}else{
		return 1;
	}
	return 0;
}

