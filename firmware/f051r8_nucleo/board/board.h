/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for ST STM32F0-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_PNM_ECU
#define BOARD_NAME              "PNM_ECU"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 * NOTE: HSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                0U
#endif

#define STM32_HSE_BYPASS

/*
 * MCU type as defined in the ST header.
 */
#define STM32F051x8

#define GPIOA_LED_GREEN         5U

#define VAL_GPIOACRL            0
#define VAL_GPIOACRH            0
#define VAL_GPIOAODR            0

#define VAL_GPIOBCRL            0
#define VAL_GPIOBCRH            0
#define VAL_GPIOBODR            0

#define VAL_GPIOCCRL            0
#define VAL_GPIOCCRH            0
#define VAL_GPIOCODR            0

#define VAL_GPIODCRL            0
#define VAL_GPIODCRH            0
#define VAL_GPIODODR            0

#define VAL_GPIOFCRL            0
#define VAL_GPIOFCRH            0
#define VAL_GPIOFODR            0

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
