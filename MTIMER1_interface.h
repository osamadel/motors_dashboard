#ifndef MTIMER1_INTERFACE_H_
#define MTIMER1_INTERFACE_H_

	void MTIMER1_voidInit(void);
	void MTIMER1_voidEnable(void);
	void MTIMER1_voidDisable(void);
	void MTIMER1_voidSetCallback(void (*)(void));
	void MTIMER1_voidSetPWM(uint16 value);

	#define MTIMER1_U8_CALLBACK_OVERFLOW			0
	#define MTIMER1_U8_CALLBACK_COMPARE_MATCH		1

	/********************************************************/
	/* Macros for configuration */
	#define MTIMER1_DISABLED			0
	#define MTIMER1_ENABLED				1
	// PRESCALERS
	#define MTIMER1_NO_PRESCALER		0b001
	#define MTIMER1_8_PRESCALER			0b010
	#define MTIMER1_64_PRESCALER		0b011
	#define MTIMER1_256_PRESCALER		0b100
	#define MTIMER1_1024_PRESCALER		0b101
	// TIMER MODE
	#define MTIMER1_NORMAL				0b00000000
	#define MTIMER1_PWM_PHASE_CORRECT	0b01000000
	#define MTIMER1_CTC					0b00001000
	#define MTIMER1_PWM_FAST_PWM		0b01001000
	// COMPARE MATCH MODE
	#define MTIMER1_CTC_NORMAL			0b00000000
	#define MTIMER1_CTC_TOGGLE			0b00010000
	#define MTIMER1_CTC_CLEAR			0b00100000
	#define MTIMER1_CTC_SET				0b00110000
	/********************************************************/



#endif
