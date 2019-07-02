#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_

	void MTIMER2_voidInit(void);
	void MTIMER2_voidEnable(void);
	void MTIMER2_voidDisable(void);
	void MTIMER2_voidSetDesiredTimeMs(uint32 Copy_u32TimeMs);
	void MTIMER2_voidSetDesiredTimeUs(uint32 Copy_u32TimeUs);
	void MTIMER2_voidSetCallback(void (*)(void), uint8 Copy_u8CallbackEvent);
	void MTIMER2_voidSetPWMValue(uint8 Copy_u8OCR);
	uint8 MTIMER2_u8GetOVF(void);
	uint8 MTIMER2_u8GetOCF(void);
	void MTIMER2_voidSetOVF(uint8 OVflag);
	void MTIMER2_voidSetOCF(uint8 OCflag);

	#define MTIMER2_U8_CALLBACK_OVERFLOW			0
	#define MTIMER2_U8_CALLBACK_COMPARE_MATCH		1

	/********************************************************/
	/* Macros for configuration */
	#define MTIMER2_DISABLED						0
	#define MTIMER2_ENABLED							1
	// PRESCALERS
	#define MTIMER2_NO_PRESCALER					0b001
	#define MTIMER2_8_PRESCALER						0b010
	#define MTIMER2_64_PRESCALER					0b011
	#define MTIMER2_256_PRESCALER					0b100
	#define MTIMER2_1024_PRESCALER					0b101
	// TIMER MODE
	#define MTIMER2_NORMAL							0b00000000
	#define MTIMER2_PWM_PHASE_CORRECT				0b01000000
	#define MTIMER2_CTC								0b00001000
	#define MTIMER2_PWM_FAST_PWM					0b01001000
	// COMPARE MATCH MODE
	#define MTIMER2_CTC_NORMAL						0b00000000
	#define MTIMER2_CTC_TOGGLE						0b00010000
	#define MTIMER2_CTC_CLEAR						0b00100000
	#define MTIMER2_CTC_SET							0b00110000
	// FAST PWM MODE
	#define MTIMER2_FAST_PWM_NORMAL					0b00000000
	#define MTIMER2_FAST_PWM_CLR_ON_CM				0b00100000
	#define MTIMER2_FAST_PWM_SET_ON_CM				0b00110000
	// PHASE CORRECT PWM MODE
	#define MTIMER2_PHASECORRECT_PWM_NORMAL			0b00000000
	#define MTIMER2_PHASECORRECT_PWM_CLR_UP			0b00100000
	#define MTIMER2_PHASECORRECT_PWM_SET_UP			0b00110000
	/********************************************************/



#endif
