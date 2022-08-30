/*
 * main.c
 *
 * Created: 8/28/2022 7:04:40 PM
 *  Author: patryk
 */ 

#include <xc.h>
#include "lcd/LCD.h";
#include "sensor/sensor.h";

char* itoa(int i, char b[]){  // stole it from stackoverflow
	char const digit[] = "0123456789";
	char* p = b;
	if(i<0){
		*p++ = '-';
		i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do{ //Move back, inserting digits as u go
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}

void init_pins(){
	DDRC = 0b00111000;
	DDRD = 0x0F; // why this is not working ?
 }


int main(void)
{
	init_pins(); 
	init_lcd();
	uint8_t temperature;
	uint8_t humidity;
	char temperature_str[3];
	char humidity_str[2];
    while(1)
    {
		temperature=0;
		humidity=0;
		read_data(&temperature,&humidity);
		itoa(temperature,temperature_str);
		itoa(humidity,humidity_str);
		write("temperature: ");
		write(temperature_str);
		send_letter(0b11011111);
		command(jump_second_line);
		write("humidity: ");
		write(humidity_str);
		write("%");
		_delay_ms(8000);
		command(clear_display);
	}
}