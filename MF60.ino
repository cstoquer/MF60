#include "MIDI_debug.h"

#define PULSE_WIDTH_USEC 5
#define ANALOG_READ_RATE 50
#define DEBOUNCE_TRIGGER 8

#define HC165_CLOCK 2
#define HC165_LOAD  3
#define HC165_DATA0 4
#define HC165_DATA1 5
#define HC165_DATA2 6
#define HC165_DATA3 7


#define MAX7219_DATA  10
#define MAX7219_LOAD  9
#define MAX7219_CLOCK 8

//███████████████████████████████████████████████████
//█████████████████████████ ▄▄▄▄ █▀▄▄▄▀█▀▀ ███▀▄▄▄▄▀█
//█▄ ▀▄▀▀▄▀█▀▄▄▄▄▀██▄ ██ ▄█████▀▄████▀▄███ ███ ████ █
//██ ██ ██ █▀▄▄▄▄ ████  ██████▀▄███▀▄█████ ████▄▄▄▄ █
//█▀ ▀█ ▀█ █▄▀▀▀▄ ▀█▀ ██ ▀████ ███ ▀▀▀ █▀▀ ▀▀█▀▀▀▀▄██
//███████████████████████████████████████████████████

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
#define MAX7219_REG_intensity   0x0a
#define MAX7219_REG_scanLimit   0x0b
#define MAX7219_REG_shutdown    0x0c
#define MAX7219_REG_displayTest 0x0f


byte Max7219_registers[8];

inline void Max7219_putByte(byte data) {
	// TODO: don't know which version is faster
	/*for (byte mask = 128; mask > 0; mask >>= 1) {
		digitalWrite(MAX7219_CLOCK, LOW);
		digitalWrite(MAX7219_DATA, (data & mask) ? HIGH : LOW);
		digitalWrite(MAX7219_CLOCK, HIGH);
	}*/
	shiftOut(MAX7219_DATA, MAX7219_CLOCK, MSBFIRST, data);
}

void Max7219_write(byte reg, byte data) {    
	digitalWrite(MAX7219_LOAD, LOW);   // begin     
	Max7219_putByte(reg);              // specify register
	Max7219_putByte(data);             // put data   
	digitalWrite(MAX7219_LOAD, HIGH);  // load
}

void Max7219_lightOn(byte led) {
	byte reg = led / 8;
	byte bit = led % 8;
	Max7219_registers[reg] |= 1 << bit;
	Max7219_write(reg + 1, Max7219_registers[reg]);
}

void Max7219_lightOff(byte led) {
	byte reg = led / 8;
	byte bit = led % 8;
	Max7219_registers[reg] &= !(1 << bit);
	Max7219_write(reg + 1, Max7219_registers[reg]);
}

void Max7219_begin() {
	pinMode(MAX7219_DATA,  OUTPUT);
	pinMode(MAX7219_CLOCK, OUTPUT);
	pinMode(MAX7219_LOAD,  OUTPUT);

	// initiation of the max 7219
	Max7219_write(MAX7219_REG_scanLimit,   0x07);      
	Max7219_write(MAX7219_REG_decodeMode,  0x00); // using an led matrix (not digits)
	Max7219_write(MAX7219_REG_shutdown,    0x01); // not in shutdown mode
	Max7219_write(MAX7219_REG_displayTest, 0x00); // no display test

	for (int i = 0; i < 8; ++i)  {
		Max7219_write(i + 1, 0);  // empty registers, turn all LEDs off
		Max7219_registers[i] = 0;
	}

	Max7219_write(MAX7219_REG_intensity, 0x0f);   // range: 0x00 to 0x0f
}

//██████████████████████████████████████████████████
//████████▄  █  ▄█▄ ▄▄▄ ██▀▄▄▄█▀▄▄▄▄▀███████████████
//█████████ ▄▀▄ ███ ▀ ███ ▀▀▀██ ██ █ ███████████████
//█████████ █▄█ ███ █▄███ ███ █ █ ██ ███████████████
//████████▀ ▀█▀ ▀█▀ ▀████▄▀▀▀▄█▄▀▀▀▀▄███████████████
//██████████████████████████████████████████████████


