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

#if MAIN_LEDTEST
static THD_WORKING_AREA(wa_ledTestThread, 128);
static THD_FUNCTION(ledTestThread, arg) {
    (void)arg;
    palSetPad(GPIOA, CKP_LED);
    while (TRUE) {
	palTogglePad(GPIOA, CKP_LED);
        chThdSleepMilliseconds(250);
    }
}
#endif

/*
 * Application entry point.
 */
int main(void) {

#if MAIN_LEDTEST
	halInit();
	chSysInit();
	palSetPadMode(GPIOA, CKP_LED, PAL_MODE_OUTPUT_PUSHPULL);
	chThdCreateStatic(wa_ledTestThread, sizeof(wa_ledTestThread), NORMALPRIO, ledTestThread, NULL);
	while (true) {
		chThdSleepMilliseconds(500);
	}
#else

	// Hardware Abstraction Layer initialization
	halInit();

	// RTOS scheduler initialization
	chSysInit();

	// EEPROM initialization
 #ifdef F103RBNUCLEO
	ecu_MEM_Init();
 #endif

	// I/O Pins initialization
	ecu_GPIO_Init();

	// Serial Shell initialization
	ecu_SHELL_Init();

	// Input Capture initialization
	ecu_ICU_Init();

	// Analog-Digital initialization
	ecu_ADC_Init();

	// Generic Timer initialization
	ecu_GPT_Init();

	while (true) {
		// Serial Shell Loop initialization
		ecu_SHELL_Loop();

		// Latency to keep scheduling from race
		chThdSleepMilliseconds(500);
	}
#endif
}

/**  @} */

