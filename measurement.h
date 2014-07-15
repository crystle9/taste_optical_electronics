#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__

void Measurement_Init(void);
//void Get_Into_Tunnel_ISR(void);
void Tunnel_ISR(void);
int Get_OMRON_Count(void);
void Clear_OMRON_Count(void);

extern unsigned char LD2_count;
extern unsigned char tunnel_count;
extern unsigned int xdata tunnel_length[20];

#endif

