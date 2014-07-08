#include <c8051F020.h>
#include "osi.h"
#include "delay.h"
#include "oled.h"
#include "rudder.h"
#include "motor.h"
#include "sensors.h"
#include "test_helper.h"

#define SPI_CLOCK 320000 // 320kHz

unsigned char current_line; // used by test_helper module

void Port_Init (void);
void SPI0_Init(void);
void PCA0_Init(void);

void main (void) 
{
  unsigned char reflection;
  
  WDTCN = 0xDE;                       // disable watchdog timer
  WDTCN = 0xAD;

  SYSCLK_Init ();                     // Initialize system clock to 16MHz
  ExtCrystalOsc_Init ();              // switch system clock
  Port_Init ();                       // Initialize crossbar and GPIO
  Timer2_Init ();                     // Timer2: interrupt to blink LED.
  SPI0_Init();
  LED_Init();                         // Initialize OLED
  Sensors_Init();
  Test_Helper_Init();

  EA = 1;                             // Enable global interrupts
  PUT_LINE("OMRON:",get_OMRON_count());
  PUT_LINE("infrared:",get_infrared_status());
  PUT_LINE("reflection:",get_LD_reflection());
  while (1) {                         // Spin forever
    reflection = get_LD_reflection();
    UPDATE_VALUE(2,reflection);
    delay1ms(250);
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
 - D0   ����I/O   ����   CLK   P0.0    OLED
 - D1	����I/O	  ����	 MOSI  P0.2
 - IN1  ����I/O   ����   CEX0  P0.4    rudder PWM0
 - DJ3  ����I/O   ����   CEX1  P0.5    motor PWM1
 - ?    ?	  ?      CEX2  P0.6
 - ?    ?	  ?      CEX3  P0.7
 - AD0	ģ������  ©��	 AIN1  P1.0    LD0
 - ?	ģ������  ©��	 AIN2  P1.1
 - LD2	����I/O	  ©��	 T1    P1.2    count trees
 - ��   ����I/O   ©��   T2    P1.3    OMRON
 - LD1  ����I/O   ©��   T2EX  P1.4    get off tunnel signal
 - RST	����I/O	  ����	 I/O   P1.5    OLED reset
 - DC	����I/O	  ����	 I/O   P1.6    OLED data/command
 - D3-6 ����I/O   ©��   I/O   P2:0-3  infrared
 - LD1	����I/O	  ©��	 EX6   P3.6    get into tunnel signal
 - D7	����I/O	  ©��	 EX7   P3.7    stop signal

 */
// P3.3   digital   push-pull     LED
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
  P0MDOUT = 0x35;
  P1MDOUT = 0x60;
  //P2MDOUT = 0x00;
  //P3MDOUT = 0x00;

  P1MDIN = 0x03;
  
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
