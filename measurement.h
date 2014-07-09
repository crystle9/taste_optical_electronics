#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__

void Measurement_Init(void);
void Get_Into_Tunnel_ISR(void);
void Leave_Tunnel_ISR(void);

extern unsigned char LD2_count;
extern unsigned int xdata tunnel_length[20];

#endif

