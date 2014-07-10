#include <c8051F020.h>
#include "delay.h"

#if 0
#include "osi.h"
#define DELAY_1S_COUNT Crystal_Clock/12/256/1000
#define DELAY_1MS_COUNT Crystal_Clock/12/256/1000
#define DELAY_10US_COUNT Crystal_Clock/12/100000

void delay1ms(unsigned char count)
{
  unsigned char i;

  TMOD = 0x02;
  TH0 = 0xFF;
  TL0 = 0xFF;
  TF0 = 0;
  i = count * DELAY_1MS_COUNT;
  while(i-- == 0){
    TR0 = 1;
    while(!TF0);
    TR0 = 0;
    TF0 = 0;
  }
}

void delay10us(unsigned char count)
{
  TMOD = 0x02;
  TH0 = count * DELAY_10US_COUNT;
  TL0 = count * DELAY_10US_COUNT;
  TF0 = 0;
  TR0 = 1;
  while(!TF0);
  TR0 = 0;
  TF0 = 0;
}
#endif