int   midiChannel = 1;

int   pinStates[64];     // state values of all 64 button pins
int   changed[64];       // a list of button with changed state in the current loop
int   debounceCount[64]; // debounce counter values of all 64 pins
bool  isDebouncing[64];  // is pin currently in debounce mode


const int pinToPadMap[64] = {
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 62, 63
};

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

void HC165_begin() {
	pinMode(HC165_LOAD,  OUTPUT);
	pinMode(HC165_CLOCK, OUTPUT);
	pinMode(HC165_DATA0, INPUT);
	pinMode(HC165_DATA1, INPUT);
	pinMode(HC165_DATA2, INPUT);
	pinMode(HC165_DATA3, INPUT);

	for (int i = 0; i < 64; ++i) {
		pinStates[i]     = LOW;
		changed[i]       = LOW;
		debounceCount[i] = 0;
		isDebouncing[i]  = false;
	}
}


//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

int readButtons() {
	int nChanged = 0;
	int pin = 0;
	//-------------------------------------
	// store pin values for all shift register
	digitalWrite(HC165_LOAD, LOW);
	delayMicroseconds(PULSE_WIDTH_USEC); // TODO: here, insert some computation
	digitalWrite(HC165_LOAD, HIGH);

	while (pin < 64) {
		//-------------------------------------
		// read shift registers values
		int values[4];

		values[0] = digitalRead(HC165_DATA0);
		values[1] = digitalRead(HC165_DATA1);
		values[2] = digitalRead(HC165_DATA2);
		values[3] = digitalRead(HC165_DATA3);

		//values[0] = LOW;
		values[1] = LOW;
		values[2] = LOW;
		values[3] = LOW;

		digitalWrite(HC165_CLOCK, HIGH);
		// delayMicroseconds(PULSE_WIDTH_USEC);
		// digitalWrite(HC165_CLOCK, LOW);

		for (int i = 0; i < 4; ++i) {
			// update and debounce value 1
			if (pinStates[pin] != values[i]) {
				// pin changed value
				pinStates[pin] = values[i];
				// switch isDebouncing
				// - if previously bebouncing, then it was an artefact
				// - if not, then isDebouncing start
				isDebouncing[pin] = !isDebouncing[pin];
				// initiate debounce counter for this pin
				debounceCount[pin] = 0;
			} else if (isDebouncing[pin]) {
				// increment isDebouncing counter value for this pin
				if (debounceCount[pin]++ == DEBOUNCE_TRIGGER) {
					// debounce is finished, button state has changed
					changed[nChanged++] = pin;
					isDebouncing[pin] = false;
				}
			}
			pin++;
		}
		digitalWrite(HC165_CLOCK, LOW);
	}
	return nChanged;
}

//█████████████████████████████████████████████████████
//███▄ ███████████████▄ ████████████▄██████████████████
//███ █ ███▄ ▀▄▄▄█▀▄▄▄▀ ██▄ ██▄ ██▄▄ ███▄ ▀▄▄▀██▀▄▄▄▄▀█
//███ ▀ ████ █████ ████ ███ ███ ████ ████ ███ ██ ████ █
//█▀ ▀█▀ ▀█▀ ▀▀▀██▄▀▀▀▄ ▀██▄▀▀▄ ▀█▀▀ ▀▀█▀ ▀█▀ ▀█▄▀▀▀▀▄█
//█████████████████████████████████████████████████████

void setup() {
	HC165_begin();
	Max7219_begin();
	MIDI.begin();
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

void loop() {
	int nChanged = readButtons();
	if (nChanged == 0) return;
	for (int i = 0; i < nChanged; ++i) {
		if (pinStates[changed[i]]) {
			MIDI.sendNoteOn(pinToPadMap[changed[i]], 120, midiChannel);
			Max7219_lightOn(7);
		} else {
			MIDI.sendNoteOff(pinToPadMap[changed[i]], 0, midiChannel);
			Max7219_lightOff(7);
		}
	}
}
