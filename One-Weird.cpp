// Version 0.01

//https://www.youtube.com/watch?v=W-qPENKa96Y



#ifndef __AVR_IO__
  #include <avr/io.h>
#endif

#ifndef _UTIL_DELAY_H_
	#ifndef F_CPU
    	#define F_CPU 16000000
	#endif 
	#include <util/delay.h>
#endif

#include "One-Weird.h"




	// Funcion de inicializacion.
	// Obtenemos 1 si el sensor responde con la señal de presencia
	// 0 en caso contrario
	unsigned char OneWeird::oneWire_initilization(void)
	{
		unsigned char presence;

		PORTB &= ~(1 << SENSOR_PORT); // low signal (x0) tri state or output low
		DDRB |= (1 << SENSOR_PORT);   // (10)
		_delay_us(500);

		DDRB &= ~(1 << SENSOR_PORT);  // (00)
		_delay_us(70); // the sensor waits between 15-60 µs from the rising edge and transmit a low for 60 to 240 µs. So i have to sample 60 - 75 µs.

		presence = (( (PINB & (1 << SENSOR_PORT)) < 1) ? (1) : (0));

		_delay_us(300); // 60 (max time to wait) + 240 (max presence width)  

		return presence;
	}

	// writes 0 if bit is equal to 0, writes 1 if bit is other value
	// 60 µs should be the minimum duration of write slot with 1 µs of recovery between write slots
	void OneWeird::oneWire_write_slot(const unsigned char bit)
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

	}

	// 60 µs should be the minimum duration of read slot with 1 µs of recovery between read slots
	unsigned char OneWeird::oneWire_read_slot(void)
	{
		unsigned char bit;

		#ifdef ONE_WEIRD_DEBUG
		PORTB &= ~(1 << SAMPLE_PORT);  // high sample port to indicate start of sampling
		#endif

		PORTB |= (1 << SENSOR_PORT);  // high signal (x1) // pull-up enable or output high
		DDRB |= (1 << SENSOR_PORT);   // Set port as output (11) 
		_delay_us(2);
		
		PORTB &= ~(1 << SENSOR_PORT); // output-low (10)
		_delay_us(2);

		DDRB &= ~(1 << SENSOR_PORT);   // Set port as input tri-state (00)
		_delay_us(8); 	// sample before 15 µs after the read slot starts
		
		#ifdef ONE_WEIRD_DEBUG
			PORTB |= (1 << SAMPLE_PORT);
		#endif
		bit = (( (PINB & (1 << SENSOR_PORT)) > 0) ? (1) : (0));
		#ifdef ONE_WEIRD_DEBUG
		PORTB &= ~(1 << SAMPLE_PORT); // low sample port to indicate start of sampling
		#endif
		_delay_us(60);

		//PORTB |= (1 << SENSOR_PORT);  // high signal (01) // pull-up enable
		//DDRB |= (1 << SENSOR_PORT);   // Set port as output (11) 

		return bit;
	}

	// writes 1 byte command ie 0x33
	void OneWeird::oneWire_write_command(const unsigned char command)
	{
		int mask = 0;	

		for(mask=0 ; mask < 8; mask++ )
		{
			oneWire_write_slot(command & (1 << mask));	
			_delay_us(2);
		}

	}

	// Reads 1 byte
	unsigned char OneWeird::oneWire_read_byte(void)
	{
		int i = 0;
		for(i = 0; i < 8; i++ )
        {
            oneWire_read_slot();
            _delay_us(1);
        }

        return 0xaa;
	}

