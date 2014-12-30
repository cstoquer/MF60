#ifndef LIB_MAX_7219_H_
#define LIB_MAX_7219_H_

#define MAX7219_DATA  2
#define MAX7219_LOAD  3
#define MAX7219_CLOCK 4

#include "Arduino.h"
#include <inttypes.h>
typedef uint8_t byte;
typedef uint16_t word;

class MAX_7219_Class {
	
public:
	MAX_7219_Class();
	void begin();
	void set(byte reg, byte data);
};

extern MAX_7219_Class MAX7219;

#endif // LIB_MAX_7219_H_