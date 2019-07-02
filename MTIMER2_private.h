#ifndef MTIMER_PRIVATE_H_
#define MTIMER_PRIVATE_H_

	#define TCCR2 		*((volatile uint8 *)(0x45))
	#define TCNT2		*((volatile uint8 *)(0x44))
	#define OCR2		*((volatile uint8 *)(0x43))
	#define TIMSK		*((volatile uint8 *)(0x59))
	#define TIFR		*((volatile uint8 *)(0x58))
	#define SREG		*((volatile uint8 *)(0x5F))

	#define MTIMER2_RESOLUTION 256

	void __vector_5(void) __attribute__ ((signal, used));
	void __vector_4(void) __attribute__ ((signal, used));

	void (* MTIMER2_OVfuncPtr) (void) = (void *) 0;
	void (* MTIMER2_OCfuncPtr) (void) = (void *) 0;
	uint8 MTIMER2_u8Prescaler;
	uint32 MTIMER2_u32Count;
	uint8 MTIMER2_u8Preload;
	uint8 MTIMER2_u8OverflowFlag = 0;
	uint8 MTIMER2_u8CompareMatchFlag = 0;

#endif
