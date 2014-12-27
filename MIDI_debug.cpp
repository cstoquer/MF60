#include "MIDI_debug.h"

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
MIDI_Class::MIDI_Class() { 
	// NOOP	
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
void MIDI_Class::begin(const byte inChannel) {
	// Initialise the Serial port
	// USE_SERIAL_PORT.begin(MIDI_BAUDRATE);
	Serial.begin(9600);
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
void MIDI_Class::sendNoteOn(byte NoteNumber, byte Velocity, byte Channel) { 
	// send(NoteOn,NoteNumber,Velocity,Channel);
	Serial.println("NOTE ON ");
	Serial.println(NoteNumber);
	Serial.println(" | ");
	Serial.println(Velocity);
	Serial.println(" | ");
	Serial.println(Channel);
	Serial.println("\n");
}


//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
void MIDI_Class::sendNoteOff(byte NoteNumber, byte Velocity, byte Channel) {
	// send(NoteOff,NoteNumber,Velocity,Channel);
	Serial.println("NOTE OFF ");
	Serial.println(NoteNumber);
	Serial.println(" | ");
	Serial.println(Velocity);
	Serial.println(" | ");
	Serial.println(Channel);
	Serial.println("\n");
}

