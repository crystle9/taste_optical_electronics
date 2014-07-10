#include <c8051F020.h>
#include "rudder.h"

#define MAX_ANGEL 30

void init_Timer0(void)
{
  TMOD |= 0x02;   //16λ��ʱ����ʽ
  TL0  = 0x70;
  TH0  = 0x70;    //50Hz�����Ƶ��
  //ET0  = 1;	     //����ʱ��0�ж�
  //PT0=1;	 //���ȼ�����
  TR0  = 1;	
}

void init_PCA0(void)
{
  PCA0MD   = 0x04;  //ѡ��ʱ��0�����Ϊʱ��Դ
}

void init_cex0(void)
{
  PCA0CPL0 = 0xED;
  PCA0CPH0 = 0xED;  //ѡ��ռ�ձ�,0.5ms(FA250)-1.5ms(ED237)-2.5ms(E0224)
  PCA0CPM0 = 0x42;  //������PWM8λ�����ȵ��Ʒ�ʽ
}

void Rudder_Init(void)
{
  init_Timer0(); //PCA0��ʱ��Դ
  init_PCA0(); //cex0 �� cex1 PWM�����Ҫ��PWM����Ϊ20ms
  init_cex0(); //���ó�ʼ�Ƕ�(0.5ms-90��,2.5ms90��)
}

void set_angel(char angel)
{
  unsigned char ang_temp;    //�ݴ����õ��ĳ�ֵ	

  ang_temp = angel * MAX_ANGEL / 900 + 237; // -MAX_ANGEL -> MAX_ANGEL
  PCA0CPH0 = ang_temp;
}
/*
void Timer0INT(void) interrupt 1 using 3
{
  TR0=0;
  TL0=0x6D;
  TH0=0x80;  //��װ��
  TR0=1;
}
*/
