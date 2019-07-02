#ifndef _MTIMER0_CONFIG_H_
#define _MTIMER0_CONFIG_H_

/********************************************************/
/* Timer0 Configurations */
#define MTIMER0_PRESCALER			MTIMER0_8_PRESCALER
#define MTIMER0_MODE				MTIMER0_PWM_FAST_PWM
#define MTIMER0_INITIAL_STATE		MTIMER0_DISABLED
#define MTIMER0_SYS_CLK				8000000LU
#define MTIMER0_CTC_MODE			MTIMER0_FAST_PWM_CLR_ON_CM
#define MTIMER0_OVINT_EN			1
#define MTIMER0_CMINT_EN			0


#endif
