#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"

#include "calculator.h"
#include "mode.h"



int firstNum = 0;
int secondNum = 0;
char operation = 'N';
int answer = 0;



void show_answer(){
    
  char answerStr[10];

  sprintf(answerStr, "%d", answer);
  
  LCD_Clear();
  LCD_PrintLn(0,"Calculator Mode");
  
  LCD_PrintLn(1,answerStr);
    
  firstNum = 0;
  secondNum = 0;
  operation = 'N';
}



void calc(){
    
  switch (operation){
  
  case '+':
    answer = firstNum + secondNum;
    show_answer();
    break;
  case '-':
    answer = firstNum - secondNum;
    show_answer();
    break;
  case 'x':
    answer = firstNum * secondNum;
    show_answer();
    break;
  case '/':
    answer = firstNum / secondNum;
    show_answer();
    break;    
    
  default:
    break;
  
  
  
  }

}



void calcMode(){
        int i = 0;
        volatile char key;
        LCD_PrintLn(0,"Calculator Mode");
        SysCtlDelay(80000000/3); //Delay
        LCD_Cursor(1,i);
        i++;

        
        while (state == calculator) {
           if (getmodebutton()==0){
              state = timer;
              printf("%d",state); 
              
           } 
           key = keypad_getkey();
           

           
           if(key == 'c'){
              answer = 0;
              i=0;
              LCD_Clear();
              LCD_PrintLn(0,"Calculator Mode");
              LCD_Cursor(1,i);
              i++;
//              continue;
           }
           
           if ((key != '+' && key != '-' && key != '/' && key != '=' && key != 'x') && (operation == 'N')){
                
//                printf("%s","first number is = ");           
                firstNum = (firstNum*10) + (((int)(key))-48);
//                printf("%d\n",firstNum);  
             
           }
           else if ((key != '+' && key != '-' && key != '/' && key != '=' && key != 'x') && (operation != 'N')){
//                printf("%s","second number is = "); 
                secondNum = (secondNum*10) + (((int)(key))-48);
//                printf("%d\n",secondNum);             
           }
           
           else if ( key == '=' ){          
              calc();
//              continue;
                
           }
           
           else if((key == '+' || key == '-' || key == '/' || key == '=' || key == 'x')){
              
             operation = key;
//             printf("%c\n",operation);              
           }
           
           else {}

           LCD_Show(key);
           LCD_Cursor(1,i);
           i++;
           SysCtlDelay(8000000/3); //Delay              
//           state = timer; 
           delay_ms(200);


        }
        
        
      LCD_Clear();
      LCD_PrintLn(0,"Timer Mode");
      LCD_PrintLn(1,"00:00");      

        
        
        
        
        
}