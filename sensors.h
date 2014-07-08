#ifndef __SENSORS_H__
#define __SENSORS_H__

void Sensors_Init(void);

int get_OMRON_count(void);
int get_LD_reflection(void);
unsigned char get_infrared_status(void);

#endif

