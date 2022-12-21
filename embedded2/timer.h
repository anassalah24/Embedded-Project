#ifndef __TIMER_H__
#define __TIMER_H__

#include "lcd.h"
#include "keypad.h"
#include "driverlib/sysctl.h"
#include <stdio.h>
#include "inc/hw_ints.h"
#include "tm4c123gh6pm.h"
#include "Delay.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"



void initTimer();

void timerMode();

double getTicks();

void timeuphandler();

void initialValue();









#endif