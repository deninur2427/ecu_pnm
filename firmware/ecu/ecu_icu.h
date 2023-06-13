/**
 * @file ecu_icu.h
 * @brief Input Capture Unit header
 *
 * @addtogroup ICU
 * @{
 */

#ifndef _ECU_ICU_H_
#define _ECU_ICU_H_

#define F_ICU   100000

/**
 * @brief Input Capture Pin
 * @details Timer 3 Channel 2 on GPIOA pin 7
 */
#define CKP_PIN 7

/**
 * @brief Input Capture Initialization
 */
void ecu_ICU_Init(void);

#endif

/**  @} */


