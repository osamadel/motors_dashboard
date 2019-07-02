#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MTIMER2_private.h"
#include "MTIMER2_config.h"
#include "MTIMER2_interface.h"

void MTIMER2_voidInit(void) {
//		MDIO_SetPinDirection(PORTC, 0, OUTPUT);
	/* initializing timer mode */
	TCCR2 |= MTIMER2_MODE;

	/* initializing CTC mode */
	TCCR2 |= MTIMER2_CTC_MODE;

	/* initializing Prescaler */
	MTIMER2_u8Prescaler = MTIMER2_PRESCALER;
	#if MTIMER2_INITIAL_STATE == 1
		TCCR2 &= 0b11111000;
		TCCR2 |= MTIMER2_u8Prescaler;
	#endif

	/* enabling global interrupts (GIE) */
	SREG = 0b10000000;

	/* initializing interrupts */
	#if (MTIMER2_OVINT_EN == 1)
		SET_BIT(TIMSK, 6);
	#endif
	#if (MTIMER2_CMINT_EN == 1)
		SET_BIT(TIMSK, 7);
	#endif
}// end MTIMER0_init


void MTIMER2_voidEnable(void) {
	// Enable code
	TCCR2 &= 0b11111000;
	TCCR2 |= MTIMER2_u8Prescaler;
}


void MTIMER2_voidDisable(void) {
	// Disable code
	TCCR2 &= 0b11111000;
}

void MTIMER2_voidSetPWMValue(uint8 Copy_u8OCR) {
	OCR2 = Copy_u8OCR;
}

void MTIMER2_voidSetDesiredTimeMs(uint32 Copy_u32TimeMs) {
	// Set desired time code
	uint32 Local_u32prescaler;
	uint32 ticktime;
	if (MTIMER2_u8Prescaler == 1) Local_u32prescaler = 1;
	else if (MTIMER2_u8Prescaler == 2) Local_u32prescaler = 8;
	else if (MTIMER2_u8Prescaler == 3) Local_u32prescaler = 64;
	else if (MTIMER2_u8Prescaler == 4) Local_u32prescaler = 256;
	else if (MTIMER2_u8Prescaler == 5) Local_u32prescaler = 1024;
	ticktime = Local_u32prescaler * 1000 / (MTIMER2_SYS_CLK / 1000000LU);
	uint32 Local_u32OverflowTime = ticktime * MTIMER2_RESOLUTION;
	MTIMER2_u32Count = (Copy_u32TimeMs * 1000000) / Local_u32OverflowTime;
	MTIMER2_u8Preload = (Copy_u32TimeMs * 1000000) % Local_u32OverflowTime;
	if (MTIMER2_u8Preload != 0) MTIMER2_u32Count++;
	#if MTIMER2_MODE == MTIMER2_NORMAL
		TCNT2 = 256 - (MTIMER2_u8Preload / ticktime);
	#elif (MTIMER2_MODE == MTIMER2_CTC)
		OCR2 = MTIMER2_u8Preload / ticktime;
	#endif
}

void MTIMER2_voidSetDesiredTimeUs(uint32 Copy_u32TimeUs) {
	// Set desired time code
	uint32 Local_u32prescaler;
	uint32 ticktime;
	if (MTIMER2_u8Prescaler == 1) Local_u32prescaler = 1;
	else if (MTIMER2_u8Prescaler == 2) Local_u32prescaler = 8;
	else if (MTIMER2_u8Prescaler == 3) Local_u32prescaler = 64;
	else if (MTIMER2_u8Prescaler == 4) Local_u32prescaler = 256;
	else if (MTIMER2_u8Prescaler == 5) Local_u32prescaler = 1024;
	ticktime = Local_u32prescaler * 1000 / (MTIMER2_SYS_CLK / 1000000LU);
	uint32 Local_u32OverflowTime = ticktime * MTIMER2_RESOLUTION;
	MTIMER2_u32Count = (Copy_u32TimeUs * 1000) / Local_u32OverflowTime;
	MTIMER2_u8Preload = (Copy_u32TimeUs * 1000) % Local_u32OverflowTime;
	if (MTIMER2_u8Preload != 0) MTIMER2_u32Count++;
	#if MTIMER2_MODE == MTIMER2_NORMAL
		TCNT2 = 256 - (MTIMER2_u8Preload / ticktime);
	#elif (MTIMER2_MODE == MTIMER2_CTC)
		OCR2 = MTIMER2_u8Preload / ticktime;
	#endif
}

void MTIMER2_voidSetCallback(void (*ptr)(void), uint8 Copy_u8CallbackEvent) {
	if (Copy_u8CallbackEvent == MTIMER2_U8_CALLBACK_OVERFLOW)
		MTIMER2_OVfuncPtr = ptr;
	else if (Copy_u8CallbackEvent == MTIMER2_U8_CALLBACK_COMPARE_MATCH)
		MTIMER2_OCfuncPtr = ptr;
}


void __vector_5(void) {
	static uint32 Local_uint32counter = 0;
	if (++Local_uint32counter == MTIMER2_u32Count) {
		MTIMER2_u8OverflowFlag = 1;
		if (MTIMER2_OVfuncPtr != (void *) 0)
			MTIMER2_OVfuncPtr();
		Local_uint32counter = 0;
		TCNT2 = 256 - MTIMER2_u8Preload;
	}

}

void __vector_4(void) {
	static uint32 Local_uint32counter = 0;
	if (++Local_uint32counter == MTIMER2_u32Count) {
		MTIMER2_u8CompareMatchFlag = 1;
		if (MTIMER2_OCfuncPtr != (void *) 0)
			MTIMER2_OCfuncPtr();
		Local_uint32counter = 0;
		OCR2 = 255;
	}

}

uint8 MTIMER2_u8GetOVF(void) {
	return MTIMER2_u8OverflowFlag;
}

uint8 MTIMER2_u8GetOCF(void) {
	return MTIMER2_u8CompareMatchFlag;
}

void MTIMER2_voidSetOVF(uint8 OVflag) {
	MTIMER2_u8OverflowFlag = OVflag;
}

void MTIMER2_voidSetOCF(uint8 OCflag) {
	MTIMER2_u8CompareMatchFlag = OCflag;
}
