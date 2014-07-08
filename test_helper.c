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

