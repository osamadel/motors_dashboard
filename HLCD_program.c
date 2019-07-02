#include "libraries/L_STD_TYPES.h"
#include "MDIO_interface.h"
#include "HLCD_private.h"
#include "HLCD_interface.h"
#include <util/delay.h>


void HLCD_init_character(void) {
	uint8 character[] = {
			0b00001010,
			0b00011111,
			0b00010101,
			0b00010001,
			0b00001010,
			0b00001010,
			0b00000100,
			0b00000000
		};
	HLCD_writeCMD(0b01000000);	// set CGRAM address
	for (char i=0; i<8; i++)
		HLCD_writeData(character[i]);	// write the new character bytes to the CGRAM
	HLCD_writeCMD(0b10000000);		// set DDRAM address to 0x00
}

void HLCD_writeText(uint8 * text) {
	for (uint8 i=0; text[i]!='\0'; i++)
		HLCD_writeData(text[i]);
	return;
}

void HLCD_writeInt (uint32 intNumber) {
	uint8 digits[11];
	uint8 digit;
	uint8 index = 1;
	do {
		digit = intNumber % 10;
		intNumber /= 10;
		digits[index] = digit;
		index++;
	} while (intNumber != 0);
	for (uint8 i=index-1; i>0; i--)
		HLCD_writeData(digits[i] + '0');
	return;
}

void HLCD_clear(void) {
	if (mode == HLCD_8_BIT)
		HLCD_writeCMD(0b00000001);
	else {
		HLCD_writeCMD(0b00000001);
		HLCD_writeCMD(0b00000001 << 4);
	}
	return;
}// end HLCD_clear

void HLCD_setLine(uint8 line) {
	HLCD_setCursor(line, 0);
	return;
}// end setLine

void HLCD_setCursor (uint8 line, uint8 offset) {
		uint8 cmd = ( (line * HLCD_LINE_2_ADDR)|(HLCD_SET_RAM_ADDR_B7) ) + offset;	// AC address is 7-bit while instruction is 8 bit, b7 is 1
		if (mode == HLCD_8_BIT)
			HLCD_writeCMD(cmd);
		else {
			HLCD_writeCMD(cmd);
			HLCD_writeCMD(cmd << 4);
		}
	return;
}

void HLCD_shiftDisplay(uint8 direction) {
	if (mode == HLCD_8_BIT) {


		if (direction == SHIFT_LEFT)
			HLCD_writeCMD(0b00011000);
		else if (direction == SHIFT_RIGHT)
			HLCD_writeCMD(0b00011100);


	}else {


		if (direction == SHIFT_LEFT) {
			HLCD_writeCMD(0b00011000);
			HLCD_writeCMD(0b00011000 << 4);
		}
		else if (direction == SHIFT_RIGHT) {
			HLCD_writeCMD(0b00011100);
			HLCD_writeCMD(0b00011100 << 4);
		}


	}
	return;
}// end HLCD_shiftDisplay

void HLCD_shiftCursor(uint8 direction, uint8 steps) {


	if (mode == HLCD_8_BIT) {


		if (direction == SHIFT_LEFT)
			for (uint8 i=0; i<steps; i++)
				HLCD_writeCMD(0b00010000);
		else if (direction == SHIFT_RIGHT)
			for (uint8 i=0; i<steps; i++)
				HLCD_writeCMD(0b00010100);



	}else{


		if (direction == SHIFT_LEFT) {
			for (uint8 i=0; i<steps; i++) {
				HLCD_writeCMD(0b00010000);
				HLCD_writeCMD(0b00010000 << 4);
			}
		}else if (direction == SHIFT_RIGHT) {
			for (uint8 i=0; i<steps; i++) {
				HLCD_writeCMD(0b00010100);
				HLCD_writeCMD(0b00010100 << 4);
			}
		}



	}
	return;
}// end

