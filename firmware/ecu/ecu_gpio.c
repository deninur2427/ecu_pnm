/**
 * @file ecu_gpio.c
 * @brief GPIO code
 *
 * @addtogroup GPIO
 * @{
 */

#include "ecu_config.h"
#include "ecu_includes.h"

void ecu_GPIO_Init(void){

#ifdef F051R8NUCLEO
    palSetPadMode(GPIOA, 13, PAL_MODE_ALTERNATE(0));
    palSetPadMode(GPIOA, 14, PAL_MODE_ALTERNATE(0));
#endif

    palSetPadMode(GPIOA, CKP_LED, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(OUT_PORT, OUT_INJ, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(OUT_PORT, OUT_IGN, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPad(GPIOA, CKP_LED);
}

/**  @} */


