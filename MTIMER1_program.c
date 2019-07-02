#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MDIO_interface.h"
#include "MTIMER1_config.h"
#include "MTIMER1_interface.h"
#include "MTIMER1_private.h"

void MTIMER1_voidInit(void) {
	/* enabling global interrupts (GIE) */
//	SREG = 0b10000000;
	TCCR1A = 0b10000010;
	TCCR1B = 0b00011000;
//	TCNT1H = 0xD8;
//	TCNT1L = 0xF0;
	ICR1H = (uint8)(20000>>8);
	ICR1L = (uint8)(20000);

	OCR1AH = (uint8)(550>>8);
	OCR1AL = (uint8)(550);

	TIMSK = 0b00000011;

}// end MTIMER0_init


void MTIMER1_voidEnable(void) {
	// Enable code
	TCCR1B &= 0b11111000;
	TCCR1B |= MTIMER1_PRESCALER;
}


void MTIMER1_voidDisable(void) {
	// Disable code
	TCCR1B &= 0b11111000;
}

/*void MTIMER0_voidSetDesiredTimeMs(uint32 Copy_u32TimeMs) {
	// Set desired time code
	uint32 Local_u32prescaler;
	uint32 Local_u32Count;
	if (MTIMER0_u8Prescaler == 1) Local_u32prescaler = 1;
	else if (MTIMER0_u8Prescaler == 2) Local_u32prescaler = 8;
	else if (MTIMER0_u8Prescaler == 3) Local_u32prescaler = 64;
	else if (MTIMER0_u8Prescaler == 4) Local_u32prescaler = 256;
	else if (MTIMER0_u8Prescaler == 5) Local_u32prescaler = 1024;

	uint32 Local_u32OverflowTime = (Local_u32prescaler * MTIMER0_RESOLUTION) / (MTIMER0_SYS_CLK / 1000000LU);
	Local_u32Count = 1000 * (Copy_u32TimeMs * 1000) / (float32)Local_u32OverflowTime;
	MTIMER0_u32Count = Local_u32Count / 1000;
	MTIMER0_u8Preload = (Local_u32Count * MTIMER0_RESOLUTION) % 1000;
	if (MTIMER0_u8Preload != 0) MTIMER0_u32Count++;
	if (MTIMER0_MODE == MTIMER0_NORMAL)
		TCNT0 = 256 - MTIMER0_u8Preload;
	else if (MTIMER0_MODE == MTIMER0_CTC)
		OCR0 = MTIMER0_u8Preload;
}*/

void MTIMER1_voidSetPWM(uint16 value) {
	value = 550 + (value * 170 / 18);
	OCR1AH = (uint8)(value>>8);
	OCR1AL = (uint8)(value);
}

void MTIMER1_voidSetCallback(void (*ptr)(void)) {
//	OVfuncPtr = ptr;
}



