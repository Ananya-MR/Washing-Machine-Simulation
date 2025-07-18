#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
{
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    static unsigned char long_press = 1;
    unsigned char key = KEYPAD_PORT & INPUT_LINES;
    static unsigned char pre_key;
    
    if ((key != ALL_RELEASED) && once)//first time when switch is pressed
    {
        once = 0; // indicate sw is pressed
        pre_key = key;
        long_press = 0;
    }
    else if ((key == ALL_RELEASED ) && !once)
    {
        once = 1; // indicate sw is not pressed or is released
        if (long_press < 15)
            return pre_key; // short press
    }
    else if (!once && long_press <= 15)//can be 30
        long_press++;
    else if (!once && long_press == 16 && key == SW4)//31 if 16 is not working
    {
        long_press++;
        return LPSW4; // long press
    }
        
    
     return ALL_RELEASED;
}

    /*static unsigned char once = 1;
    
    if (mode == LEVEL_DETECTION)//multiple times
    {
        return KEYPAD_PORT & INPUT_LINES; //PORTB & 0X3F
    }
    else  // edge detection - only once
    {
        if (((KEYPAD_PORT & INPUT_LINES) != ALL_RELEASED) && once)//check if any key is pressed
        {
            once = 0;
            
            return KEYPAD_PORT & INPUT_LINES;
        }
        else if ((KEYPAD_PORT & INPUT_LINES) == ALL_RELEASED)
        {
            once = 1;
        }
    }*/
    
   
