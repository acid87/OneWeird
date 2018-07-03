

#ifndef F_CPU
    #define F_CPU 16000000
#endif 
#include <avr/io.h>
#include <util/delay.h>


#include "..\One-Weird.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
void get_lasered_ROM_code(unsigned char *rom_code, unsigned char *family_code, OneWeird ds);
void set_resolution(const unsigned char R1, const unsigned char R0);
/////////////////////////////////////////////////////////////////////////////////////////////////

OneWeird ds;

unsigned char low_Temp, high_Temp, th_register, tl_register, configuration_register;
unsigned char rom_code[6], family_code;


int main(void)
{
    DDRB |= (1 << SENSOR_PORT) | (1 << LED_PORT) | (1 << SAMPLE_PORT); 
    PORTB &= ~(1 << SAMPLE_PORT);

    for(;;)
    {
        _delay_ms(100);        
         
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

        
        _delay_us(10);
        PORTB |= (1 << LED_PORT);   
        
        low_Temp = ds.oneWire_read_byte();
        high_Temp = ds.oneWire_read_byte();
        th_register = ds.oneWire_read_byte();
        tl_register = ds.oneWire_read_byte();
        configuration_register = ds.oneWire_read_byte();
        PORTB &= ~(1 << LED_PORT);

        ////////////////////////////////////////////////////////////////////////////////////////////////


      get_lasered_ROM_code(&rom_code[0], &family_code,ds);


      set_resolution(1,0);

    }

    return 0;  // the program executed successfully
}

void get_lasered_ROM_code(unsigned char *rom_code, unsigned char *family_code, OneWeird ds)
{
  ds.oneWire_initilization();
  ds.oneWire_write_command(0x33); 

  *family_code = ds.oneWire_read_byte(); 
  *(rom_code + 0) = ds.oneWire_read_byte();
  *(rom_code + 1) = ds.oneWire_read_byte();
  *(rom_code + 2) = ds.oneWire_read_byte();
  *(rom_code + 3) = ds.oneWire_read_byte();
  *(rom_code + 4) = ds.oneWire_read_byte();
  *(rom_code + 5) = ds.oneWire_read_byte();
  ds.oneWire_read_byte(); // 1 byte CRC
}



void set_resolution(const unsigned char R1, const unsigned char R0)
{
  if( ( (R0 != 1 && R0 != 0)|| (R1 != 1 && R1 != 0) ) ){ return; }  // Only possible values for R0/1 is 0 or 1

  ds.oneWire_initilization();
  ds.oneWire_write_command(0xCC);
  ds.oneWire_write_command(0x4E); // Write Scratchpad command


  ds.oneWire_write_command(0xAA);
  ds.oneWire_write_command(0xBB);
  ds.oneWire_write_command((R1 << 6) | (R0 << 5) | 0); // 11 = 5, 10 = 4, 01 = 2, 00 = 0
}