#ifndef __OSI_H__
#define __OSI_H__

#define Crystal_Clock 22118400L        // External Crystal oscillator
                                       // frequency (Hz)
                                       // NOTE: This value will determine the
                                       // XFCN bits in ExtCrystalOsc_Init ()

// Timer2 using SYSCLK/12 as its time base
// Timer2 counts 65536 SYSCLKs per Timer2 interrupt
// LED target flash rate = 10 Hz
//
// If Crystal_Clock is too slow to divide into a number of counts,
// <count> will always remain 0.
#define LED_interrupt_count Crystal_Clock/12/65536

/* Timer2 */
sfr16 RCAP2 = 0xCA;
sfr16 TMR2 = 0xCC;

sbit LED = P3^3;

void SYSCLK_Init (void);
void ExtCrystalOsc_Init (void);
void Timer2_Init (void);
void Timer2_ISR (void);

#endif

