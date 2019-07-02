/*
 * HSTEPPER_program.c
 *
 *  Created on: Jun 30, 2019
 *      Author: osama
 */
#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MDIO_interface.h"
#include "HSTEPEER_interface.h"
#include "HSTEPPER_config.h"
#include "HSTEPPER_private.h"
#include "util/delay.h"


void HStepper_voidInit(void) {
	MDIO_SetPinDirection(HStepper_BLUE, OUTPUT);
	MDIO_SetPinDirection(HStepper_ORANGE, OUTPUT);
	MDIO_SetPinDirection(HStepper_PINK, OUTPUT);
	MDIO_SetPinDirection(HStepper_YELLOW, OUTPUT);
	return;
}

void HStepper_voidStep(uint8 direction) {
	static uint8 substep = 0;
	if (HStepper_CCW == direction ) {
		if (substep == 0) {
			MDIO_SetPinOutput(HStepper_BLUE, HIGH);
			MDIO_SetPinOutput(HStepper_PINK, LOW);
			MDIO_SetPinOutput(HStepper_YELLOW, LOW);
			MDIO_SetPinOutput(HStepper_ORANGE, LOW);
			substep++;
		} else if (substep == 1) {
			MDIO_SetPinOutput(HStepper_BLUE, LOW);
			MDIO_SetPinOutput(HStepper_PINK, HIGH);
			MDIO_SetPinOutput(HStepper_YELLOW, LOW);
			MDIO_SetPinOutput(HStepper_ORANGE, LOW);
			substep++;
		} else if (substep == 2) {
			MDIO_SetPinOutput(HStepper_BLUE, LOW);
			MDIO_SetPinOutput(HStepper_PINK, LOW);
			MDIO_SetPinOutput(HStepper_YELLOW, HIGH);
			MDIO_SetPinOutput(HStepper_ORANGE, LOW);
			substep++;
		} else if (substep == 3) {
			MDIO_SetPinOutput(HStepper_BLUE, LOW);
			MDIO_SetPinOutput(HStepper_PINK, LOW);
			MDIO_SetPinOutput(HStepper_YELLOW, LOW);
			MDIO_SetPinOutput(HStepper_ORANGE, HIGH);
			substep = 0;
		}
	} else if (HStepper_CW == direction) {
		if (substep == 0) {
			MDIO_SetPinOutput(HStepper_BLUE, LOW);
			MDIO_SetPinOutput(HStepper_PINK, LOW);
			MDIO_SetPinOutput(HStepper_YELLOW, LOW);
			MDIO_SetPinOutput(HStepper_ORANGE, HIGH);
			substep++;
		} else if (substep == 1) {
			MDIO_SetPinOutput(HStepper_BLUE, LOW);
			MDIO_SetPinOutput(HStepper_PINK, LOW);
			MDIO_SetPinOutput(HStepper_YELLOW, HIGH);
			MDIO_SetPinOutput(HStepper_ORANGE, LOW);
			substep++;
		} else if (substep == 2) {
			MDIO_SetPinOutput(HStepper_BLUE, LOW);
			MDIO_SetPinOutput(HStepper_PINK, HIGH);
			MDIO_SetPinOutput(HStepper_YELLOW, LOW);
			MDIO_SetPinOutput(HStepper_ORANGE, LOW);
			substep++;
		} else if (substep == 3) {
			MDIO_SetPinOutput(HStepper_BLUE, HIGH);
			MDIO_SetPinOutput(HStepper_PINK, LOW);
			MDIO_SetPinOutput(HStepper_YELLOW, LOW);
			MDIO_SetPinOutput(HStepper_ORANGE, LOW);
			substep = 0;
		}
	}
	return;
}

void HStepper_voidRotate(uint16 angle, uint8 direction) {
	for (uint16 i = 0; i < 4 * angle / HStepper_STEPANGLE; i++) {
		HStepper_voidStep(direction);
		_delay_ms(2);
	}
	return;
}
