#include <c8051f020.h>
#include <stdio.h>
#include "motor.h"
#include "oled.h"

int get_current_speed(void){
  return 500;
}

int calc_speed(int speed){
  return speed - 10;
}
void set_speed(int speed){
    
}

void display_speeds(){
  
}
