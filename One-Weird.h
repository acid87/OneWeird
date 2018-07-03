// One Wire protocol implementation by 4c1d.
//

#ifndef OneWeird_h
	#define OneWeird_h
	 

	#define SENSOR_PORT PB2
	#define LED_PORT PB1
	#define SAMPLE_PORT PB3
	#define ONE_WEIRD_DEBUG 1   //comment entire line if you are not debugging



	class OneWeird
	{
	public:		
		unsigned char oneWire_initilization(void);
		void oneWire_write_slot(const unsigned char bit);
		unsigned char oneWire_read_slot(void);
		void oneWire_write_command(const unsigned char command);
		unsigned char oneWire_read_byte(void);
	};
	

	
#endif
