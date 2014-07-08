#include <c8051f020.h>
#include "rudder.h"

void init_Timer0(void){
  
}

void init_PCA0(void){
  
}

void init_cex0(void){
  
}

void Rudder_Init(void){
  init_Timer0(); //PCA0的时钟源
  init_PCA0(); //cex0 和 cex1 PWM输出，要求PWM周期为20ms
  init_cex0(); //设置初始角度(0.5ms,2.5ms)
}

void set_angel(unsigned char angel){
  
}
