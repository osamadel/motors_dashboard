#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MTIMER0_private.h"
#include "MTIMER0_config.h"
#include "MTIMER0_interface.h"

void MTIMER0_voidInit(void) {
//		MDIO_SetPinDirection(PORTC, 0, OUTPUT);
	/* initializing timer mode */
	TCCR0 |= MTIMER0_MODE;

	/* initializing CTC mode */
	TCCR0 |= MTIMER0_CTC_MODE;

	/* initializing Prescaler */
	MTIMER0_u8Prescaler = MTIMER0_PRESCALER;
	if (MTIMER0_INITIAL_STATE == 1)	{
		TCCR0 &= 0b11111000;
		TCCR0 |= MTIMER0_u8Prescaler;
	}

	/* enabling global interrupts (GIE) */
	SREG = 0b10000000;

	/* initializing interrupts */
	#if (MTIMER0_OVINT_EN == 1)
		TIMSK |= 1;
	#endif
	#if (MTIMER0_CMINT_EN == 1)
		TIMSK |= 2;
	#endif
}// end MTIMER0_init


void MTIMER0_voidEnable(void) {
	// Enable code
	TCCR0 &= 0b11111000;
	TCCR0 |= MTIMER0_u8Prescaler;
}


void MTIMER0_voidDisable(void) {
	// Disable code
	TCCR0 &= 0b11111000;
}

void MTIMER0_voidSetPWMValue(uint8 Copy_u8OCR) {
	OCR0 = Copy_u8OCR;
}

void MTIMER0_voidSetDesiredTimeMs(uint32 Copy_u32TimeMs) {
	// Set desired time code
	uint32 Local_u32prescaler;
	uint32 ticktime;
	if (MTIMER0_u8Prescaler == 1) Local_u32prescaler = 1;
	else if (MTIMER0_u8Prescaler == 2) Local_u32prescaler = 8;
	else if (MTIMER0_u8Prescaler == 3) Local_u32prescaler = 64;
	else if (MTIMER0_u8Prescaler == 4) Local_u32prescaler = 256;
	else if (MTIMER0_u8Prescaler == 5) Local_u32prescaler = 1024;
	ticktime = Local_u32prescaler * 1000 / (MTIMER0_SYS_CLK / 1000000LU);
	uint32 Local_u32OverflowTime = ticktime * MTIMER0_RESOLUTION;
	MTIMER0_u32Count = (Copy_u32TimeMs * 1000000) / Local_u32OverflowTime;
	MTIMER0_u8Preload = (Copy_u32TimeMs * 1000000) % Local_u32OverflowTime;
	if (MTIMER0_u8Preload != 0) MTIMER0_u32Count++;
	#if MTIMER0_MODE == MTIMER0_NORMAL
		TCNT0 = 256 - (MTIMER0_u8Preload / ticktime);
	#elif (MTIMER0_MODE == MTIMER0_CTC)
		OCR0 = MTIMER0_u8Preload / ticktime;
	#endif
}

void MTIMER0_voidSetDesiredTimeUs(uint32 Copy_u32TimeUs) {
	// Set desired time code
	uint32 Local_u32prescaler;
	uint32 ticktime;
	if (MTIMER0_u8Prescaler == 1) Local_u32prescaler = 1;
	else if (MTIMER0_u8Prescaler == 2) Local_u32prescaler = 8;
	else if (MTIMER0_u8Prescaler == 3) Local_u32prescaler = 64;
	else if (MTIMER0_u8Prescaler == 4) Local_u32prescaler = 256;
	else if (MTIMER0_u8Prescaler == 5) Local_u32prescaler = 1024;
	ticktime = Local_u32prescaler * 1000 / (MTIMER0_SYS_CLK / 1000000LU);
	uint32 Local_u32OverflowTime = ticktime * MTIMER0_RESOLUTION;
	MTIMER0_u32Count = (Copy_u32TimeUs * 1000) / Local_u32OverflowTime;
	MTIMER0_u8Preload = (Copy_u32TimeUs * 1000) % Local_u32OverflowTime;
	if (MTIMER0_u8Preload != 0) MTIMER0_u32Count++;
	#if MTIMER0_MODE == MTIMER0_NORMAL
		TCNT0 = 256 - (MTIMER0_u8Preload / ticktime);
	#elif (MTIMER0_MODE == MTIMER0_CTC)
		OCR0 = MTIMER0_u8Preload / ticktime;
	#endif
}

void MTIMER0_voidSetCallback(void (*ptr)(void), uint8 Copy_u8CallbackEvent) {
	if (Copy_u8CallbackEvent == MTIMER0_U8_CALLBACK_OVERFLOW)
		MTIMER0_OVfuncPtr = ptr;
	else if (Copy_u8CallbackEvent == MTIMER0_U8_CALLBACK_COMPARE_MATCH)
		MTIMER0_OCfuncPtr = ptr;
}


void __vector_11(void) {
	static uint32 Local_uint32counter = 0;
	if (++Local_uint32counter == MTIMER0_u32Count) {
		MTIMER0_u8OverflowFlag = 1;
		if (MTIMER0_OVfuncPtr != (void *) 0)
			MTIMER0_OVfuncPtr();
		Local_uint32counter = 0;
		TCNT0 = 256 - MTIMER0_u8Preload;
	}

}

void __vector_10(void) {
	static uint32 Local_uint32counter = 0;
	if (++Local_uint32counter == MTIMER0_u32Count) {
		MTIMER0_u8CompareMatchFlag = 1;
		if (MTIMER0_OCfuncPtr != (void *) 0)
			MTIMER0_OCfuncPtr();
		Local_uint32counter = 0;
		OCR0 = 255;
	}

}

uint8 MTIMER0_u8GetOVF(void) {
	return MTIMER0_u8OverflowFlag;
}

uint8 MTIMER0_u8GetOCF(void) {
	return MTIMER0_u8CompareMatchFlag;
}

void MTIMER0_voidSetOVF(uint8 OVflag) {
	MTIMER0_u8OverflowFlag = OVflag;
}

void MTIMER0_voidSetOCF(uint8 OCflag) {
	MTIMER0_u8CompareMatchFlag = OCflag;
}
