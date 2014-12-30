#include "MIDI_debug.h"

MIDI_Class MIDI;

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
MIDI_Class::MIDI_Class() { 
	// NOOP	
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
void MIDI_Class::begin() {
	// Initialise the Serial port
	// USE_SERIAL_PORT.begin(MIDI_BAUDRATE);
	Serial.begin(9600);
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
void MIDI_Class::sendNoteOn(byte NoteNumber, byte Velocity, byte Channel) { 
	// send(NoteOn,NoteNumber,Velocity,Channel);
	Serial.print("NOTE ON ");
	Serial.print(NoteNumber);
	Serial.print(" | ");
	Serial.print(Velocity);
	Serial.print(" | ");
	Serial.print(Channel);
	Serial.print("\n");
}


//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
void MIDI_Class::sendNoteOff(byte NoteNumber, byte Velocity, byte Channel) {
	// send(NoteOff,NoteNumber,Velocity,Channel);
	Serial.print("NOTE OFF ");
	Serial.print(NoteNumber);
	Serial.print(" | ");
	Serial.print(Velocity);
	Serial.print(" | ");
	Serial.print(Channel);
	Serial.print("\n");
}

