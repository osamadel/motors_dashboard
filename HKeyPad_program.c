#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MDIO_interface.h"
#include "HKeyPad_private.h"
#include "HKeyPad_interface.h"


void HKeyPad_init() {
    MDIO_SetPortDirection(KPD_PORT, KPD_DIRECTION);
    MDIO_SetPortValue(KPD_PORT, ~(KPD_DIRECTION));
}// end HKeyPad_init


uint8 HKeyPad_getKey(void) {
    uint8 pressedButton;
    for (uint8 i=0; i<4; i++) {
    	// switch all columns to HIGH
    	MDIO_SetPinOutput(KPD_PORT, 0, HIGH);
    	MDIO_SetPinOutput(KPD_PORT, 1, HIGH);
    	MDIO_SetPinOutput(KPD_PORT, 2, HIGH);
    	MDIO_SetPinOutput(KPD_PORT, 3, HIGH);

    	// set the current column to LOW
        MDIO_SetPinOutput(KPD_PORT, i, LOW);

        // read each row
        for (uint8 j=4; j<8; j++) {
            pressedButton = MDIO_GetPinValue(KPD_PORT, j);
            // if row=0 at the current column, then switch (row, column) is pressed
            if (!pressedButton)
                return KPD_arr[j-4][i];
        }
    }// end for
    return 0;
}// end HKeyPad_getKey
