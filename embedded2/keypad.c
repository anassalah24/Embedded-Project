 
/*
*  @Hardware Connentions
*
* [PE1 - PE4] -> [R1 - R4]  Rows
* [PC4 - PC7] -> [C1 - C4]  Cols
*  
****************************************************/
#include "keypad.h"

unsigned int ncols = 0;
unsigned int nrows = 0;                                                                    
unsigned const char symbol[padRows][padCols] = {{ '1', '2',  '3', '+'},      
                                                { '4', '5',  '6', '-'},      
                                                { '7', '8',  '9', '/'},      
                                                { 'x', '0',  'c', '='}}; 
extern volatile int state;

// This functions initializes port C and port E to be ready for use upon the needed features.
void keypad_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x14;            //enable clc for port C & D  
  while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be enabled
  GPIO_PORTC_CR_R  |= 0xF0;             //allow changes to all the bits in port C
  GPIO_PORTE_CR_R  |= 0x1E;             //allow changes to all the bits in port E
  GPIO_PORTC_DIR_R |= 0xF0;             //set directions cols are o/ps
  GPIO_PORTE_DIR_R |= 0x00;             //set directions raws are i/ps
  GPIO_PORTE_PDR_R |= 0x1E;             //pull down resistor on Raws
  GPIO_PORTC_DEN_R |= 0xF0;             //digital enable pins in port C
  GPIO_PORTE_DEN_R |= 0x1E;             //digital enable pins in port E

}


//These function returns the value of a key have been pressed at the moment the function had been called. 
//It simply makes a 2 loops one to find the column which contains the button 
//had been pressd and another loop to determine the row of that button. 
//Having these data the we could determine a unique value for each button.
//They operate on a while loop as long as their state is the state of the specific mode 
//for example keypad_getkeycalc will loop as long as I am in the calculator mode 
char keypad_getkeycalc(void)
{
  while(state == 1)
  {
    for(int i = 0; i < 4; i++)                        //columns traverse
    {
      GPIO_PORTC_DATA_R = (1U << i+4);
      delay_us(2);
      for(int j = 0; j < 4; j++)                     //raws traverse
      {
        if((GPIO_PORTE_DATA_R & 0x1E) & (1U << j+1))
          return symbol[j][i];
      }
    }
  }
  return 'q';
}


char keypad_getkeytim(void)
{
  while(state == 2)
  {
    for(int i = 0; i < 4; i++)                        //columns traverse
    {
      GPIO_PORTC_DATA_R = (1U << i+4);
      delay_us(2);
      for(int j = 0; j < 4; j++)                     //raws traverse
      {
        if((GPIO_PORTE_DATA_R & 0x1E) & (1U << j+1))
          return symbol[j][i];
      }
    }
  }
 return 'q';
}

char keypad_getkeystop(void)
{
  while(state == 3)
  {
    for(int i = 0; i < 4; i++)                        //columns traverse
    {
      GPIO_PORTC_DATA_R = (1U << i+4);
      delay_us(2);
      for(int j = 0; j < 4; j++)                     //raws traverse
      {
        if((GPIO_PORTE_DATA_R & 0x1E) & (1U << j+1))
          return symbol[j][i];
      }
    }
  }
  return 'q';
}