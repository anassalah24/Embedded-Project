#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

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



void show_answer();
void calc();
void calcMode();













#endif