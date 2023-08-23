/**
 * @file ecu_gpio.c
 * @brief GPIO code
 *
 * @addtogroup GPIO
 * @{
 */

#include "ecu_config.h"
#include "ecu_includes.h"

#if LEDSHELL_TEST
static THD_WORKING_AREA(wa_ledTestThread, 128);
static THD_FUNCTION(ledTestThread, arg) {
    (void)arg;
    palSetPad(GPIOA, CKP_LED);
    while (TRUE) {
	palTogglePad(GPIOA, CKP_LED);
        chThdSleepMilliseconds(250);
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

#if LEDSHELL_TEST
	chThdCreateStatic(wa_ledTestThread, sizeof(wa_ledTestThread), NORMALPRIO, ledTestThread, NULL);
#endif
}

/**  @} */


