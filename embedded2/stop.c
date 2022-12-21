#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"
#include "calculator.h"
#include "mode.h"
#include <time.h>
#include "tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "stop.h"

static int minutes = 0;
static int seconds = 0;

extern volatile int state;

//This funtion initiates all things needed to use the timer0 module that is used in stop watch mode
void initStop(){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}
  TimerDisable(TIMER0_BASE,TIMER_A);
  IntMasterEnable();
  TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC);
  TimerControlStall(TIMER0_BASE,TIMER_A,true);
}


//This function views the last value that stopwatch stopped at when user enters the stopwatch mode (it stores last value)
void initialValuestop(){
    
    //construct the last value stored
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

//This function is the interrupt handler fot the timer0 which is elapsed every 1 second to update the lcd 
void secondpassedHandler(){
  //clear interrupt flag
  TIMER0_ICR_R = 0x1 ;
  char currentTimer[5];  
  
  //construct updated minutes and second to view on lcd
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
  if (seconds == 59){
      minutes ++;
      seconds = 00;
  }
  else{
      seconds++;
  }
  LCD_PrintLn(1,currentTimer);
}

//This function starts the timer when user press start
void start(){
     //load 1 second in the timer
     TimerLoadSet(TIMER0_BASE,TIMER_A,SysCtlClockGet());
     IntEnable(INT_TIMER0A);
     //interrupt on timeout
     TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
     TIMER0_ICR_R = 0x1 ;
     TimerIntRegister(TIMER0_BASE , TIMER_A , secondpassedHandler);
     TimerEnable(TIMER0_BASE, TIMER_A);
}

//This is the main loop for the stopwatch , it loops as long as the global external state variable is 3 
// it controls the pauseing , starting and resetting of the stopwatch
void stopmode(){

        volatile char key;
        LCD_PrintLn(0,"StopWatch Mode");
        //show latest value
        initialValuestop();

        while (state == 3){
           key = keypad_getkeystop(); 
           if(key == 'q'){continue;}
           if(key == '='){             
              start();           
           }
           if (key == 'x'){         
              TimerDisable(TIMER0_BASE,TIMER_A);
           } 
           if (key == 'c'){
              TimerDisable(TIMER0_BASE,TIMER_A);
              TimerLoadSet(TIMER0_BASE,TIMER_A,0);
              TIMER0_ICR_R = 0x1 ; 
              minutes = 0;
              seconds = 0;
              LCD_PrintLn(1,"00:00");
           }
        }

}




