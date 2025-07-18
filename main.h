/* 
 * File:   main.h
 * Author: DELL
 *
 * Created on 12 June, 2025, 7:15 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "clcd.h"
#include "digital_keypad.h"
#include "timers.h"
#include "Washing_Machine_Header.h"

#define WASHING_PROGRAM_SCREEN      0X01
#define WATER_LEVEL_SCREEN          0X02
#define START_STOP_SCREEN           0X03

#define RESET_WASH_PROGRAM_SCREEN   0X11//ANY VALUE
#define RESET_NOTHING               0XFF
#define RESET_WATER_LEVEL_SCREEN    0x22
#define RESET_START_STOP_SCREEN     0X33
#define START_SCREEN                0X44
#define RESET_START_SCREEN          0x55
#define PAUSE                       0x66

#define FAN_DDR                     TRISC2 
#define BUZZER_DDR                  TRISC1 
#define FAN                         RC2 
#define BUZZER                      RC1
#define ON                          1
#define OFF                         0
                      

#endif	/* MAIN_H */

