#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"

#include "calculator.h"
#include "mode.h"


volatile int state = calculator;

void initmode(){

  SYSCTL_RCGCGPIO_R |= 0x00000020;
  while((SYSCTL_PRGPIO_R&0x00000020) == 0){};
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R = 0x10;
  GPIO_PORTF_DIR_R = 0x00;
  GPIO_PORTF_PUR_R = 0x10;
  GPIO_PORTF_DEN_R = 0x10;


}


int getmodebutton(){
  
     if((GPIO_PORTF_DATA_R & 0x10U)>>4)
    {
      delay_ms(50);
      if((GPIO_PORTF_DATA_R & 0x10U)>>4)
      {
          return ((GPIO_PORTF_DATA_R & 0x10U)>>4);
      }
      while((GPIO_PORTF_DATA_R & 0x10U)>>4 ){;
      delay_ms(50);
      }
    }

     return ((GPIO_PORTF_DATA_R & 0x10U)>>4);


}