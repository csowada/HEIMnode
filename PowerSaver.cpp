#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include "PowerSaver.h"

void PowerSaverClass::powerDown8s(uint8_t loops)
{
  //Needed for delay_ms
  power_timer0_disable();

  // shut down ADC
  uint8_t keep_ADCSRA = ADCSRA;
  uint8_t keep_ACSR = ACSR;

  ADCSRA = 0;
  ACSR = (1 << ACD); //Disable the analog comparator

  // Go to sleep for 1 second (with code from Nick Gammon)
  // clear various "reset" flags
  MCUSR = 0;
  // allow changes, disable reset
  WDTCSR |= _BV(WDCE) | _BV(WDE);

  wdt_enable(WDTO_8S);
  //WDTCSR |= (1 << WDIE);
  WDTCSR |= _BV(WDIE);
  
  for (uint8_t i = 1; i < loops; i++) {
    
    wdt_reset();  // pat the dog

    set_sleep_mode (SLEEP_MODE_PWR_DOWN);
    
    cli();
    sleep_enable();

    // turn off brown-out enable in software
    //MCUCR = _BV (BODS) | _BV (BODSE);  // turn on brown-out enable select
    //MCUCR = _BV (BODS);        // this must be done within 4 clock cycles of above
    
    sleep_bod_disable();
    sei();
    sleep_cpu();

    // **** SLEEP ****

    // continues here after wakeup
    // cancel sleep as a precaution
    sleep_disable();
  }

  ADCSRA = keep_ADCSRA;
  ACSR = keep_ACSR;

  power_timer0_enable(); //Needed for delay_ms
}

/*******************************************************************************
* Name: ISR (WDT_vect)
* Description: Watchdog Timer interrupt service routine. This routine is
*		           required to allow automatic WDIF and WDIE bit clearance in
*			         hardware.
*
*******************************************************************************/
ISR (WDT_vect)
{
  // WDIE & WDIF is cleared in hardware upon entering this ISR
  wdt_disable();
}

PowerSaverClass PowerSaver;
