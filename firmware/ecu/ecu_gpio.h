/**
 * @file ecu_gpio.h
 * @brief GPIO header
 *
 * @addtogroup GPIO
 * @{
 */

#ifndef _ECU_GPIO_H_
#define _ECU_GPIO_H_

#define CKP_LED 5

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

/**
 * @brief ECU GPIO Initialization
 */
void ecu_GPIO_Init(void);

#endif

/**  @} */


