#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"
#include "calculator.h"
#include "mode.h"
#include <time.h>
#include "inc/hw_ints.h"
#include "tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"


static int minutes = 0;
static int seconds = 0;

extern volatile int state;
void updateLCD(){
   
    LCD_Clear();
    LCD_PrintLn(0,"Timer Mode");
    
    
    while ((minutes !=0) || (seconds!=0) ){
        char currentTimer[5];
        
        if (( minutes == 0 ) && (seconds == 0)){break;}
        
        currentTimer[2]=':';
        
        
        
        if (minutes < 10){
        
            currentTimer[0]='0';
            currentTimer[1] = minutes+'0';
            
        
        }
        else {
   
            currentTimer[0] = (minutes / 10)+'0';
            currentTimer[1] = (minutes % 10)+'0';
            
        }
        if (seconds < 10){
        
            currentTimer[3]='0';
            currentTimer[4] = seconds+'0';
            
        
        }
        else {
   
            currentTimer[3] = (seconds / 10)+'0';
            currentTimer[4] = (seconds % 10)+'0';
            
        }        
        
        
        
        LCD_PrintLn(1,currentTimer);
        
        if (seconds == 0){
            minutes --;
            seconds = 59;
        
        }
        else{
        
            seconds--;
        }
        
        
//        LCD_Clear();
//        LCD_PrintLn(0,"Timer Mode");
        LCD_PrintLn(1,currentTimer);
        
        
        delay_ms(2000);
        
        

    
    }
  
  }       





double getTicks(){

  double minTicks = ((minutes*60)*SysCtlClockGet());
  double secTicks = (seconds*SysCtlClockGet());

  return minTicks+secTicks;

}


void timeuphandler(){

      WTIMER0_ICR_R = 0x1 ;
//      LCD_Clear();
//      LCD_PrintLn(0,"Timer Mode");   
//      LCD_PrintLn(1,"Time's up !!");
//      GPIO_PORTF_DATA_R = 0x2U;
//    LCD_Clear();
//    LCD_PrintLn(0,"Timer Mode");
      char currentTimer[5];
      if (( minutes == 0 ) && (seconds == 0)){
        LCD_PrintLn(1,"Time's up !!");
        GPIO_PORTF_DATA_R = 0x2U;
        TimerDisable(WTIMER0_BASE, TIMER_A);        
        return;
      }        
      currentTimer[2]=':';
      if (minutes < 10){
      
          currentTimer[0]='0';
          currentTimer[1] = minutes+'0'; 
      }
      else {
          currentTimer[0] = (minutes / 10)+'0';
          currentTimer[1] = (minutes % 10)+'0';           
      }
      if (seconds < 10){        
          currentTimer[3]='0';
          currentTimer[4] = seconds+'0';        
      }
      else {   
          currentTimer[3] = (seconds / 10)+'0';
          currentTimer[4] = (seconds % 10)+'0';            
      }           
      LCD_PrintLn(1,currentTimer);
      if (seconds == 0){
          minutes --;
          seconds = 59;   
      }
      else{
          seconds--;
      }
//        LCD_Clear();
//        LCD_PrintLn(0,"Timer Mode");
//      LCD_PrintLn(1,currentTimer);
//      delay_ms(2000);
  }


void initTimer(){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER0)){}
  TimerDisable(WTIMER0_BASE,TIMER_A);
  IntMasterEnable();
  TimerConfigure(WTIMER0_BASE,TIMER_CFG_PERIODIC);
  TimerControlStall(WTIMER0_BASE,TIMER_A,true);
  

}


void timerMode(){
        int i  = 0;
        volatile char key;
        LCD_PrintLn(0,"Timer Mode");
        LCD_PrintLn(1,"00:00");        
        SysCtlDelay(80000000/3); //Delay
//        LCD_Cursor(1,i);
//        i++;
        
       
        while (state == 2){
           key = keypad_getkeytim();
           if(key == 'q'){continue;}
           if (key == 'x'){//dont forget to change the =
            LCD_Clear();
            LCD_PrintLn(0,"Timer Mode");
            LCD_PrintLn(1,"00:00"); 
            GPIO_PORTF_DATA_R = 0x0U;
            SysCtlDelay(80000000/3); //Delay
            i=0;
            minutes = 0;
            seconds = 0;
            continue;
           
           }
           
           if (key == '='){
             LCD_Command(0xC0 + 16); //Hide cursor           
             double ticks = getTicks();
//             int loopcount = (ticks /SysCtlClockGet());
//             for (int i = 0 ; i < loopcount; i++){
             if (( minutes == 0 ) && (seconds == 0)){
                LCD_PrintLn(1,"Time's up !!");
                GPIO_PORTF_DATA_R = 0x2U;
                TimerDisable(WTIMER0_BASE, TIMER_A);
                break;
              }        
             TimerLoadSet64(WTIMER0_BASE,SysCtlClockGet());
//             IntEnable(INT_WTIMER0A);
             TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
             TimerIntRegister(WTIMER0_BASE , TIMER_A , timeuphandler);
             TimerEnable(WTIMER0_BASE, TIMER_A);
             
//             }
//             TimerLoadSet64(WTIMER0_BASE,ticks);
//             IntEnable(INT_WTIMER0A);
//             TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
//             TimerIntRegister(WTIMER0_BASE , TIMER_A , timeuphandler);
//             //function to show each count
////             printf("%s","Reached here?");
//             TimerEnable(WTIMER0_BASE, TIMER_A);
             // how to stop counting if stopped or transitioned program
//             LCD_Command(0xC0 + 16); //Hide cursor
//             updateLCD();
//             LCD_PrintLn(1,"00:00");  
             continue;
               
              
           }
           
           LCD_Cursor(1,i); 
           LCD_Show(key);
           if (i>2){
             seconds = (seconds*10) + (((int)(key))-48); 
//             printf("%s","Minutes is = ");
//             printf("%d\n",minutes);   
//             printf("%s","seconds is = ");
//             printf("%d\n",seconds);
             SysCtlDelay(8000000/3); //Delay              
             delay_ms(200);
             i++;
             continue;               
           }
           
           minutes = (minutes*10) + (((int)(key))-48);           
            
//           printf("%s","Minutes is = ");
//           printf("%d\n",minutes); 
//           
//           printf("%s","seconds is = ");
//           printf("%d\n",seconds);            
           
           SysCtlDelay(8000000/3); //Delay              
           delay_ms(200);
           i++;
           if (i==2){
            i++;
           }
        
        
        
        
        
        
        }
        
        
        
        
        
        
        
        
        
        
        

}


