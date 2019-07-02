#ifndef MTIMER_PRIVATE_H_
#define MTIMER_PRIVATE_H_

	#define TCCR0 		*((volatile uint8 *)(0x53))
	#define TCNT0		*((volatile uint8 *)(0x52))
	#define OCR0		*((volatile uint8 *)(0x5C))
	#define TIMSK		*((volatile uint8 *)(0x59))
	#define TIFR		*((volatile uint8 *)(0x58))
	#define SREG		*((volatile uint8 *)(0x5F))

	#define MTIMER0_RESOLUTION 256

	void __vector_11(void) __attribute__ ((signal, used));
	void __vector_10(void) __attribute__ ((signal, used));

	void (* MTIMER0_OVfuncPtr) (void) = (void *) 0;
	void (* MTIMER0_OCfuncPtr) (void) = (void *) 0;
	uint8 MTIMER0_u8Prescaler;
	uint32 MTIMER0_u32Count;
	uint8 MTIMER0_u8Preload;
	uint8 MTIMER0_u8OverflowFlag = 0;
	uint8 MTIMER0_u8CompareMatchFlag = 0;

#endif
