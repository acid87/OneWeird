// Version 0.01

//https://www.youtube.com/watch?v=W-qPENKa96Y



#ifndef __AVR_IO__
  #include <avr/io.h>
#endif

#ifndef _UTIL_DELAY_H_
	#include <util/delay.h>
#endif

#include "One-Weird.h"




// Funcion de inicializacion.
// Obtenemos true si el sensor responde con la señal de presencia
// false en caso contrario
bool oneWire_initilization(void)
{
	bool presence;

	PORTB &= ~(1 << SENSOR_PORT); // low signal (x0) tri state or output low
	DDRB |= (1 << SENSOR_PORT);   // (10)
	_delay_us(500);

	DDRB &= ~(1 << SENSOR_PORT);  // (00)
	_delay_us(70); // the sensor waits between 15-60 µs from the rising edge and transmit a low for 60 to 240 µs. So i have to sample 60 - 75 µs.

	presence = (( (PINB & (1 << SENSOR_PORT)) < 1) ? (true) : (false));

	_delay_us(300); // 60 (max time to wait) + 240 (max presence width)  

	return presence;
}

// writes 0 if bit is equal to 0, writes 1 if bit is other value
// 60 µs should be the minimum duration of write slot with 1 µs of recovery between write slots
bool oneWire_write_slot(const unsigned char bit)
{	

	PORTB |= (1 << SENSOR_PORT);  // high signal (x1) // pull-up enable or output high
	DDRB |= (1 << SENSOR_PORT);   // Set port as output (11) 
	_delay_us(2);

	PORTB &= ~(1 << SENSOR_PORT); // low signal			(10)
	_delay_us(10); // les than 15 µs

	if( bit == 0)
	{
		PORTB &= ~(1 << SENSOR_PORT); // low signal
		_delay_us(60);	
	}
	else
	{
		PORTB |= (1 << SENSOR_PORT);  // high signal
		_delay_us(60);
	}

	PORTB |= (1 << SENSOR_PORT);  // (11) output high
	_delay_us(2);
	return true;

}

// 60 µs should be the minimum duration of read slot with 1 µs of recovery between read slots
bit_t oneWire_read_slot(void)
{
	bit_t bit;
	PORTB &= ~(1 << SAMPLE_PORT);  // high sample port to indicate start of sampling

	PORTB |= (1 << SENSOR_PORT);  // high signal (x1) // pull-up enable or output high
	DDRB |= (1 << SENSOR_PORT);   // Set port as output (11) 
	_delay_us(2);
	
	PORTB &= ~(1 << SENSOR_PORT); // output-low (10)
	_delay_us(2);

	DDRB &= ~(1 << SENSOR_PORT);   // Set port as input tri-state (00)
	_delay_us(8); 	// sample before 15 µs after the read slot starts
	
	PORTB |= (1 << SAMPLE_PORT);
	bit = (( (PINB & (1 << SENSOR_PORT)) > 0) ? (HIGH) : (LOW));

	PORTB &= ~(1 << SAMPLE_PORT); // low sample port to indicate start of sampling

	_delay_us(60);

	//PORTB |= (1 << SENSOR_PORT);  // high signal (01) // pull-up enable
	//DDRB |= (1 << SENSOR_PORT);   // Set port as output (11) 

	return bit;
}

// writes 1 byte command ie 0x33
bool oneWire_write_command(const unsigned char command)
{
	int mask = 0;	

	for(mask=0 ; mask < 8; mask++ )
	{
		oneWire_write_slot(command & (1 << mask));	
		_delay_us(2);
	}

	return true;
}

// writes 1 byte command ie 0x33
bool oneWire_read_byte(void)
{


	return true;
}