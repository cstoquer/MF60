#include "Arduino.h"
#include "MAX7219.h"

#define MAX7219_REG_noop        0x00
#define MAX7219_REG_digit0      0x01
#define MAX7219_REG_digit1      0x02
#define MAX7219_REG_digit2      0x03
#define MAX7219_REG_digit3      0x04
#define MAX7219_REG_digit4      0x05
#define MAX7219_REG_digit5      0x06
#define MAX7219_REG_digit6      0x07
#define MAX7219_REG_digit7      0x08
#define MAX7219_REG_decodeMode  0x09
#define MAX7219_REG_intensity   0x0A
#define MAX7219_REG_scanLimit   0x0B
#define MAX7219_REG_shutdown    0x0C
#define MAX7219_REG_displayTest 0x0F


MAX_7219_Class MAX7219;

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
MAX_7219_Class::MAX_7219_Class() { 
	// NOOP	
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
/*inline void maxPutByte(byte data) {
	for (byte mask = 128; mask > 0; mask >>= 1) {
		digitalWrite(MAX7219_CLOCK, LOW);
		digitalWrite(MAX7219_DATA, (data & mask) ? HIGH : LOW);
		digitalWrite(MAX7219_CLOCK, HIGH);
	}
}*/

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
void MAX_7219_Class::set(byte reg, byte data) { 
	digitalWrite(MAX7219_LOAD, LOW);
	/*
	maxPutByte(reg);  // specify register
	maxPutByte(data); // put data
	*/
	shiftOut(MAX7219_DATA, MAX7219_CLOCK, MSBFIRST, reg);
	shiftOut(MAX7219_DATA, MAX7219_CLOCK, MSBFIRST, data);
	digitalWrite(MAX7219_LOAD,HIGH);
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
void MAX_7219_Class::begin() {
	pinMode(MAX7219_DATA,  OUTPUT);
	pinMode(MAX7219_CLOCK, OUTPUT);
	pinMode(MAX7219_LOAD,  OUTPUT);

	// initiation of the max 7219
	set(MAX7219_REG_scanLimit,   0x07);      
	set(MAX7219_REG_decodeMode,  0x00); // using an led matrix (not digits)
	set(MAX7219_REG_shutdown,    0x01); // not in shutdown mode
	set(MAX7219_REG_displayTest, 0x00); // no display test

	for (int i = 1; i <= 8; ++i) set(i, 0);  // empty registers, turn all LEDs off

	set(MAX7219_REG_intensity,   0x0F);   // range: 0x00 to 0x0F
}
