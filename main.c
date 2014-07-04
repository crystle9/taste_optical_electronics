#include <c8051F020.h>
#include "osi.h"
#include "delay.h"
#include "oled.h"
#include "rudder.h"
#include "motor.h"

#define LED_interrupt_count Crystal_Clock/12/65536
#define SPI_CLOCK 320000 // 320kHz

/* Timer2 */
sfr16 RCAP2 = 0xCA;
sfr16 TMR2 = 0xCC;

sbit LED = P3^3;

void Port_Init (void);
void Timer2_Init (void);
void SPI0_Init(void);

void OLED_Display(void); 

void Timer2_ISR (void);

void main (void) 
{
  int speed, angel;
  
  WDTCN = 0xDE;                       // disable watchdog timer
  WDTCN = 0xAD;

  SYSCLK_Init ();                     // Initialize system clock to 16MHz
  ExtCrystalOsc_Init ();              // switch system clock
  Port_Init ();                       // Initialize crossbar and GPIO
  Timer2_Init ();                     // Timer2: interrupt to blink LED.
  SPI0_Init();
  LED_Init();                         // Initialize OLED

  EA = 1;                             // Enable global interrupts

  //OLED_Display();
  display_angels();
  display_speeds();
  while (1) {                         // Spin forever
    speed = get_current_speed();
    angel = get_current_angel();
    set_speed(calc_speed(speed));
    set_angel(calc_angel(angel));
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
// P0.0   digital   push-pull     /SYSCLK
// P3.3   digital   push-pull     LED
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
  P0MDOUT |= 0x35;                    // Enable CLK,MOSI,RST,DC as a push-pull output

  P3MDOUT |= 0x08;                    // Enable LED as a push-pull output

  XBR0 = 0x02;                        // Route SPI0 to a port pin
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
// Timer2_Init ()
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure Timer2 to 16-bit auto-reload and generate an interrupt after the
// maximum possible time (TMR2RL = 0x0000).
//
//-----------------------------------------------------------------------------
void Timer2_Init (void)
{
  T2CON = 0x00;                       // Stop Timer2; Clear TF2;
  // auto-reload mode

  CKCON &= ~0x20;                     // use SYSCLK/12 as timebase

  RCAP2 = 0x0000;                     // Init reload value
  TMR2 = 0xffff;                      // Set to reload immediately

  ET2 = 1;                            // Enable Timer2 interrupts

  TR2 = 1;                            // Start Timer2
}

void OLED_Display(void)
{
  unsigned int i;

  LED_P14x16Str(25, 0, (unsigned char*)"信意电子科技");
  LED_P8x16Str(0, 2, (unsigned char*)" http://xydz123.taobao.com");
  delay1ms(4);

  LED_Fill(0x00);    
  LED_P14x16Str(30, 1, (unsigned char*)"屏幕测试");

  for (i = 0; i <= 100; i++)
    {
      delay10us(4);
      LED_PrintChar(45, 5, (char)i);        
    }
  delay1ms(8);

  LED_Fill(0xFF); //点亮全屏
  delay1ms(8);

  LED_Fill(0x00); //黑屏
  delay1ms(2);

  LED_P8x16Str(10, 2, (unsigned char*)"Test Finished!");

  return;
}



//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Timer2_ISR
//-----------------------------------------------------------------------------
//
// This routine changes the state of the LED whenever Timer2 overflows.
//
//-----------------------------------------------------------------------------
void Timer2_ISR (void) interrupt 5
{
  static unsigned int count = 0;

  TF2 = 0;                            // Clear Timer2 interrupt flag

  if (count == LED_interrupt_count)
    {
      LED = ~LED;                      // Change state of LED

      count = 0;
    }
  else
    {
      count++;
    }
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
