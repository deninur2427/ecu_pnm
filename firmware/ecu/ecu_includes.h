/**
 * @file ecu_includes.h
 * @brief Global Inclusion header
 *
 * @addtogroup MAIN
 * @{
 */

#ifndef _ECU_INCLUDES_H_
#define _ECU_INCLUDES_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include "ch.h"
#include "hal.h"

#include "ecu_adc.h"
#include "ecu_gpio.h"
#include "ecu_mem.h"

#include "stm32f10x_flash.h"
#include "stm32f10x_eeprom.h"

#define assert_param(expr) ((void)0)

#endif

/**  @} */


