#ifndef _MTIMER0_CONFIG_H_
#define _MTIMER0_CONFIG_H_

/********************************************************/
/* Timer0 Configurations */
#define MTIMER2_PRESCALER			MTIMER2_8_PRESCALER
#define MTIMER2_MODE				MTIMER2_PWM_FAST_PWM
#define MTIMER2_INITIAL_STATE		MTIMER2_DISABLED
#define MTIMER2_SYS_CLK				8000000LU
#define MTIMER2_CTC_MODE			MTIMER2_FAST_PWM_CLR_ON_CM
#define MTIMER2_OVINT_EN			1
#define MTIMER2_CMINT_EN			0


#endif
