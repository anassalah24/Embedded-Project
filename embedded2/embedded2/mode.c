#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"

#include "calculator.h"
#include "mode.h"
#include "stop.h"
#include "calculator.h"
#include "timer.h"


extern volatile int state;

void gpioHandler(){
  
  GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
  LCD_Clear();
  LCD_PrintLn(0, "Loading...");
  SysCtlDelay(80000000/3); //Delay
  switch (state){
  case 1:
    state = 2;
    break;
  
  case 2:
    state = 3;
    break;
    
  case 3:
    state = 1;
    break;
  default:
    break;
  }
  }
   
  


void modeinit(){

    SYSCTL_RCGCGPIO_R |= 0x00000020;
    while((SYSCTL_PRGPIO_R&0x00000020) == 0){};
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_PUR_R = 0x11;
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_DATA_R = 0x0U;        
    GPIOIntEnable(GPIO_PORTF_BASE,GPIO_INT_PIN_4);        
    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_LOW_LEVEL);        
    IntPrioritySet(INT_GPIOF, 0);        
    IntRegister(INT_GPIOF, gpioHandler);       
    IntEnable(INT_GPIOF);
    IntMasterEnable();


}