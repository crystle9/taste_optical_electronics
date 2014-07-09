#include <c8051F020.h>
#include "sensors.h"

void init_OMRON(void);
void init_LD(void);
void init_infrared(void);

void Sensors_Init()
{
  init_OMRON();
  init_LD();
  init_infrared();
}

int get_OMRON_count(void)
{
  return 0;
}

unsigned char get_LD_reflection(void)
{
  unsigned char reflection;
  
  ADC1CN &= 0xDF; //AD1INT = 0
  ADC1CN |= 0x10; //AD1BUSY = 1, start conversion
  while(!(ADC1CN & 0x20)); //until AD1INT == 1
  reflection = ADC1;
  return reflection;
}

unsigned char get_infrared_status(void)
{
  unsigned char status;
  status = P2;
  status &= 0x0F;
  return status;
}

void init_OMRON(void)
{
  
}

void init_LD(void)
{
  AMX1SL = 0x00;
  ADC1CF = 0x00;
  ADC1CN = 0x80;
  REF0CN = 0x02;
}

void init_infrared(void)
{
  P2 = 0xFF;
}

