#include <c8051F020.h>
#include "osi.h"
#include "oled.h"
#include "rudder.h"
#include "motor.h"
#include "sensors.h"
#include "measurement.h"
#include "test_helper.h"

#define SPI_CLOCK 320000 // 320kHz
#define MAX_REFLECTION 102
#define RUDDER_FIX 10
#define M_ANGEL 75

unsigned char current_line; // used by test_helper module

unsigned char LD2_count; // used by measurement module
unsigned int xdata tunnel_length[20];

#define LEFT3 P24
#define LEFT2 P20
#define LEFT1 P21
#define RIGHT1 P22
#define RIGHT2 P23
#define RIGHT3 P25
#define DIRECTION P30

sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P30 = P3^0;

void Port_Init (void);
void SPI0_Init(void);
void PCA0_Init(void);

void main (void) 
{
  int reflection,LDs_count,omron_count;

  char angel;
  unsigned char reflect;
  char flag;
  
  WDTCN = 0xDE;                       // disable watchdog timer
  WDTCN = 0xAD;

  SYSCLK_Init ();                     // Initialize system clock to 16MHz
  ExtCrystalOsc_Init ();              // switch system clock
  Port_Init ();                       // Initialize crossbar and GPIO
  SPI0_Init();
  LED_Init();                         // Initialize OLED
  Sensors_Init();
  Rudder_Init();
  Motor_Init();
  Measurement_Init();
  Test_Helper_Init();

  EA = 1;                             // Enable global interrupts
  CR = 1;                             // start to output PWM

  PUT_LINE("OMRON:",omron_count);
  PUT_LINE("reflection:",reflection);
  PUT_LINE("LDs_count:",LDs_count);
  PUT_LINE("Tunnel:",tunnel_length[0]);
  PUT_LINE("angel:",angel);

  while (1) {                         // Spin forever
    // go straight forward: PID
    DIRECTION = 0;
    PCA0CPH1 = 0xD0;
    while (1) {
      // dectecting
      reflect = get_LD_reflection();

      if(MAX_REFLECTION > reflect)
	angel = MAX_REFLECTION - reflect;
      else
	angel = 0;
      flag = 0;
      UPDATE_VALUE(4,angel);
      if(angel > M_ANGEL){
	if(!LEFT3)
	  flag = 1;
	if(!RIGHT3)
	  flag = -1;
	if(flag)
	  break;
      }
      if(!LEFT1 || !LEFT2 || !LEFT3)
	flag = 1;
      if(!RIGHT1 || !RIGHT2 || !RIGHT3)
	flag = -1;
      set_angel(flag * angel + RUDDER_FIX);

      // debug info
      omron_count = Get_OMRON_Count();
      reflection = get_LD_reflection();
      LDs_count = TL1 + LD2_count;
      UPDATE_VALUE(0,omron_count);
      UPDATE_VALUE(1,reflection);
      UPDATE_VALUE(2,LDs_count);
      UPDATE_VALUE(3,tunnel_length[LD2_count]);
    }

    // get through cornner
    DIRECTION = 1;
    PCA0CPH1 = 0x3F;
    Clear_OMRON_Count();
    set_angel(-flag * 127);
    while(1){
      omron_count = Get_OMRON_Count();
      UPDATE_VALUE(0,omron_count);
      if(omron_count >= 320) //1062
	break;
    }
    DIRECTION = 0;
    PCA0CPH1 = 0xC0;
    Clear_OMRON_Count();
    set_angel(flag * 127);
    while(1){
      omron_count = Get_OMRON_Count();
      UPDATE_VALUE(0,omron_count);
      if(omron_count >= 600)//2124
	break;
    }
  }
}

//-----------------------------------------------------------------------------
// Port_Init ()
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the Crossbar and GPIO ports.
//
/*
 - D0   数字I/O   推挽   CLK   P0.0    OLED
 - D1	数字I/O	  推挽	 MOSI  P0.2
 - IN2  数字I/O   推挽   CEX0  P0.4    rudder PWM0
 - DJ3  数字I/O   推挽   CEX1  P0.5    motor PWM1
 - ?    ?	  ?      CEX2  P0.6
 - ?    ?	  ?      CEX3  P0.7
 - AD0	模拟输入  漏开	 AIN1  P1.0    LD0
 - LD2	数字I/O	  漏开	 T1    P1.1    count trees
 - 黑   数字I/O   漏开   T2    P1.2    OMRON
 - LD1  数字I/O   漏开   T2EX  P1.3    get off tunnel signal
 - 白   数字I/O   漏开   T4    P1.4    count OMRON
 - RST	数字I/O	  推挽	 I/O   P1.5    OLED reset
 - DC	数字I/O	  推挽	 I/O   P1.6    OLED data/command
 - EN   数字I/O   推挽   I/O   P1.7    功放允许位
 - D3-6 数字I/O   漏开   I/O   P2:0-3  infrared
 - IN1  数字I/O   推挽   I/O   P3.0    forward or backward
 - LD1	数字I/O	  漏开	 EX6   P3.6    get into tunnel signal
 - D7	数字I/O	  漏开	 EX7   P3.7    stop signal

 */
// P3.3   digital   push-pull     LED
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
  P0MDOUT = 0x35;
  P1MDOUT = 0xE0;
  //P2MDOUT = 0x00;
  P3MDOUT = 0x01;

  P0 = 0x00;
  P1 = 0x1F;
  P2 = 0xFF;
  P3 = 0xC0;

  P1MDIN = 0xFE;
  
  XBR0 = 0x22;
  XBR1 = 0x68;
  XBR2 = 0x48;                        // Enable crossbar and weak pull-ups
}

void SPI0_Init()
{
  SPI0CFG   = 0x07;                   // CKPHA = '0', CKPOL = '0'
  // SPI transmits 8 bits
  SPI0CN    = 0x03;                   // Master, SPI enabled

  // SPI clock frequency equation from the datasheet
  SPI0CKR   = (Crystal_Clock/(2*SPI_CLOCK))-1;
}

//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

