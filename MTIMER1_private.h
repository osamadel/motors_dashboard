#ifndef MTIMER1_PRIVATE_H_
#define MTIMER1_PRIVATE_H_

	#define TCCR1A		*((volatile uint8 *)(0x4F))
	#define TCCR1B		*((volatile uint8 *)(0x4E))
	#define TCNT1H		*((volatile uint8 *)(0x4D))
	#define TCNT1L		*((volatile uint8 *)(0x4C))
	#define OCR1AH		*((volatile uint8 *)(0x4B))
	#define OCR1AL		*((volatile uint8 *)(0x4A))
	#define OCR1BH		*((volatile uint8 *)(0x49))
	#define OCR1BL		*((volatile uint8 *)(0x48))
	#define ICR1H		*((volatile uint8 *)(0x47))
	#define ICR1L		*((volatile uint8 *)(0x46))

	#define TIMSK		*((volatile uint8 *)(0x59))
	#define TIFR		*((volatile uint8 *)(0x58))
	#define SREG		*((volatile uint8 *)(0x5F))

	#define MTIMER2_RESOLUTION 0x10000

//	void __vector_11(void) __attribute__ ((signal, used));
//	void __vector_10(void) __attribute__ ((signal, used));
//	void __vector_9(void) __attribute__ ((signal, used));
	void __vector_7(void) __attribute__ ((signal, used));

//	void (* OVfuncPtr) (void) = (void *) 0;

#endif
