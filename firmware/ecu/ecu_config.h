/**
 * @file ecu_config.h
 * @brief Global Configuration header
 *
 * @addtogroup MAIN
 * @{
 */

#ifndef _ECU_CONFIG_H_
#define _ECU_CONFIG_H_

#define assert_param(expr) ((void)0)

#define MAIN_LEDTEST FALSE

#define ECU_USE_MEM     FALSE
#define ECU_USE_GPIO    TRUE
#define ECU_USE_SHELL   TRUE
#define ECU_USE_ICU     TRUE
#define ECU_USE_ADC     TRUE
#define ECU_USE_GPT     TRUE

#endif

/**  @} */
