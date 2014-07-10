#include <c8051F020.h>
#include "rudder.h"

#define MAX_ANGEL 30

void init_Timer0(void)
{
  TMOD |= 0x02;   //16位定时器方式
  TL0  = 0x70;
  TH0  = 0x70;    //50Hz的溢出频率
  //ET0  = 1;	     //允许定时器0中断
  //PT0=1;	 //优先级待定
  TR0  = 1;	
}

void init_PCA0(void)
{
  PCA0MD   = 0x04;  //选择定时器0溢出作为时钟源
}

void init_cex0(void)
{
  PCA0CPL0 = 0xED;
  PCA0CPH0 = 0xED;  //选择占空比,0.5ms(FA250)-1.5ms(ED237)-2.5ms(E0224)
  PCA0CPM0 = 0x42;  //工作在PWM8位脉冲宽度调制方式
}

void Rudder_Init(void)
{
  init_Timer0(); //PCA0的时钟源
  init_PCA0(); //cex0 和 cex1 PWM输出，要求PWM周期为20ms
  init_cex0(); //设置初始角度(0.5ms-90度,2.5ms90度)
}

void set_angel(char angel)
{
  unsigned char ang_temp;    //暂存计算得到的初值	

  ang_temp = angel * MAX_ANGEL / 900 + 237; // -MAX_ANGEL -> MAX_ANGEL
  PCA0CPH0 = ang_temp;
}
/*
void Timer0INT(void) interrupt 1 using 3
{
  TR0=0;
  TL0=0x6D;
  TH0=0x80;  //重装载
  TR0=1;
}
*/
