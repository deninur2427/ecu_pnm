/**
 * @file ecu_gpio.c
 * @brief GPIO code
 *
 * @addtogroup GPIO
 * @{
 */

#include "ecu_config.h"
#include "ecu_includes.h"

#if ECU_COIL_TEST
static uint16_t coil_counter;

static THD_WORKING_AREA(wa_coilTestThread, 128);
static THD_FUNCTION(coilTestThread, arg) {
  (void)arg;

  while (TRUE) {
      coil_counter++;

      ecu_ENG_Ign_ON();
      ECU_COIL_DELAY; // coil EMF may freeze the chip
      ecu_ENG_Ign_OFF();

      chThdSleepMilliseconds(250);
      chprintf((BaseSequentialStream*)&SD1,"Coil sparked for %i times\r\n",coil_counter);
  }
}
#endif

void ecu_GPIO_Init(void){

#ifdef F051R8NUCLEO
    palSetPadMode(GPIOA, 13, PAL_MODE_ALTERNATE(0));
    palSetPadMode(GPIOA, 14, PAL_MODE_ALTERNATE(0));
#endif

    palSetPadMode(GPIOA, CKP_LED, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(OUT_PORT, OUT_INJ, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(OUT_PORT, OUT_IGN, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPad(GPIOA, CKP_LED);

#if ECU_COIL_TEST
    chThdCreateStatic(wa_coilTestThread, sizeof(wa_coilTestThread), NORMALPRIO, coilTestThread, NULL);
#endif
}

/**  @} */


