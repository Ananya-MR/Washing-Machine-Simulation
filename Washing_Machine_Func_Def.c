#include "main.h"

extern unsigned char reset_flag; //to get reset_flag value from main.c program
extern unsigned char operational_mode;

//Array of char strings
char *washing_program[] = {"Daily", "Heavy", "Delicates", "Whites", "Stain Wash", "Eco cottons", "Woolens", "BedSheets", "Rinse+Dry", "Dry Only", "Wash Only", "Aqua Store"};
unsigned char program_number = 0;

char *water_level[] = {"Auto", "Low", "Mediun", "High", "Max"};
unsigned char level = 0;
//function definition

unsigned char sec, min;
unsigned int total_time, time, wash_time, rinse_time, spin_time;

void power_on_screen(void) {
    for (unsigned char i = 0; i < 16; i++) {
        clcd_putch(BLOCK, LINE1(i));
        __delay_ms(100);
    }

    clcd_print("Powering ON", LINE2(3));
    clcd_print("Washing Machine", LINE3(1));

    for (unsigned char i = 0; i < 16; i++) {
        clcd_putch(BLOCK, LINE4(i));
        __delay_ms(100);
    }

    __delay_ms(2000);

}

void washing_program_display(unsigned char key) {
    if (reset_flag == RESET_WASH_PROGRAM_SCREEN) {
        clear_screen();
        reset_flag = RESET_NOTHING;
    }
    if (key == SW4) {
        clear_screen(); //to clear data present previously in every line
        program_number++;
        if (program_number == 12) {
            program_number = 0;
        }
    }

    clcd_print("Washing Program", LINE1(0));
    clcd_putch('*', LINE2(0));
    clcd_print(washing_program[program_number], LINE2(1));
    clcd_print(washing_program[(program_number + 1)%12], LINE3(1));
    clcd_print(washing_program[(program_number + 2)%12], LINE4(1));

    /*if (program_number <= 9) {
        clcd_print(washing_program[program_number], LINE2(1));
        clcd_print(washing_program[program_number + 1], LINE3(1));
        clcd_print(washing_program[program_number + 2], LINE4(1));
    } else if (program_number == 10) {
        clcd_print(washing_program[program_number], LINE2(1));
        clcd_print(washing_program[program_number + 1], LINE3(1));
        clcd_print(washing_program[0], LINE4(1));
    } else if (program_number == 11) {
        clcd_print(washing_program[program_number], LINE2(1));
        clcd_print(washing_program[0], LINE3(1));
        clcd_print(washing_program[1], LINE4(1));
    }*/
}

void water_level_screen(unsigned char key) {
    if (reset_flag == RESET_WATER_LEVEL_SCREEN) {
        clear_screen();
        reset_flag = RESET_NOTHING;
    }

    if (key == SW4) {
        clear_screen();
        level++;
        if (level == 5)
            level = 0;
    }
    
    clcd_print("Water Level", LINE1(0));
    clcd_putch('*', LINE2(0));
    clcd_print(water_level[level], LINE2(1));
    clcd_print(water_level[(level + 1)%5], LINE3(1));
    clcd_print(water_level[(level + 2)%5], LINE4(1));
    
}

//EXTRA - can be given in main.c itself
void start_stop_screen(unsigned char key) {
    if (reset_flag == RESET_START_STOP_SCREEN) {
        clear_screen();
        reset_flag = RESET_NOTHING;
    }
    clcd_print("Press Switch:", LINE1(0));
    clcd_print("SW5: START", LINE2(0));
    clcd_print("SW6: STOP", LINE3(0));  
}

void start_screen(unsigned char key)
{
    door_status_check();
    if(reset_flag == RESET_START_SCREEN)
    {
        clear_screen();
        clcd_print("Prog:",LINE1(0));
        clcd_print(washing_program[program_number],LINE1(6));
        clcd_print("Time:",LINE2(0));
        // mm:ss int to ascii
        clcd_putch(min/10 + '0',LINE2(6));//extract ascii of higher digit
        clcd_putch(min%10 + '0',LINE2(7));//extract ascii of lower digit
        clcd_putch(':',LINE2(8));
        clcd_putch(sec/10 + '0',LINE2(9));//extract ascii of higher digit
        clcd_putch(sec%10 + '0',LINE2(10));//extract ascii of lower digit
        reset_flag = RESET_NOTHING;
        
        __delay_ms(2000);
        clear_screen();
        
        clcd_print("Function:",LINE1(0));
        clcd_print("Time:",LINE2(0));
        clcd_print("S5:START",LINE3(0));
        clcd_print("S6:PAUSE",LINE4(0));
        
        total_time = time = (min*60)+sec;
        wash_time = (int) total_time*0.46;
        rinse_time = (int) total_time*0.12;
        spin_time = (int) total_time*0.42;
        TMR2ON = 1;//turn on timer
        FAN = ON;
        
    }
    if(key == SW6)
    {
        TMR2ON = 0;//turn off timer
        FAN = OFF;
        operational_mode = PAUSE;
    }

    total_time = (min*60)+sec;
    if(program_number <= 7)
    {
        if(total_time >= (time-wash_time))
        {
            clcd_print("WASH ",LINE1(9));
        }
        else if(total_time >= (time-wash_time-spin_time))
        {
            clcd_print("RINSE ",LINE1(9));
        }
        else
        {
            clcd_print("SPIN ",LINE1(9));
        }
    }
    else if(program_number == 8)
    {
        if(total_time >= (time-(0.4*time)))
        {
            clcd_print("RINSE ",LINE1(9));
        }  
        else
        {
            clcd_print("SPIN ",LINE1(9));
        }   
    }
    else if(program_number == 9)
    {
        clcd_print("SPIN ",LINE1(9));
    } 
    else
    {
        clcd_print("WASH ",LINE1(9));
    }
    
    clcd_putch(min/10 + '0',LINE2(6));//extract ascii of higher digit
    clcd_putch(min%10 + '0',LINE2(7));
    clcd_putch(':',LINE2(8));
    clcd_putch(sec/10 + '0',LINE2(9));//extract ascii of higher digit
    clcd_putch(sec%10 + '0',LINE2(10));//extract ascii of lower digit
    if(sec==0 && min == 0)
    {
        clear_screen();
        FAN = OFF;
        BUZZER = ON;
        clcd_print("ProgramCompleted",LINE1(0));
        clcd_print("Remove Clothes",LINE2(0));
        __delay_ms(2000);
         BUZZER = OFF;
        
        operational_mode = WASHING_PROGRAM_SCREEN;
        reset_flag = RESET_WASH_PROGRAM_SCREEN;
        clear_screen();
    }
        
    
}