void HLCD_init(uint8 m) {
	mode = m;
	// set PORTA as OUTPUT
	if (mode == HLCD_8_BIT) {
		MDIO_SetPinDirection(HLCD_D0, OUTPUT);
		MDIO_SetPinDirection(HLCD_D1, OUTPUT);
		MDIO_SetPinDirection(HLCD_D2, OUTPUT);
		MDIO_SetPinDirection(HLCD_D3, OUTPUT);
	}
	MDIO_SetPinDirection(HLCD_D4, OUTPUT);
	MDIO_SetPinDirection(HLCD_D5, OUTPUT);
	MDIO_SetPinDirection(HLCD_D6, OUTPUT);
	MDIO_SetPinDirection(HLCD_D7, OUTPUT);
	// set RW as OUTPUT
	MDIO_SetPinDirection(HLCD_RW, OUTPUT);
	// set RS as OUTPUT
	MDIO_SetPinDirection(HLCD_RS, OUTPUT);
	// set E as OUTPUT
	MDIO_SetPinDirection(HLCD_E, OUTPUT);

	// set E to (0)
	MDIO_SetPinOutput(HLCD_E, LOW);
	// start init
	_delay_ms(50);
	if (mode == HLCD_8_BIT) {
		HLCD_writeCMD(0b00111000); // set LCD to 8-bit mode, 2 lines, 5x10 font size
		_delay_ms(1);
		HLCD_writeCMD(0b00001111); // set LCD display ON, cursor ON, cursor blink ON
		_delay_ms(1);
		HLCD_writeCMD(0b00000001); // clear LCD display
		_delay_ms(2);
		HLCD_writeCMD(0b00000110); // set Address Counter to increasing, NO display shift
	} else {
		HLCD_writeCMD(0b00101000); // set LCD to 4-bit mode, 2 lines, 5x10 font size
		HLCD_writeCMD(0b00101000);
		HLCD_writeCMD(0b00101000 << 4);
		_delay_ms(1);
		HLCD_writeCMD(0b00001111); // set LCD display ON, cursor ON, cursor blink ON
		HLCD_writeCMD(0b00001111 << 4);
		_delay_ms(1);
		HLCD_writeCMD(0b00000001); // clear LCD display
		HLCD_writeCMD(0b00000001 << 4);
		_delay_ms(2);
		HLCD_writeCMD(0b00000110); // set Address Counter to increasing, NO display shift
		HLCD_writeCMD(0b00000110 << 4);
	}
	return;
}// end HLCD_init

//LCD in 8-bit mode
void HLCD_writeCMD(uint8 cmd) {
	MDIO_SetPinOutput(HLCD_RS, LOW);		// set RS to 0 (Command Reg)
	MDIO_SetPinOutput(HLCD_RW, LOW);		// Set RW to 0

	MDIO_SetPortValue(HLCD_PORT, cmd);		// Write the command to D0-D7

	MDIO_SetPinOutput(HLCD_E, HIGH);		// Set E to 1 (Read Data)
	_delay_ms(2);							// delay 2ms
	MDIO_SetPinOutput(HLCD_E, LOW);			// Set E to 0 (falling edge: Write Data)
	return;
}// end HLCD_writeCMD

void HLCD_writeData(uint8 data) {
	MDIO_SetPinOutput(HLCD_RS, HIGH);		// set RS to 1 (Data Reg)
	MDIO_SetPinOutput(HLCD_RW, LOW); 		// Set RW to 0

	if (mode == HLCD_8_BIT) {
		MDIO_SetPortValue(HLCD_PORT, data);	// Write the data to D0-D7
		MDIO_SetPinOutput(HLCD_E, HIGH); 		// Set E to 1 (Read Data)
		_delay_ms(2);							// delay 2ms
		MDIO_SetPinOutput(HLCD_E, LOW); 		// Set E to 0 (falling edge: Write Data)

	}else{
		MDIO_SetPortValue(HLCD_PORT, data & 0xF0);	// Write the Hdata to D4-D7
		MDIO_SetPinOutput(HLCD_E, HIGH); 		// Set E to 1 (Read Data)
		_delay_ms(2);							// delay 2ms
		MDIO_SetPinOutput(HLCD_E, LOW); 		// Set E to 0 (falling edge: Write Data)

		MDIO_SetPortValue(HLCD_PORT, (data << 4) & 0xF0);	// Write the Ldata to D4-D7
		MDIO_SetPinOutput(HLCD_E, HIGH); 		// Set E to 1 (Read Data)
		_delay_ms(2);							// delay 2ms
		MDIO_SetPinOutput(HLCD_E, LOW); 		// Set E to 0 (falling edge: Write Data)
	}
	return;
} // end HLCD_writeData
