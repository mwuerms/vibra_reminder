/**
 * Martin Egli
 * 2021-03-06
 *
 * attiny85 pin description
 * name     pin     functions (attiny85)
 * PB0      5       (MOSI/DI/SDA/AIN0/OC0A/OC1A/AREF/PCINT0)
 * PB1      6       (MISO/DO/AIN1/OC0B/OC1A/PCINT1)
 * PB2      7       (SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)
 * PB3      2       (PCINT3/XTAL1/CLKI/OC1B/ADC3)
 * PB4      3       (PCINT4/XTAL2/CLKO/OC1B/ADC2)
 * PB5      1       (PCINT5/RESET/ADC0/dW)
 * VCC      8       2.7 ... 5.5 V
 * GND      4
 *
 * pin usage on project "vibra"
 * name     signal
 * PB0      switch, pullup
 * PB1      switch, pullup
 * PB2      en vibra motor
 * PB3      unused, debug out
 * PB4      led out
 * PB5      Reset
 */

/* - includes --------------------------------------------------------------- */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <string.h>
#include "arch.h"
#include "wdtTimer.h"
#include "vbat.h"

/* - typedefs --------------------------------------------------------------- */
//typedef void *(* state_handler_t)(void);

/* - defines ---------------------------------------------------------------- */
#define GPIO_SWITCH0_IN _BV(0)
#define GPIO_SWITCH1_IN _BV(1)
#define GPIO_VIBRA_EN   _BV(2)
#define GPIO_DEBUG_OUT  _BV(3)
#define GPIO_LED_OUT    _BV(4)

#define VIBRA_TIMEOUT_10s   (10)
#define VIBRA_TIMEOUT_30min (30*60)
#define VIBRA_TIMEOUT_45min (45*60)
#define VIBRA_TIMEOUT_60min (60*60)

/* - variables -------------------------------------------------------------- */
volatile uint8_t global_events;
#define fEV_TICK_TIMER     _BV(0)
#define fEV_BUTTON_WAKE    _BV(1)

/* - private functions  ----------------------------------------------------- */
/**
 * enter the given sleep mode, see avr/sleep.h
 * @param   mode    sleep modes:
 * translate: own defines to arv/sleep.h:
 * cSLEEP_MODE_... | SLEEP_MODE_...
 * cSLEEP_MODE_ACTIVE | none, do not enter this function
 * cSLEEP_MODE_IDLE | SLEEP_MODE_IDLE
 *  none | SLEEP_MODE_ADC
 * cSLEEP_MODE_POWER_DOWN | SLEEP_MODE_PWR_DOWN
 *  none | SLEEP_MODE_PWR_SAVE
 *  none | SLEEP_MODE_STANDBY
 *  none | SLEEP_MODE_EXT_STANDBY
 */
static void _EnterSleepMode(uint8_t mode) {
    set_sleep_mode(mode);
    sleep_enable();
    sei();
    sleep_cpu();    // enter sleep mode, wait here
    sleep_disable();
    cli();
}

/**
 * initialize all components
 */
static void init(void) {
    //uint8_t vbat;
    cli();

    // DISABLE BOD in FUSE bits
    PRR = 0xFF; // disable CLK for Timer0, Timer1, USI, ADC
    global_events = 0;

    // set gpios out
    DDRB = (GPIO_VIBRA_EN | GPIO_LED_OUT);

    /*vbat = vbat_Get(cVREF_VCC);
    send_SeialMSB(vbat, _BV(0));*/
    sei();
}

#define gpio_VibraOn()      PORTB |=  GPIO_VIBRA_EN
#define gpio_VibraOff()     PORTB &= ~GPIO_VIBRA_EN
#define gpio_LEDOn()        PORTB |=  GPIO_LED_OUT
#define gpio_LEDOff()       PORTB &= ~GPIO_LED_OUT

/* - public functions ------------------------------------------------------- */

/**
 * main loop
 */
#include <util/delay.h>
int main (void)
{
    uint16_t vibra_timeout_cnt = 0;
    uint8_t led_cnt = 0;
    uint8_t local_events = 0;
    init();

    // start, 1 s timeout
    wdtTimer_StartTimeout(8, cEV_TIMER_INTERVAL_0_125S, fEV_TICK_TIMER);
    /* calc timeout counts
     * -- using WDT intervals -------------------------------------
     * 60 min = 60 * 60 * 8 WDT intervals = 28800 cnts -> 16 bit
     * 30 min = 30 * 60 * 8 WDT intervals = 14400 cnts -> 16 bit
     *  1 min =  1 * 60 * 8 WDT intervals =   480 cnts -> 16 bit
     * -- using 1 s intervals -------------------------------------
     * 60 min = 60 * 60 * 1 s interval = 3600 cnts -> 16 bit
     * 30 min = 30 * 60 * 1 s interval = 1800 cnts -> 16 bit
     *  1 min =  1 * 60 * 1 s interval =   60 cnts ->  8 bit
     * -- conclusion ----------------------------------------------
     * use uint16_t vibra_timeout_cnt using 1 s intervals
     */
    vibra_timeout_cnt = 0; // vibra at start up
    led_cnt = 0;
    while(1) {

		if(local_events & fEV_TICK_TIMER) {

            gpio_VibraOff();
            if(vibra_timeout_cnt) {
                vibra_timeout_cnt--;
            }
            else {
                // timeout -> enable vibra
                //vibra_timeout_cnt = VIBRA_TIMEOUT_10s;
                vibra_timeout_cnt = VIBRA_TIMEOUT_45min;
                gpio_VibraOn();
            }
            gpio_LEDOff();
            if(led_cnt) {
                led_cnt--;
            }
            else {
                led_cnt = 10;
                gpio_LEDOn();
            }

			wdtTimer_StartTimeout(8, cEV_TIMER_INTERVAL_0_125S, fEV_TICK_TIMER);
		}

        while(1) {
            cli();
            local_events = global_events;
            global_events = 0;
            if(local_events) {
                sei();
                break;
            }
            // Power-down mode + WDT enabled = 10 uA ? datasheet ATTiny85, p 162
            // measured 2021-03-22 ca. 6 uA, 20 °C, UNI-T, UT139C
            _EnterSleepMode(SLEEP_MODE_PWR_DOWN);
        }
    }
    return(0);
}
