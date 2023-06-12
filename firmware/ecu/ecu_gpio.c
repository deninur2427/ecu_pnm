/**
 * @file ecu_gpio.c
 * @brief GPIO code
 *
 * @addtogroup GPIO
 * @{
 */

#include "ch.h"
#include "hal.h"

#include "ecu_gpio.h"

static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    chThdSleepMilliseconds(100);
    NO_CKP();
  }
}

void ecu_GPIO_Init(void){
    palSetPadMode(GPIOA, CKP_LED, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(OUT_PORT, OUT_INJ, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(OUT_PORT, OUT_IGN, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPad(GPIOA, CKP_LED);
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
}

/**  @} */


