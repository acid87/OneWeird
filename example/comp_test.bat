avr-gcc -Wall -Os -mmcu=atmega328p -c -o ..\One-Weird.o ..\One-Weird.c
avr-gcc -Wall -Os -mmcu=atmega328p -c -o test_lib.o test_lib.c
avr-gcc -mmcu=atmega328p test_lib.o ..\One-Weird.o -o test_lib
avr-objcopy -O ihex -R .eeprom test_lib test_lib.hex