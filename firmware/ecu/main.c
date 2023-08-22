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

#include "ecu_config.h"
#include "ecu_includes.h"

/*
 * Application entry point.
 */
int main(void) {

	// Hardware Abstraction Layer initialization
	halInit();

	// RTOS scheduler initialization
	chSysInit();

	// EEPROM initialization
#if ECU_USE_MEM
	ecu_MEM_Init();
#endif

	// I/O Pins initialization
#if ECU_USE_GPIO
	ecu_GPIO_Init();
#endif

	// Serial Shell initialization
#if ECU_USE_SHELL
	ecu_SHELL_Init();
#endif

	// Input Capture initialization
#if ECU_USE_ICU
	ecu_ICU_Init();
#endif

	// Analog-Digital initialization
#if ECU_USE_ADC
	ecu_ADC_Init();
#endif

	// Generic Timer initialization
#if ECU_USE_GPT
	ecu_GPT_Init();
#endif

	while (true) {
		// Serial Shell Loop initialization
	#if ECU_USE_SHELL
		ecu_SHELL_Loop();
	#endif

		// Latency to keep scheduling from race
		chThdSleepMilliseconds(500);
	}
}

/**  @} */

