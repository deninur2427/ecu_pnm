/**
 * @file ecu_gpio.c
 * @brief GPIO code
 *
 * @addtogroup GPIO
 * @{
 */

#include "ecu_config.h"
#include "ecu_includes.h"

#if MAIN_LEDTEST
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
    palSetPadMode(GPIOA, CKP_LED, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(OUT_PORT, OUT_INJ, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(OUT_PORT, OUT_IGN, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPad(GPIOA, CKP_LED);

#if MAIN_LEDTEST
	chThdCreateStatic(wa_ledTestThread, sizeof(wa_ledTestThread), NORMALPRIO, ledTestThread, NULL);
#endif
}

/**  @} */


