#ifndef HLCD_INTERFACE_H
#define HLCD_INTERFACE_H

	void HLCD_init_character			(void);
	void HLCD_clear						(void);
	void HLCD_init						(uint8);
	void HLCD_writeCMD					(uint8);
	void HLCD_writeData					(uint8);
	void HLCD_writeText					(uint8 * text);
	void HLCD_writeInt					(uint32 intNumber);
	void HLCD_setLine					(uint8 line);
	void HLCD_setCursor					(uint8 line, uint8 offset);
	void HLCD_shiftDisplay				(uint8 direction);
	void HLCD_shiftCursor				(uint8 direction, uint8 steps);
	

	#define HLCD_MODE 			HLCD_8_BIT
	#define SHIFT_LEFT			1
	#define SHIFT_RIGHT			2
	#define HLCD_8_BIT 			1
	#define HLCD_4_BIT 			0

#endif
