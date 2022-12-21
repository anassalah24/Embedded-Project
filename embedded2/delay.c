//This module is needed in some lcd functionalities to function properly
#include "delay.h"

//This function delays the code by pooling on the micro controller 
//for a specific period of time measured upon the fact that the controller
//is running by speed 16MHZ.
//Calculating the no cycles needed from the microcontroller to wait no of Milli seconds.

void delay_ms(int time)
{
int i, j;
for(i = 0 ; i < time; i++)
  for(j = 0; j < 3180; j++){}
}
 
//This function delays the code by pooling on the micro controller 
//for a specific period of time measured upon the fact that the controller
//is running by speed 16MHZ.
//Calculating the no cycles needed from the microcontroller to wait no of Micro seconds.

void delay_us(int time)
{
int i, j;
for(i = 0 ; i < time; i++)
  for(j = 0; j < 3; j++){}
}