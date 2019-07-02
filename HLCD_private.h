#ifndef HLCD_PRIVATE_H
#define HLCD_PRIVATE_H

	#define HLCD_RS 				PORTD, 0
	#define HLCD_RW 				PORTD, 1
	#define HLCD_E 					PORTD, 2
	#define HLCD_PORT				PORTA
	#define HLCD_D0 				PORTA, 0
	#define HLCD_D1 				PORTA, 1
	#define HLCD_D2 				PORTA, 2
	#define HLCD_D3 				PORTA, 3
	#define HLCD_D4 				PORTA, 4
	#define HLCD_D5 				PORTA, 5
	#define HLCD_D6 				PORTA, 6
	#define HLCD_D7 				PORTA, 7
	#define HLCD_LINE_2_ADDR		0x40
	#define HLCD_SET_RAM_ADDR_B7	0x80

	uint8 mode = 1;


#endif
