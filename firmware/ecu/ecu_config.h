/**
 * @file ecu_config.h
 * @brief Global Configuration header
 *
 * @addtogroup MAIN
 * @{
 */

#ifndef _ECU_CONFIG_H_
#define _ECU_CONFIG_H_

#include "ch.h"
#include "hal.h"

#define assert_param(expr) ((void)0)

#define ECU_SIMULATE    TRUE

#define ECU_USE_GPIO    TRUE
#define ECU_USE_SHELL   TRUE
#define ECU_USE_ICU     TRUE
#define ECU_USE_MEM     TRUE
#define ECU_USE_ADC     TRUE
#define ECU_USE_GPT     FALSE

#define ECU_OVF_DELAY   100

#define ECU_SIM_DELAY   chThdSleepMilliseconds(5)  // fastest RPM it might can be
#define ECU_COIL_DELAY  chThdSleepMicroseconds(500) // coil charging max delay without EMF

#endif

/**  @} */
