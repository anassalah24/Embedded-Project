#ifndef __MODE_H__
#define __MODE_H__



#include "lcd.h"
#include "keypad.h"
#include "driverlib/sysctl.h"
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "Delay.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"

#define calculator 1
#define timer 2
#define stopwatch 3

extern volatile int state;


void initmode();

int getmodebutton();


#endif