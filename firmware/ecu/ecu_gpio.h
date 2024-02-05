/**
 * @file ecu_gpio.h
 * @brief GPIO header
 *
 * @addtogroup GPIO
 * @{
 */

#ifndef _ECU_GPIO_H_
#define _ECU_GPIO_H_

#include "hal.h"

/**
 * @brief PickUp signal LED
 */
#define CKP_LED     5

/**
 * @brief Output IO Port
 */
#define OUT_PORT    GPIOC

/**
 * @brief Ignition Output Pin
 */
#define OUT_IGN     8

/**
 * @brief Injection Output Pin
 */
#define OUT_INJ     6

/**
 * @brief No PickUp signal received indicator
 */
#define NO_CKP()    palTogglePad(GPIOA, CKP_LED)

// Injector Output declaration functions
#define ecu_ENG_Inj_ON()    palSetPad(OUT_PORT,OUT_INJ)
#define ecu_ENG_Inj_OFF()   palClearPad(OUT_PORT,OUT_INJ)

// Ignition Output declaration functions
#define ecu_ENG_Ign_ON()    palSetPad(OUT_PORT,OUT_IGN)
#define ecu_ENG_Ign_OFF()   palClearPad(OUT_PORT,OUT_IGN)

/**
 * @brief ECU GPIO Initialization
 */
void ecu_GPIO_Init(void);

#endif

/**  @} */


