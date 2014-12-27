#ifndef LIB_MIDI_H_
#define LIB_MIDI_H_


class MIDI_Class {
	
public:
	MIDI_Class();
	void begin(const byte inChannel = 1);
	void sendNoteOn(byte NoteNumber,byte Velocity,byte Channel);
	void sendNoteOff(byte NoteNumber,byte Velocity,byte Channel);
};

extern MIDI_Class MIDI;

#endif // LIB_MIDI_H_
