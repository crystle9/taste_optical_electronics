#include <c8051f020.h>
#include "rudder.h"

void init_Timer0(void){
  
}

void init_PCA0(void){
  
}

void init_cex0(void){
  
}

void Rudder_Init(void){
  init_Timer0(); //PCA0��ʱ��Դ
  init_PCA0(); //cex0 �� cex1 PWM�����Ҫ��PWM����Ϊ20ms
  init_cex0(); //���ó�ʼ�Ƕ�(0.5ms,2.5ms)
}

void set_angel(unsigned char angel){
  
}
