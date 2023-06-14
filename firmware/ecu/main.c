/**
 * @file main.c
 * @brief Main Entry Program
 *
 * @addtogroup MAIN
 * @{
 */

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

#include "ecu_includes.h"

/*
 * Application entry point.
 */
int main(void) {
  halInit();
  chSysInit();

  ecu_MEM_Init();
  ecu_GPIO_Init();
  ecu_SHELL_Init();
  ecu_ICU_Init();
  ecu_ADC_Init();
  ecu_GPT_Init();

  while (true) {
      ecu_SHELL_Loop();
      chThdSleepMilliseconds(500);
  }
}

/**  @} */

