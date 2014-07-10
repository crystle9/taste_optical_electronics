#include <c8051F020.h>
#include "test_helper.h"
#include "oled.h"

void Test_Helper_Init(){
  LED_Fill(0x00);
  current_line = 0;
}

void _put_line(int value){

  LED_PrintShort(90, current_line, value);

  if(++current_line > 7){
    Test_Helper_Init();
  }
}

void general_delay(void)
{
  TMR3L = 0x00;
  TMR3H = 0x00;
  TMR3CN = 0x00;
  TMR3CN |= 0x04; //TR3 = 1
  while(!(TMR3CN & 0x80));
  TMR3CN = 0x00;
}
