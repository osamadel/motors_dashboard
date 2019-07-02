#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MDIO_interface.h"
#include "HKeyPad_interface.h"
#include "HLCD_interface.h"
#include "MTIMER2_interface.h"
#include "MTIMER1_interface.h"
#include "MTIMER0_interface.h"
#include "HSTEPEER_interface.h"
#include <util/delay.h>

void displayMainScreen(void);
void displayDCDirectionScreen(void);
void displayDCSpeedScreen(void);
void displayServoScreen(void);
void displayStepperDirectionScreen(void);
void displayStepperAngleScreen(void);
uint16 getKeyPadPassword(void);
void timer2_isr(void);


uint8 direction;
uint8 speed;
uint8 angle;
uint8 keyNumber = 0;
uint8 timer0_counter = 0;
uint8 stepperDirection;
uint8 stepperFlag = 0;
uint16 steps = 0;
uint16 stepperAngle;



enum states {
	MAIN_SCREEN,
	DC_DIRECTION,
	DC_SPEED,
	SERVO_ANGLE,
	STEPPER_DIRECTION,
	STEPPER_ANGEL
} systemState;


int main(void) {
	/*one-time init*/
	HKeyPad_init();
	HStepper_voidInit();
	HLCD_init(HLCD_8_BIT);
	MDIO_SetPinDirection(PORTD, 5, OUTPUT);
	MDIO_SetPinDirection(PORTB, 3, OUTPUT);
	MTIMER1_voidInit();
	MTIMER0_voidInit();
	MTIMER2_voidInit();
	MTIMER2_voidSetCallback(timer2_isr, MTIMER2_U8_CALLBACK_OVERFLOW);
	MTIMER2_voidSetDesiredTimeMs(5);

	MTIMER1_voidEnable();
	MTIMER0_voidEnable();
	MTIMER2_voidEnable();

	MTIMER0_voidSetPWMValue(0);
	MTIMER1_voidSetPWM(0);

	/*printing main screen to LCD*/
	systemState = MAIN_SCREEN;

	/*infinite loop*/
	for (;;) {
		/*clear display then print "Select Motor:" and the pressed number*/
		switch (systemState) {
		case MAIN_SCREEN:
			displayMainScreen();
			/*block until a key is pressed*/
			while((keyNumber = HKeyPad_getKey()) == 0);
			if (keyNumber == '1') systemState = DC_DIRECTION;
			else if (keyNumber == '2') systemState = SERVO_ANGLE;
			else if (keyNumber == '3')	systemState = STEPPER_DIRECTION;
			break;
		case DC_DIRECTION:
			displayDCDirectionScreen();
			/*block until a key is pressed*/
			while((keyNumber = HKeyPad_getKey()) == 0);
			direction = keyNumber;
			systemState = DC_SPEED;
			break;
		case DC_SPEED:
			displayDCSpeedScreen();
			/*block until a key is pressed*/
			while((keyNumber = HKeyPad_getKey()) == 0);
			speed = keyNumber;
//			HLCD_writeInt((speed-'0'-1) * 51);
			MTIMER0_voidSetPWMValue((speed-'0'-1) * 51);
			systemState = MAIN_SCREEN;
			break;
		case SERVO_ANGLE:
			displayServoScreen();
			/*block until a key is pressed*/
			angle = getKeyPadPassword();
			MTIMER1_voidSetPWM(angle);
			systemState = MAIN_SCREEN;
			break;
		case STEPPER_DIRECTION:
			displayStepperDirectionScreen();
			/*block until a key is pressed*/
			while((keyNumber = HKeyPad_getKey()) == 0);
			stepperDirection = keyNumber=='1'? HStepper_CW : HStepper_CCW;
			systemState = STEPPER_ANGEL;
			break;
		case STEPPER_ANGEL:
			displayStepperAngleScreen();
			/*block until a key is pressed*/
			stepperAngle = getKeyPadPassword();
			stepperFlag = 1;
			systemState = MAIN_SCREEN;
			break;
		}
		_delay_ms(500);
	}
	return 0;
}

void displayMainScreen(void) {
	HLCD_clear();
	HLCD_writeText("Select Motor:");
	HLCD_setCursor(1, 0);
	HLCD_writeText("1-DC ");
	HLCD_writeText("2-Sv ");
	HLCD_writeText("3-Stp");
}

void displayDCDirectionScreen(void) {
	HLCD_clear();
	HLCD_writeText("Select Direction:");
	HLCD_setCursor(1, 0);
	HLCD_writeText("1-CW ");
	HLCD_writeText("2-CCW ");
}

void displayDCSpeedScreen(void) {
	HLCD_clear();
	HLCD_writeText("Select Speed:");
	HLCD_setCursor(1, 0);
	HLCD_writeText("1  2  3  4  5");
}

void displayServoScreen(void) {
	HLCD_clear();
	HLCD_writeText("Enter Angle:");
	HLCD_setCursor(1, 0);
}

void displayStepperDirectionScreen(void) {
	HLCD_clear();
	HLCD_writeText("Select Direction:");
	HLCD_setCursor(1, 0);
	HLCD_writeText("1-CW ");
	HLCD_writeText("2-CCW ");
}

void displayStepperAngleScreen(void) {
	HLCD_clear();
	HLCD_writeText("Enter Angle:");
	HLCD_setCursor(1, 0);
}

uint16 getKeyPadPassword(void) {
	uint16 num = 0;
	uint8 keyNumber;
	while ((keyNumber = HKeyPad_getKey()) != '=') {
		if (keyNumber != 0 && keyNumber >= '0' && keyNumber <= '9') {
			HLCD_writeData(keyNumber);
			num *= 10;
			num += keyNumber - '0';
		}
		_delay_ms(200);
	}
	return num;
}

void timer2_isr(void) {
	if (stepperFlag == 1 && steps < stepperAngle * 4) {
		HStepper_voidStep(stepperDirection);
		steps++;
		if (steps >= stepperAngle * 4) {
			steps = 0;
			stepperFlag = 0;
		}
	}

}
