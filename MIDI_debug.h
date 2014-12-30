#ifndef LIB_MIDI_H_
#define LIB_MIDI_H_

#include "Arduino.h"
#include <inttypes.h>
typedef uint8_t byte;
typedef uint16_t word;

class MIDI_Class {
	
public:
	MIDI_Class();
	void begin();
	void sendNoteOn(byte NoteNumber,byte Velocity,byte Channel);
	void sendNoteOff(byte NoteNumber,byte Velocity,byte Channel);
};

extern MIDI_Class MIDI;

#endif // LIB_MIDI_H_
