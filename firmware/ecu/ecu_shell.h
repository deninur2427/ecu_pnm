/**
 * @file ecu_shell.h
 * @brief Serial Shell header
 *
 * @addtogroup INTERFACE
 * @{
 */

#ifndef _ECU_SHELL_H_
#define _ECU_SHELL_H_

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
#define TEST_WA_SIZE    THD_WORKING_AREA_SIZE(256)

/**
 * @brief Shell Interface initialization
 */
void ecu_SHELL_Init(void);


/**
 * @brief Shell Interface Loop
 */
void ecu_SHELL_Loop(void);

#endif

/**  @} */


