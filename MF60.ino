#include "MIDI_debug.h"

#define PULSE_WIDTH_USEC 5
#define ANALOG_READ_RATE 50
#define DEBOUNCE_TRIGGER 8

#define CLOCK 2
#define LOAD  3

#define DATA0 4
#define DATA1 5
#define DATA2 6
#define DATA3 7


int   midiChannel = 1;

int   pinStates[64];  // state values of all 64 button pins
int   changed[64];    // a list of button with changed state in the current loop
int   debounce[64];   // debounce counter values of all 64 pins
bool  debouncing[64]; // pins currently in debounce mode


const int pinToPadMap[64] = {
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 12, 13, 14, 15, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
	61, 62, 63
};

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

void setup() {
	pinMode(LOAD,  OUTPUT);
	pinMode(CLOCK, OUTPUT);
	pinMode(DATA0, INPUT);
	pinMode(DATA1, INPUT);
	pinMode(DATA2, INPUT);
	pinMode(DATA3, INPUT);

	for (int i = 0; i < 64; ++i) {
		pinStates[i]  = LOW;
		changed[i]    = LOW;
		debounce[i]   = 0;
		debouncing[i] = false;
	}

	MIDI.begin();
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

int readButtons() {
	int nChanged = 0;
	int pin = 0;
	//-------------------------------------
	// store pin values for all shift register
	digitalWrite(LOAD, LOW);
	delayMicroseconds(PULSE_WIDTH_USEC); // TODO: here, insert some computation
	digitalWrite(LOAD, HIGH);

	while (pin < 64) {
		//-------------------------------------
		// read shift registers values
		int values[4];

		values[0] = digitalRead(DATA0);
		values[1] = digitalRead(DATA1);
		values[2] = digitalRead(DATA2);
		values[3] = digitalRead(DATA3);

//values[0] = LOW;
//values[1] = LOW;
values[2] = LOW;
values[3] = LOW;

		digitalWrite(CLOCK, HIGH);
		// delayMicroseconds(PULSE_WIDTH_USEC);

		for (int i = 0; i < 4; ++i) {
			// update and debounce value 1
			if (pinStates[pin] != values[i]) {
				// pin changed value
				pinStates[pin] = values[i];
				// switch debouncing
				// - if previously bebouncing, then it was an artefact
				// - if not, then debouncing start
				debouncing[pin] = !debouncing[pin];
				// initiate debounce counter for this pin
				debounce[pin] = 0;
			} else if (debouncing[pin]) {
				// increment debouncing counter value for this pin
				if (debounce[pin]++ == DEBOUNCE_TRIGGER) {
					// debounce is finished, button state has changed
					changed[nChanged++] = pin;
					debouncing[pin] = false;
				}
			}
			pin++;
		}
		digitalWrite(CLOCK, LOW);
	}
	return nChanged;
}


//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

void loop() {
	int nChanged = readButtons();
	if (nChanged == 0) return;
	for (int i = 0; i < nChanged; ++i) {
		if (pinStates[changed[i]]) {
			MIDI.sendNoteOn(pinToPadMap[changed[i]], 120, midiChannel);
		} else {
			MIDI.sendNoteOff(pinToPadMap[changed[i]], 0, midiChannel);
		}
	}
}
