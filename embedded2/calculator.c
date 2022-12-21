#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"

#include "calculator.h"
#include "mode.h"

/*THIS IS THE CALCULATOR MODE .c FILE*/

// variables used in calculations 
static float firstNum = 0;
static float secondNum = 0;
static char operation = 'N';
static float answer = 0;

extern volatile int state;

//This function transforms the answer variable (int) into string so it can be displayed on the LCD
void show_answer(){
    
  char answerStr[10];
  //int to str
  sprintf(answerStr, "%f", answer);
  
  LCD_Clear();
  LCD_PrintLn(0,"Calculator Mode");
  
  LCD_PrintLn(1,answerStr);
    
  firstNum = 0;
  secondNum = 0;
  operation = 'N';
}


//This functions simply performs the calculation on firstNum and secondNum using operation used
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


// This is the main loop for this mode which enables user to enter digits and operation and construct numbers from string passed to LCD from keypad
// This loop stays in the calculator mode as long as global external state variable is 1

void calcMode(){
        int i = 0;
        volatile char key;
        LCD_PrintLn(0,"Calculator Mode");
        
        //show last stored answer
        
        char answerStr[9];
        char lastanswerstr[] = "Last Ans:";
        sprintf(answerStr, "%f", answer);
        strcat(lastanswerstr,answerStr);
        LCD_PrintLn(1,lastanswerstr);
        firstNum=0;
        secondNum=0;
        LCD_Cursor(1,i);
        i++;
        
        
        while (state == 1) {
          
           
          // get value from keypad
           key = keypad_getkeycalc();
           
           if(key == 'q'){continue;}
           
           //clear screen
           if(key == 'c'){
              i=0;
              LCD_Clear();
              LCD_PrintLn(0,"Calculator Mode");
              LCD_Cursor(1,i);
              i++;
              firstNum=0;
              secondNum=0;
              continue;
           }
           //user entered a digit an has not yet entered an operation so its the first number 
           if ((key != '+' && key != '-' && key != '/' && key != '=' && key != 'x') && (operation == 'N')){
                           
                firstNum = (firstNum*10) + (((int)(key))-48);
             
           }
           //user entered a digit after entering an operation so its the second number
           else if ((key != '+' && key != '-' && key != '/' && key != '=' && key != 'x') && (operation != 'N')){

                secondNum = (secondNum*10) + (((int)(key))-48);
           
           }
           //calculate
           else if ( key == '=' ){          
              calc();
              continue;
                
           }
           //user entered a mathematical operation
           else if((key == '+' || key == '-' || key == '/' || key == '=' || key == 'x')){
              
             operation = key;            
           }
           
           else {}

           LCD_Show(key);
           LCD_Cursor(1,i);
           i++;
           SysCtlDelay(8000000/3); //Delay              
           delay_ms(200);


        }
        
   
        
}