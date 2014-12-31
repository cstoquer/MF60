
//███████████████████████████████████████████████████
//█████████████████████████░▄▄▄▄░█▀▄▄▄▀█▀▀░███▀▄▄▄▄▀█
//█▄░▀▄▀▀▄▀█▀▄▄▄▄▀██▄░██░▄█████▀▄████▀▄███░███░████░█
//██░██░██░█▀▄▄▄▄░████░░██████▀▄███▀▄█████░████▄▄▄▄░█
//█▀░▀█░▀█░█▄▀▀▀▄░▀█▀░██░▀████░███░▀▀▀░█▀▀░▀▀█▀▀▀▀▄██
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


#define MAX7219_DATA  10
#define MAX7219_LOAD  9
#define MAX7219_CLOCK 8


inline void Max7219_putByte(byte data) {
	/*for (byte mask = 128; mask > 0; mask >>= 1) {
		digitalWrite(MAX7219_CLOCK, LOW);
		digitalWrite(MAX7219_DATA, (data & mask) ? HIGH : LOW);
		digitalWrite(MAX7219_CLOCK, HIGH);
	}*/
	shiftOut(MAX7219_DATA, MAX7219_CLOCK, MSBFIRST, data);
}

void Max7219_write(byte reg, byte col) {    
	digitalWrite(MAX7219_LOAD, LOW);   // begin     
	Max7219_putByte(reg);                  // specify register
	Max7219_putByte(col);                  // put data   
	digitalWrite(MAX7219_LOAD,HIGH);   // and load
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

	for (int i = 1; i <= 8; ++i)  Max7219_write(i, 0);  // empty registers, turn all LEDs off

	Max7219_write(MAX7219_REG_intensity, 0x0f);   // range: 0x00 to 0x0f
}

void setup () {
	Max7219_begin();
}

void loop () {


	//------------ MAX LIGHT SHOW --------------

	/*
	Max7219_write(1,1);    //  █ ░ ░ ░ ░ ░ ░ ░
	Max7219_write(2,2);    //  ░ █ ░ ░ ░ ░ ░ ░
	Max7219_write(3,4);    //  ░ ░ █ ░ ░ ░ ░ ░
	Max7219_write(4,8);    //  ░ ░ ░ █ ░ ░ ░ ░
	Max7219_write(5,16);   //  ░ ░ ░ ░ █ ░ ░ ░
	Max7219_write(6,32);   //  ░ ░ ░ ░ ░ █ ░ ░
	Max7219_write(7,64);   //  ░ ░ ░ ░ ░ ░ █ ░
	Max7219_write(8,128);  //  ░ ░ ░ ░ ░ ░ ░ █

	delay(1000);

	Max7219_write(1,1);    //  █ ░ ░ ░ ░ ░ ░ ░
	Max7219_write(2,3);    //  █ █ ░ ░ ░ ░ ░ ░
	Max7219_write(3,7);    //  █ █ █ ░ ░ ░ ░ ░
	Max7219_write(4,15);   //  █ █ █ █ ░ ░ ░ ░
	Max7219_write(5,31);   //  █ █ █ █ █ ░ ░ ░
	Max7219_write(6,63);   //  █ █ █ █ █ █ ░ ░
	Max7219_write(7,127);  //  █ █ █ █ █ █ █ ░
	Max7219_write(8,255);  //  █ █ █ █ █ █ █ █

	delay(1000);
	*/

	Max7219_write(1, 128);
	delay(1000);
	Max7219_write(1, 64);
	delay(1000);
}
