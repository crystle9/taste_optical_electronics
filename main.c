#include <c8051F020.h>
#include "osi.h"
#include "oled.h"
#include "rudder.h"
#include "motor.h"
#include "sensors.h"
//#include "measurement.h"
#include "test_helper.h"

#define SPI_CLOCK 320000 // 320kHz
#define MAX_REFLECTION 126

unsigned char current_line; // used by test_helper module

unsigned char LD2_count; // used by measurement module
unsigned int xdata tunnel_length[20];

void Port_Init (void);
void SPI0_Init(void);
void PCA0_Init(void);

void main (void) 
{
  int reflection, status, LDs_count,omron_count;
  unsigned char angel,stat;
  
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
  //Measurement_Init();
  Test_Helper_Init();

  EA = 1;                             // Enable global interrupts
  CR = 1;                             // start to output PWM

  reflection = 0;
  status = 0;
  LDs_count = 0;
  status += get_infrared_status();
  reflection += get_LD_reflection();
  LDs_count += TL1 + LD2_count;
  PUT_LINE("OMRON:",omron_count);
  PUT_LINE("infrared:",status);
  PUT_LINE("reflection:",reflection);
  PUT_LINE("LDs_count:",LDs_count);
  PUT_LINE("Tunnel:",tunnel_length[LD2_count]);
  while (1) {                         // Spin forever
    status = 0;
    reflection = 0;
    LDs_count = 0;

    status += get_infrared_status();
    reflection += get_LD_reflection();
    LDs_count += TL1 + LD2_count;

    angel = MAX_REFLECTION - get_LD_reflection();
    switch (status & 0x06)
      {
      case 0x02:
	set_angel(0x80 + angel);
	break;
      case 0x04:
	set_angel(0x80 - angel);
	break;
      case 0x00:
	set_angel(0x80 + angel);
	break;
      default:
	set_angel(0x80);
	break;
      }

    UPDATE_VALUE(1,status);
    UPDATE_VALUE(2,reflection);
    UPDATE_VALUE(3,LDs_count);
    UPDATE_VALUE(4,tunnel_length[LD2_count]);
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
 - IN1  数字I/O   推挽   CEX0  P0.4    rudder PWM0
 - DJ3  数字I/O   推挽   CEX1  P0.5    motor PWM1
 - ?    ?	  ?      CEX2  P0.6
 - ?    ?	  ?      CEX3  P0.7
 - AD0	模拟输入  漏开	 AIN1  P1.0    LD0
 - ?	模拟输入  漏开	 AIN2  P1.1
 - LD2	数字I/O	  漏开	 T1    P1.2    count trees
 - 黑   数字I/O   漏开   T2    P1.3    OMRON
 - LD1  数字I/O   漏开   T2EX  P1.4    get off tunnel signal
 - RST	数字I/O	  推挽	 I/O   P1.5    OLED reset
 - DC	数字I/O	  推挽	 I/O   P1.6    OLED data/command
 - EN   数字I/O   推挽   I/O   P1.7    功放允许位
 - D3-6 数字I/O   漏开   I/O   P2:0-3  infrared
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
  //P3MDOUT = 0x00;

  P0 = 0x00;
  P1 = 0x1F;
  P2 = 0xFF;
  P3 = 0xC0;

  P1MDIN = 0xFC;
  
  XBR0 = 0x22;
  XBR1 = 0x68;
  XBR2 = 0x40;                        // Enable crossbar and weak pull-ups
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
