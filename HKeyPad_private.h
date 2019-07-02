#ifndef H_KEYPAD_PRIVATE_H
#define H_KEYPAD_PRIVATE_H

    #define ROWS            4
    #define COLS            4
    #define KPD_DIRECTION   0x0F
    #define KPD_PORT        PORTC

    uint8 KPD_arr[4][4] = {
        {'1', '2', '3', '+'},
        {'4', '5', '6', '-'},
        {'7', '8', '9', '*'},
        {'C', '0', '=', '/'}
    };

#endif
