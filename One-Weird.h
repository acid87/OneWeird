// One Wire protocol implementation by 4c1d.
//

#ifndef OneWeird_h
#define OneWeird_h
  

#define SENSOR_PORT PB2
#define LED_PORT PB1
#define SAMPLE_PORT PB3


unsigned char oneWire_initilization(void);
void oneWire_write_slot(const unsigned char bit);
unsigned char oneWire_read_slot(void);
void oneWire_write_command(const unsigned char command);





#endif
