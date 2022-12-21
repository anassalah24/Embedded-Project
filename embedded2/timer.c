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
     

//This function calculate ticks from minutes and seconds passed by the user
double getTicks(){
  
  //sysclockget retun the ticks for one second depending of clock frequency of the board
  double minTicks = ((minutes*60)*SysCtlClockGet());
  double secTicks = (seconds*SysCtlClockGet());

  return minTicks+secTicks;

}


// This is the interrupt handler for the Wtimer0 module that is fired every second since the timer elapses every 1 second to update the LCD
// it also shows times up after counting stops as it reaches 00:00 and Lights up the RED LED in gpio portf
void timeuphandler(){
      //clear interrupt
      WTIMER0_ICR_R = 0x1 ;
      char currentTimer[5];
      //check if time is up!!
      if (( minutes == 0 ) && (seconds == 0)){
        LCD_PrintLn(1,"Time's up !!");
        GPIO_PORTF_DATA_R = 0x2U;
        TimerDisable(WTIMER0_BASE, TIMER_A);        
        return;
      }        
      currentTimer[2]=':';
      //construct view of counter to pass to lcd
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
      //decrement seconds and minutes
      if (seconds == 0){
          minutes --;
          seconds = 59;   
      }
      else{
          seconds--;
      }
  }

//This function initiates all things related to Wtimer0 that is used in this mode
void initTimer(){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER0)){}
  TimerDisable(WTIMER0_BASE,TIMER_A);
  IntMasterEnable();
  TimerConfigure(WTIMER0_BASE,TIMER_CFG_PERIODIC);
  TimerControlStall(WTIMER0_BASE,TIMER_A,true);
  

}

//This function shows the last value in timer when user opens timer mode (last value is stored)
void initialValue(){
        char currentTimer[5];       
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
}


//This is the main loop fot the timer mode , it stays in this mode as long as global external variable state is 2
//it controls pausing,starting and clearing the timer
void timerMode(){
        int i  = 0;
        volatile char key;
        LCD_PrintLn(0,"Timer Mode");
        //view last stored value of timer
        initialValue();
       
        while (state == 2){
           //get key from user to know minutes and seconds before starting timer
           key = keypad_getkeytim();
           if(key == 'q'){continue;}
           //clear timer and reset value to 0
           if (key == 'c'){
            TimerDisable(WTIMER0_BASE, TIMER_A);
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
           //pause the timer
           if(key == 'x'){
            TimerDisable(WTIMER0_BASE, TIMER_A);
            continue; 
           }
           //start timer
           if (key == '='){
             LCD_Command(0xC0 + 16); //Hide cursor           
             double ticks = getTicks();
             //if user presses start with no values passed
             if (( minutes == 0 ) && (seconds == 0)){
                LCD_PrintLn(1,"Time's up !!");
                GPIO_PORTF_DATA_R = 0x2U;
                TimerDisable(WTIMER0_BASE, TIMER_A);
                break;
              }        
             TimerLoadSet64(WTIMER0_BASE,SysCtlClockGet());
             TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
             TimerIntRegister(WTIMER0_BASE , TIMER_A , timeuphandler);
             TimerEnable(WTIMER0_BASE, TIMER_A);
             continue;   
           }
           //construct minutes and seconds
           LCD_Cursor(1,i); 
           LCD_Show(key);
           if (i>2){
             seconds = (seconds*10) + (((int)(key))-48); 
             SysCtlDelay(8000000/3); //Delay              
             delay_ms(200);
             i++;
             continue;               
           }           
           minutes = (minutes*10) + (((int)(key))-48);                                           
           SysCtlDelay(8000000/3); //Delay              
           delay_ms(200);
           i++;
           if (i==2){
            i++;
           }   
        }
        
        
        
        
        
        
        
        
        
        
        

}


