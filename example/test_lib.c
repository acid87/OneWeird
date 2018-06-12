
#define F_CPU 16000000  

#include <avr/io.h>
#include <util/delay.h>

#include "..\One-Weird.h"

int i;

int main(void)
{
    DDRB |= (1 << SENSOR_PORT) | (1 << LED_PORT) | (1 << SAMPLE_PORT); 
    PORTB &= ~(1 << SAMPLE_PORT);

    for(;;)
    {
    	_delay_ms(100);        
       
    	oneWire_initilization();
		oneWire_write_command(0xCC);
		oneWire_write_command(0x44);    	
		_delay_ms(500);
		_delay_ms(500);

        oneWire_initilization();
        oneWire_write_command(0xCC);
        PORTB |= (1 << LED_PORT);
    	oneWire_write_command(0xBE);
    	PORTB &= ~(1 << LED_PORT);

    
    	
    	_delay_us(10);
		PORTB |= (1 << LED_PORT);	
    	for(i = 0; i < 16; i++ )
    	{
    		oneWire_read_slot();
    		_delay_us(1);
    	}
    	
    	PORTB &= ~(1 << LED_PORT);


    }

    return 0; 
}