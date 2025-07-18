/*
 * File:   main.c
 * Author: DELL
 *
 * Created on 11 June, 2025, 7:55 PM
 */


#include <xc.h>
#include "main.h"
#include "Washing_Machine_Header.h"

unsigned char operational_mode = WASHING_PROGRAM_SCREEN;
unsigned char reset_flag = RESET_WASH_PROGRAM_SCREEN;

#pragma config WDTE = OFF

static void init_config(void) {
    //to initialise clcd
    init_clcd();
    //to initialise Digital keypad
    init_digital_keypad();
    //to initialise timer
    init_timer2();
    //to enable global and peripheral interrupt
    GIE = 1;
    PEIE = 1;
    
    BUZZER_DDR = 0;
    FAN_DDR = 0;
    FAN = OFF;
    BUZZER = OFF;
    
}

void main(void) 
{
    init_config();
    unsigned char key;
    
    //initial display statements
    clcd_print("Press Key 5 to ",LINE1(1));
    clcd_print("Power ON",LINE2(4));
    clcd_print("Washing Machine",LINE3(1));
    while(read_digital_keypad(STATE) != SW5); // wait untill sw5 is pressed
    
    clear_screen();
    power_on_screen();
    
     while(1) {
        key = read_digital_keypad(STATE);
         /*to avoid bouncing effect*/
        for(unsigned int delay=300;delay--;);
        
        if (key == LPSW4 && operational_mode == WASHING_PROGRAM_SCREEN )
        {
            operational_mode = WATER_LEVEL_SCREEN;
            reset_flag = RESET_WATER_LEVEL_SCREEN;
        }
        else if(key == LPSW4 && operational_mode == WATER_LEVEL_SCREEN)
        {
            operational_mode = START_STOP_SCREEN;
            reset_flag = RESET_START_STOP_SCREEN;
        }
        else if(key == SW5 && operational_mode == PAUSE)
        {
            operational_mode = START_SCREEN;
            TMR2ON = ON;
            FAN = ON;
        }
        
        switch(operational_mode)
        {
            case WASHING_PROGRAM_SCREEN:
                washing_program_display(key);
                break;
                        
            case WATER_LEVEL_SCREEN: 
                water_level_screen(key);
                break;
                 
            case START_STOP_SCREEN:
                start_stop_screen(key);
                if (key == SW5)
                {
                    operational_mode = START_SCREEN;
                    reset_flag = RESET_START_SCREEN;
                    set_time();
                   
                }
                else if (key == SW6)
                {
                    operational_mode = WASHING_PROGRAM_SCREEN;
                    reset_flag = RESET_WASH_PROGRAM_SCREEN;
                }
                break;
            
            case START_SCREEN:
                start_screen(key);//run program
                break;
                
        }
    
     }
    return;
    
} 