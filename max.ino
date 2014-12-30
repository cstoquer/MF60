/* code for max 7219 from maxim */

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


int MAX_DATA  = 2;
int MAX_LOAD  = 3;
int MAX_CLOCK = 4;


void putByte(byte data) {
	byte i = 8;
	byte mask;
	while (i > 0) {
		mask = 0x01 << (i - 1);      // get bitmask
		digitalWrite( MAX_CLOCK, LOW);   // tick
		if (data & mask){            // choose bit
			digitalWrite(MAX_DATA, HIGH);// send 1
		} else {
			digitalWrite(MAX_DATA, LOW); // send 0
		}
		digitalWrite(MAX_CLOCK, HIGH);   // tock
		--i;                         // move to lesser bit
	}
}

void maxSingle(byte reg, byte col) {    
	digitalWrite(MAX_LOAD, LOW);   // begin     
	putByte(reg);                  // specify register
	putByte(col);                  // put data   
	digitalWrite(MAX_LOAD,HIGH);   // and load
}

void setupMax() {
	pinMode(MAX_DATA,  OUTPUT);
	pinMode(MAX_CLOCK, OUTPUT);
	pinMode(MAX_LOAD,  OUTPUT);

	// initiation of the max 7219
	maxSingle(MAX7219_REG_scanLimit,   0x07);      
	maxSingle(MAX7219_REG_decodeMode,  0x00); // using an led matrix (not digits)
	maxSingle(MAX7219_REG_shutdown,    0x01); // not in shutdown mode
	maxSingle(MAX7219_REG_displayTest, 0x00); // no display test

	for (int i = 1; i <= 8; ++i)  maxSingle(i, 0);  // empty registers, turn all LEDs off

	maxSingle(MAX7219_REG_intensity, 0x0f);   // range: 0x00 to 0x0f
}

void setup () {
	setupMax();
	// digitalWrite(13, HIGH);  
	// beginSerial(9600);
}

void loop () {


	//------------ MAX LIGHT SHOW --------------

	/*
	maxSingle(1,1);    //  █ ░ ░ ░ ░ ░ ░ ░
	maxSingle(2,2);    //  ░ █ ░ ░ ░ ░ ░ ░
	maxSingle(3,4);    //  ░ ░ █ ░ ░ ░ ░ ░
	maxSingle(4,8);    //  ░ ░ ░ █ ░ ░ ░ ░
	maxSingle(5,16);   //  ░ ░ ░ ░ █ ░ ░ ░
	maxSingle(6,32);   //  ░ ░ ░ ░ ░ █ ░ ░
	maxSingle(7,64);   //  ░ ░ ░ ░ ░ ░ █ ░
	maxSingle(8,128);  //  ░ ░ ░ ░ ░ ░ ░ █

	delay(1000);

	maxSingle(1,1);    //  █ ░ ░ ░ ░ ░ ░ ░
	maxSingle(2,3);    //  █ █ ░ ░ ░ ░ ░ ░
	maxSingle(3,7);    //  █ █ █ ░ ░ ░ ░ ░
	maxSingle(4,15);   //  █ █ █ █ ░ ░ ░ ░
	maxSingle(5,31);   //  █ █ █ █ █ ░ ░ ░
	maxSingle(6,63);   //  █ █ █ █ █ █ ░ ░
	maxSingle(7,127);  //  █ █ █ █ █ █ █ ░
	maxSingle(8,255);  //  █ █ █ █ █ █ █ █

	delay(1000);
	*/

	maxSingle(1, 128);
	delay(1000);
	maxSingle(1, 64);
	delay(1000);
}
