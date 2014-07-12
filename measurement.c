#include <c8051F020.h>
#include "measurement.h"

init_Timer1(void)
{
  TMOD |= 0x60; //8λ������
  TL1 = 0x00;
  TH1 = 0x00;
  TR1 = 1;
}

init_Timer2(void)
{
  CPRL2 = 1; //ѡ��׽
  CT2 = 1; //����T2��������
  EXEN2 = 1; //T2EX���Ÿ����䲶׽
  ET2 = 1; //�����ж�
  TR2 = 0;
}

init_Timer4(void)
{
  T4CON = 0x06; // CT4,TR4 = 1
}

init_EX6(void)
{
  P3IF = 0x04; //�����ش���
  EIP2 |= 0x10; //������
  EIE2 |= 0x10; //�����ж�
}

init_EX7(void)
{
  P3IF |= 0x08;
  EIP2 |= 0x20;
  EIE2 |= 0x20;
}

void Measurement_Init(void)
{
  LD2_count = 0;
  tunnel_length[0] = 0;
  init_Timer1();
  init_Timer2();
  init_Timer4();
  init_EX6();
  init_EX7();
}

void Leave_Tunnel_ISR(void) interrupt 5
{
  EXF2 = 0;
  TR2 = 0;
  tunnel_length[LD2_count] = RCAP2H*256 + RCAP2L;
  if(++LD2_count > 19)
    LD2_count = 0;
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


//void Get_Into_Tunnel_ISR(void) interrupt 18
void Get_Into_Tunnel_ISR(void) interrupt 19
{
  TH2 = 0x00;
  TL2 = 0x00;
  TR2 = 1;
  P3IF = 0x08;
}
