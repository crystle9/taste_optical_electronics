#include <c8051F020.h>
#include "measurement.h"

sbit P31 = P3^1;

init_Timer1(void)
{
  TMOD |= 0x60; //8位计数器
  TL1 = 0x00;
  TH1 = 0x00;
  TR1 = 1;
}

init_Timer2(void)
{
  CPRL2 = 0; //重装载
  CT2 = 1; //计数T2引脚脉冲
  EXEN2 = 0; //T2EX引脚负跳变捕捉
  ET2 = 0; //允许中断
  TR2 = 0;
}

init_Timer4(void)
{
  T4CON = 0x06; // CT4,TR4 = 1
}

init_EX6(void)
{
  P3IF = 0x00;
  EIP2 |= 0x10;
  EIE2 |= 0x10;
  tunnel_count = 0;
}

init_EX7(void)
{
  P3IF = 0x00;
  EIE2 |= 0x20;
  LD2_count = 0;
}

void Measurement_Init(void)
{
  unsigned char i;

  for(i = 0; i < 20; i++)
    tunnel_length[i] = 0;
  
  init_Timer1();
  init_Timer2();
  init_Timer4();
  init_EX6();
  init_EX7();
}

int Get_OMRON_Count(void)
{
  return TH4 * 256 + TL4;
}

void Clear_OMRON_Count(void)
{
  T4CON = 0x02; // CT4 = 1,TR4 = 0
  TL4 = 0;
  TH4 = 0;
  T4CON = 0x06; // CT4,TR4 = 1
}

void Tunnel_ISR(void) interrupt 18
{
  if(P3IF & 0x04){
    // leave tunnel
    TR2 = 0; // stop counting OMRON
    
    tunnel_length[tunnel_count] = TH2*256 + TL2;
    if(++tunnel_count > 4)
      P31 = 0;
    
    TR1 = 1; // start LD1 counting(Timer1)
    EIE2 |= 0x20; // enable LD2 counting(EX7)
    P3IF = 0x00; // clear interrupt flag, waiting next tunnel
  }else{
    // get into tunnel
    TH2 = 0x00;
    TL2 = 0x00;
    TR2 = 1; // start counting OMRON
    TR1 = 0; // stop LD1 counting
    EIE2 &= 0xDF; // disable LD2 counting
    P3IF = 0x04; // clear interrupt flag, waiting exit
  }
}

void LD2_Find_a_Tree_ISR(void) interrupt 19
{
  LD2_count++;
  P3IF = 0x00;
}
