#include <c8051f020.h>
#include "motor.h"

void init_cex1(void)
{
  PCA0CPL1 = 0xE0;
  PCA0CPH1 = 0xE0;  //ѡ��ռ�ձ�
  PCA0CPM1 = 0x42;  //������PWM8λ�����ȵ��Ʒ�ʽ 
}

void Motor_Init(void){
  init_cex1();
}

