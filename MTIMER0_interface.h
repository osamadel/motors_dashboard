#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_

	void MTIMER0_voidInit(void);
	void MTIMER0_voidEnable(void);
	void MTIMER0_voidDisable(void);
	void MTIMER0_voidSetDesiredTimeMs(uint32 Copy_u32TimeMs);
	void MTIMER0_voidSetDesiredTimeUs(uint32 Copy_u32TimeUs);
	void MTIMER0_voidSetCallback(void (*)(void), uint8 Copy_u8CallbackEvent);
	void MTIMER0_voidSetPWMValue(uint8 Copy_u8OCR);
	uint8 MTIMER0_u8GetOVF(void);
	uint8 MTIMER0_u8GetOCF(void);
	void MTIMER0_voidSetOVF(uint8 OVflag);
	void MTIMER0_voidSetOCF(uint8 OCflag);

	#define MTIMER0_U8_CALLBACK_OVERFLOW			0
	#define MTIMER0_U8_CALLBACK_COMPARE_MATCH		1

	/********************************************************/
	/* Macros for configuration */
	#define MTIMER0_DISABLED						0
	#define MTIMER0_ENABLED							1
	// PRESCALERS
	#define MTIMER0_NO_PRESCALER					0b001
	#define MTIMER0_8_PRESCALER						0b010
	#define MTIMER0_64_PRESCALER					0b011
	#define MTIMER0_256_PRESCALER					0b100
	#define MTIMER0_1024_PRESCALER					0b101
	// TIMER MODE
	#define MTIMER0_NORMAL							0b00000000
	#define MTIMER0_PWM_PHASE_CORRECT				0b01000000
	#define MTIMER0_CTC								0b00001000
	#define MTIMER0_PWM_FAST_PWM					0b01001000
	// COMPARE MATCH MODE
	#define MTIMER0_CTC_NORMAL						0b00000000
	#define MTIMER0_CTC_TOGGLE						0b00010000
	#define MTIMER0_CTC_CLEAR						0b00100000
	#define MTIMER0_CTC_SET							0b00110000
	// FAST PWM MODE
	#define MTIMER0_FAST_PWM_NORMAL					0b00000000
	#define MTIMER0_FAST_PWM_CLR_ON_CM				0b00100000
	#define MTIMER0_FAST_PWM_SET_ON_CM				0b00110000
	// PHASE CORRECT PWM MODE
	#define MTIMER0_PHASECORRECT_PWM_NORMAL			0b00000000
	#define MTIMER0_PHASECORRECT_PWM_CLR_UP			0b00100000
	#define MTIMER0_PHASECORRECT_PWM_SET_UP			0b00110000
	/********************************************************/



#endif
