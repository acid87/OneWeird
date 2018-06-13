

#ifndef F_CPU
    #define F_CPU 16000000
#endif 
#include <avr/io.h>
#include <util/delay.h>


#include "..\One-Weird.h"

int i;

OneWeird ds;

int main(void)
{
    DDRB |= (1 << SENSOR_PORT) | (1 << LED_PORT) | (1 << SAMPLE_PORT); 
    PORTB &= ~(1 << SAMPLE_PORT);

    for(;;)
    {
        _delay_ms(100);        
        //PORTB |= (1 << LED_PORT);
        //   // toggle PD5
        // _delay_ms(250);  // delay in ms, valor maximo = 260/F_CPU in MHz
        // PORTB &= ~(1 << LED_PORT);
        // _delay_ms(250);

        // // test init
        // if(oneWire_initilization() == true)
        //  PORTB |= (1 << LED_PORT);
        
        // _delay_ms(500);        
  //       PORTB |= (1 << LED_PORT);
  //       // test write slot
  //       oneWire_write_slot(0);
  //       _delay_us(1);

  //       oneWire_write_slot(1);
  //       _delay_us(1);

  //       oneWire_write_slot(1);
  //       _delay_us(1);

  //       PORTB &= ~(1 << LED_PORT);


        ////////////////////////////////////////////////////////////////////////////////////////////////
        ds.oneWire_initilization();
        ds.oneWire_write_command(0xCC);
        ds.oneWire_write_command(0x44);        
        _delay_ms(500);
        _delay_ms(500);

        ds.oneWire_initilization();
        ds.oneWire_write_command(0xCC);
        PORTB |= (1 << LED_PORT);
        ds.oneWire_write_command(0xBE);
        PORTB &= ~(1 << LED_PORT);

        //oneWire_write_command(0xBE);
        //oneWire_write_slot(1);
        //oneWire_write_slot(0);
        //_delay_us(1);
        //oneWire_write_slot(0);

        
        _delay_us(10);
        PORTB |= (1 << LED_PORT);   
        for(i = 0; i < 16; i++ )
        {
            ds.oneWire_read_slot();
            _delay_us(1);
        }
        
        PORTB &= ~(1 << LED_PORT);
        ////////////////////////////////////////////////////////////////////////////////////////////////


        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);

  //    oneWire_initilization();
        // oneWire_write_command(0x33);
         
        // PORTB |= (1 << LED_PORT);    
  //    for(i = 0; i < 16; i++ )
  //    {
  //        oneWire_read_slot();
  //        _delay_us(1);
  //    } 
  //    PORTB &= ~(1 << LED_PORT);
  //    _delay_ms(1);   
                



    }

    return 0;  // the program executed successfully
}
