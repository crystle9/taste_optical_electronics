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

int get_LD_reflection(void)
{
  ADC1CN &= 0xDF;
  ADC1CN |= 0x10;
  while(!(ADC1CN & 0x20));
  return (int*)ADC1;
}

unsigned char get_infrared_status(void)
{
  return P2;
}

void init_OMRON(void)
{
  
}

void init_LD(void)
{
  ADC1CF = 0x18;
  AMX1SL = 0x00;
  ADC1CN = 0x80;
}

void init_infrared(void)
{
  P2 = 0xFF;
}

