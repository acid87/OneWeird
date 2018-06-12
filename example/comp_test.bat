avr-g++ -Wall -Os -mmcu=atmega328p -c -o ..\One-Weird.o ..\One-Weird.cpp
avr-g++ -Wall -Os -mmcu=atmega328p -c -o test_lib.o test_lib.c
avr-g++ -mmcu=atmega328p test_lib.o ..\One-Weird.o -o test_lib
avr-objcopy -O ihex -R .eeprom test_lib test_lib.hex