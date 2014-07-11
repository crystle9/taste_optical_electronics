#include <c8051f020.h>
#include "motor.h"

void init_cex1(void)
{
  PCA0CPL1 = 0xD0;
  PCA0CPH1 = 0xD0;  //选择占空比
  PCA0CPM1 = 0x42;  //工作在PWM8位脉冲宽度调制方式 
}

void Motor_Init(void){
  init_cex1();
}

