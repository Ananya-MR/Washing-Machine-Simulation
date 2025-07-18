#include <xc.h>
#include "clcd.h"

void clcd_write(unsigned char byte, unsigned char mode) // write data/instruction to CLCD
{
    CLCD_RS = mode;
    CLCD_DATA_PORT = byte;
    
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;
    
    __delay_us(4100); // - max time taken for any data or instruction
}

static void init_display_controller(void)
{
    /* Startup Time for the CLCD controller */
    __delay_ms(30); // 40 - 50 in datasheet so avg of 30ms
    
    /* The CLCD Startup Sequence */
    clcd_write(EIGHT_BIT_MODE, INST_MODE);  //0x33 - instruction
    __delay_us(4100); //as mentioned in datasheet
    clcd_write(EIGHT_BIT_MODE, INST_MODE);
    __delay_us(100); //as mentioned in datasheet
    clcd_write(EIGHT_BIT_MODE, INST_MODE);
    __delay_us(1); //safer side
    
    clcd_write(TWO_LINES_5x8_8_BIT_MODE, INST_MODE); //selecting from page29 of datasheet
    __delay_us(100);
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
    clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
    __delay_us(100);
}

void init_clcd(void)
{
    /* Setting the CLCD Data Port as Output */
    CLCD_DATA_PORT_DDR = 0x00; //TRISD =0x00;
    
    /* Setting the RS and EN lines as Output */
    CLCD_RS_DDR = 0; //TRISE2 =0
    CLCD_EN_DDR = 0; //TRISE1 =0
    
    init_display_controller();
}

void clcd_putch(const char data, unsigned char addr)
{
    clcd_write(addr, INST_MODE); //move cursor to given address
    clcd_write(data, DATA_MODE);
}

void clcd_print(const char *str, unsigned char addr)
{
    clcd_write(addr, INST_MODE); //move cursor to given address
    
    while (*str != '\0') //repeat for all char or just while (*str)
    {
        clcd_write(*str, DATA_MODE); 
        str++;
    }
}