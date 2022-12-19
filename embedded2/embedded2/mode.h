#ifndef __MODE_H__
#define __MODE_H__


#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "keypad.h"
#include <stdio.h>
#include "calculator.h"
#include "keypad.h"  
#include "timer.h"
#include "stop.h"  
#include "mode.h"   
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

#define calculator 1
#define timer 2
#define stopwatch 3

void gpioHandler();
void modeinit();


#endif