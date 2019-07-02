#ifndef L_UTILS
#define L_UTILS
    #define MASK(bits)              (1 << bits)
    #define SET_BIT(var,bit)        var = var | MASK(bit)
    #define CLR_BIT(var, bit)       var = var & ~MASK(bit)
    #define GET_BIT(var, bit)       ((var >> bit) & 1)
    #define TOGGLE_BIT(var, bit)    var = var ^ MASK(bit)
#endif
