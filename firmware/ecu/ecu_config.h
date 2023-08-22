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

#define LEDSHELL_TEST     FALSE

#if LEDSHELL_TEST
  #define ECU_USE_GPIO    TRUE
  #define ECU_USE_SHELL   TRUE
#else
  #define ECU_USE_MEM     FALSE
  #define ECU_USE_GPIO    TRUE
  #define ECU_USE_SHELL   TRUE
  #define ECU_USE_ICU     TRUE
  #define ECU_USE_ADC     TRUE
  #define ECU_USE_GPT     TRUE
#endif

#endif

/**  @} */
