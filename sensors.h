#ifndef __SENSORS_H__
#define __SENSORS_H__

void Sensors_Init(void);

unsigned char get_LD_reflection(void);
unsigned char get_infrared_status(void);

#endif

