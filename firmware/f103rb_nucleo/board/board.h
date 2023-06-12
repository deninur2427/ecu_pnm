/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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
 * Setup for the ST INEMO-M1 Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_PNM_ECU
#define BOARD_NAME              "PNM_ECU"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            0

#if defined(NUCLEO_EXTERNAL_OSCILLATOR)
#define STM32_HSECLK            8000000
#define STM32_HSE_BYPASS

#elif defined(NUCLEO_HSE_CRYSTAL)
#define STM32_HSECLK            8000000

#else
#define STM32_HSECLK            0
#endif

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_MD

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

#define VAL_GPIOECRL            0
#define VAL_GPIOECRH            0
#define VAL_GPIOEODR            0

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp)

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
