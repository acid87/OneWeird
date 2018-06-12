// One Wire protocol implementation by 4c1d.
//

#ifndef OneWeird_h
#define OneWeird_h
  

#define SENSOR_PORT PB2
#define LED_PORT PB1
#define SAMPLE_PORT PB3

typedef enum { false, true } bool;
typedef enum { HIGH, LOW } bit_t;


bool oneWire_initilization(void);
bool oneWire_write_slot(const unsigned char bit);
bit_t oneWire_read_slot(void);
bool oneWire_write_command(const unsigned char command);





#endif
