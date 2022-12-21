

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



volatile int state = 0;

int main(void) {
        //configure system clock
        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
        // initialize lcd ports , keypad ports , timers , SW1 and LEDs
        LCD_init();
        keypad_Init();
        initStop();
        initTimer();
        modeinit();
        //set priority of mode switching higher than timers to change mode before counting timer values
        IntPrioritySet(INT_WTIMER0A, 0xE0);
        IntPrioritySet(INT_GPIOF, 0x00);
        //initial state is calulator
        state = 1;
        while (1) {
        
          switch (state){
          
          case 1:
            LCD_Clear();
            calcMode();
            break;
          
          case 2:
            LCD_Clear();
            timerMode();
            break;
            
          case 3:
            LCD_Clear();
            stopmode();
            break;
          default:
            break;
          
          }
        
        
        }
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