void set_time(void)
{
    switch(program_number)
    {
        case 0://daily
            switch (level)
            {
                case 1://low
                    min = 0;
                    sec = 33;
                    break;
                case 0://Auto
                case 2://medium
                    sec = 41;
                    min = 0;
                    break;
                case 3://high
                case 4://max
                    sec = 45;
                    min = 0;
                    break;
            }
        break;
            
        case 1://heavy
            switch (level)
            {
                case 1://low
                    sec = 50;
                    min = 0;
                    break;
                case 0://Auto
                case 2://medium
                    sec = 44;
                    min = 0;
                    break;
                case 3://high
                case 4://max
                    sec = 57;
                    min = 0;
                    break;
            }
        break;
        case 2://Delicates
            switch (level)
            {
                case 1://low
                case 0://Auto
                case 2://medium
                    sec = 26;
                    min = 0;
                    break;
                case 3://high
                case 4://max
                    sec = 31;
                    min = 0;
                    break;
            }
        break;
        case 3://Whites
            switch (level)
            {
                case 1://low
                case 0://Auto
                case 2://medium
                case 3://high
                case 4://max
                    min = 1;
                    sec = 16;
                    break;
            }
        break;
        case 4://Stain Wash
            switch (level)
            {
                case 1://low
                case 0://Auto
                case 2://medium
                case 3://high
                case 4://max
                    min = 1;
                    sec = 36;
                    break;
            }
        break;
        case 5://Eco cottons
            switch (level)
            {
                case 1://low
                case 0://Auto
                case 2://medium
                    sec = 31;
                    min = 0;
                    break;
                case 3://high
                case 4://max
                    sec = 36;
                    min = 0;
                    break;
            }
        break;
        case 6://Woolens
            switch (level)
            {
                case 1://low
                case 0://Auto
                case 2://medium
                case 3://high
                case 4://max
                    sec = 29;
                    min = 0;
                    break;
            }
        break;
        case 7://BedSheets
            switch (level)
            {
                case 1://low
                    sec = 46;
                    min = 0;
                    break;
                case 0://Auto
                case 2://medium
                    sec = 53;
                    min = 0;
                    break;
                case 3://high
                case 4://max
                    sec = 60;
                    min = 0;
                    break;
            }
        break;
        case 8://Rinse+Dry
            switch (level)
            {
                case 1://low
                    sec = 18;
                    min = 0;
                    break;
                case 0://Auto
                case 2://medium
                case 3://high
                case 4://max
                    sec = 20;
                    min = 0;
                    break;
            }
        break;
        case 9://Dry Only
            switch (level)
            {
                case 1://low
                case 0://Auto
                case 2://medium
                case 3://high
                case 4://max
                    sec = 6;
                    min = 0;
                    break;
            }
        break;
        case 10://Wash Only
            switch (level)
            {
                case 1://low
                    sec = 16;
                    min = 0;
                    break;
                case 0://Auto
                case 2://medium
                    sec = 21;
                    min = 0;
                    break;
                case 3://high
                case 4://max
                    sec = 26;
                    min = 0;
                    break;
            }
        break;
        case 11://Aqua Store
            switch (level)
            {
                case 1://low
                case 0://Auto
                case 2://medium
                case 3://high
                case 4://max
                    sec = 50;
                    min = 0;
                    break;
            }
        break;
    }
}

void door_status_check(void)
{
    if(RB0 == 0)
    {
        FAN = OFF;
        TMR2ON = 0;
        BUZZER = ON;
        clear_screen();
        clcd_print("Door is open",LINE1(0));
        clcd_print("Close the door",LINE2(0));
        while(RB0==0)
        {
            ;//wait untill door is closed
        }
        FAN = ON;
        TMR2ON = 1;
        BUZZER = OFF;
        clear_screen();
        clcd_print("Function:",LINE1(0));
        clcd_print("Time:",LINE2(0));
        clcd_print("S5:START",LINE3(0));
        clcd_print("S6:PAUSE",LINE4(0));   
    }
}


void clear_screen(void) { //to clear CLCD display screen
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE); //0x01,0
    __delay_us(500);
}