#ifndef MDIO_PRIVATE_H
#define MDIO_PRIVATE_H
    
    // PORTA
    #define MDIO_PORTA  *((volatile uint8 *) 0x3B)
    #define MDIO_DDRA   *((volatile uint8 *) 0x3A)
    #define MDIO_PINA   *((volatile uint8 *) 0x39)
    // PORTB
    #define MDIO_PORTB  *((volatile uint8 *) 0x38)
    #define MDIO_DDRB   *((volatile uint8 *) 0x37)
    #define MDIO_PINB   *((volatile uint8 *) 0x36)
    // PORTC
    #define MDIO_PORTC  *((volatile uint8 *) 0x35)
    #define MDIO_DDRC   *((volatile uint8 *) 0x34)
    #define MDIO_PINC   *((volatile uint8 *) 0x33)
    // PORTD
    #define MDIO_PORTD  *((volatile uint8 *) 0x32)
    #define MDIO_DDRD   *((volatile uint8 *) 0x31)
    #define MDIO_PIND   *((volatile uint8 *) 0x30)

#endif
