/*
 * main.c
 *  Author:
 *      Ahmet Eren ODACI
 *
 *  Credit:
 *      Lokman G?KDERE
 *      http://www.mcu-turkey.com/stellaris-launchpad-16x2-lcd/
 */

#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "keypad.h"
#include "driverlib/sysctl.h"
#include <stdio.h>
#include "calculator.h"
#include "mode.h"
#include "keypad.h"   
   





int main(void) {

        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

        LCD_init();
        initmode();
        keypad_Init();
        state = calculator;
        calcMode();

}
























//            LCD_Print("Hello", "ya RORO"); //Print 2 lines
//
//            SysCtlDelay(80000000/3); //Delay
//            LCD_Clear();

//            LCD_PrintLn(0, "Anas, fuck you ");
//            SysCtlDelay(8000000/3); //Delay
//
//            LCD_PrintLn(1, "You motherfucker");
//
//            SysCtlDelay(80000000/3); //Delay
//            LCD_Clear();
//
//            LCD_PrintJustify(0, "akteb", "eh?");
//
//            SysCtlDelay(80000000/3); //Delay
//            LCD_Clear();
              
//              LCD_PrintLn(0 , "Calculator Mode");
//              SysCtlDelay(80000000/3); //Delay
//              LCD_Cursor(1,0);
//              LCD_Show('1');
//              SysCtlDelay(8000000/3); //Delay              
//              LCD_Cursor(1,1);
//              LCD_Show('+');
//              SysCtlDelay(8000000/3); //Delay
//              LCD_Cursor(1,2);            
//              LCD_Show('1');
//              SysCtlDelay(8000000/3); //Delay
//              LCD_Clear();
//              
//              LCD_PrintLn(1,"2");