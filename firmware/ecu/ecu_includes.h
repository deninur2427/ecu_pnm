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

#include "shell.h"
#include "chprintf.h"

#include "ecu_config.h"

#include "ecu_adc.h"
#include "ecu_gpio.h"
#include "ecu_mem.h"
#include "ecu_icu.h"
#include "ecu_gpt.h"
#include "ecu_shell.h"
#include "ecu_engine.h"

#ifdef F103RBNUCLEO
 #include "stm32f10x_flash.h"
 #include "stm32f10x_eeprom.h"
#endif

#ifdef F051R8NUCLEO
 #include "stm32f0xx_flash.h"
 #include "stm32f0xx_eeprom.h"
#endif

#endif

/**  @} */


