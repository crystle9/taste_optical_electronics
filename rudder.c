#include <c8051f020.h>
#include <stdio.h>
#include "rudder.h"
#include "oled.h"

int get_current_angel(void){
  return 50;
}

int calc_angel(int angel){
  return angel + 10;  
}

void set_angel(int angel){
  
}

void display_angels(){
  int xdata angel;
  unsigned char xdata current_angel[16];
  unsigned char xdata pid_angel[16];

  angel = get_current_angel();
  sprintf(current_angel, "%d", angel);
  sprintf(pid_angel, "%d", calc_angel(angel));
  LED_Fill(0x00);
  LED_P8x16Str(0, 0, "current_angel: ");
  LED_P8x16Str(2, 1, current_angel);
  LED_P8x16Str(0, 2, "pid_angel: ");
  LED_P8x16Str(2, 3, pid_angel);
}
