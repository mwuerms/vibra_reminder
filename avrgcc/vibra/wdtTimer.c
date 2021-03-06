/**
 * Martin Wuerms
 * 2015-10-18
 *
 */

/* - includes --------------------------------------------------------------- */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "arch.h"
#include "wdtTimer.h"

/* - defines ---------------------------------------------------------------- */

/* - typedef ---------------------------------------------------------------- */

/* - variables -------------------------------------------------------------- */
static volatile uint8_t wdt_timeout, wdt_event_flag;

/* - private functions ------------------------------------------------------ */

/**
 * stop wdtTimer
 */
static inline void wdtTimer_Stop(void) {
    WDTCR = (1 << WDCE);
    WDTCR = 0;
}

/**
 * watchdog ISR
 */
ISR(WDT_vect) {
    if(wdt_timeout > 1) {   // so "wdtTimer_StartTimeout(1, ...)" does result in delay of 1 and not 2 wdt periodes
        wdt_timeout--;
    }
    else {
        wdtTimer_Stop();
        global_events |= wdt_event_flag;
    }
}

/* - public functions ------------------------------------------------------- */

/**
 * start the wdtTimer
 * @param   timeout     overall timeout = interval * timeout
 */
void wdtTimer_StartTimeout(uint8_t timeout, uint8_t interval, uint8_t event_flag) {
    uint8_t sr;
    lock_interrupt(sr);
    wdt_timeout = timeout;
    wdt_event_flag = event_flag;
    WDTCR = (1 << WDCE) | (1 << WDIF);
    WDTCR = (interval & 0x07);
    WDTCR |= (1 << WDIE);
    restore_interrupt(sr);
}
