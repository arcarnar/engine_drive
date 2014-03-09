
#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  if (CALBC1_16MHZ==0xFF)					// If calibration constant erased
   {
     while(1);                               // do not load, trap CPU!!
   }
   DCOCTL = 0;                               // Select lowest DCOx and MODx settings
   BCSCTL1 = CALBC1_16MHZ;                   // Set range
   DCOCTL = CALDCO_16MHZ;
  P2DIR |= ((1<<4)|(1<<2));                            // P1.2 and P1.3 output
  P2SEL |= ((1<<4)|(1<<2));     // P1.2 and P1.3 TA1/2 options
//  P2SEL2 |= ((1<<4)|(1<<2));
  TA1CCR0 = 512-1;                             // PWM Period
  TA1CCTL1 = OUTMOD_7;                         // CCR1 reset/set
  TA1CCTL2 = OUTMOD_7;
  TA1CCR1 = 384;                               // CCR1 PWM duty cycle
  TA1CCR2 = 128;
  TA1CTL = TASSEL_2 + MC_1;                  // SMCLK, up mode

  _BIS_SR(CPUOFF);                          // Enter LPM0
}
