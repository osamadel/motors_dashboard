/*
 * HSTEPEER_interface.h
 *
 *  Created on: Jun 30, 2019
 *      Author: osama
 */

#ifndef HSTEPEER_INTERFACE_H_
#define HSTEPEER_INTERFACE_H_

void HStepper_voidInit(void);

void HStepper_voidStep(uint8 direction);

void HStepper_voidRotate(uint16 angle, uint8 direction);

#define HStepper_CW			1
#define HStepper_CCW		0

#endif /* HSTEPEER_INTERFACE_H_ */
