/**
 * @file ecu_adc.h
 * @brief ADC header
 *
 * @addtogroup ADC
 * @{
 */

#ifndef _ECU_ADC_H_
#define _ECU_ADC_H_

/**
 * @brief ADC Channels
 * @details Throttle Position Sensor (TPS)
 */
#define ADC_GRP1_NUM_CHANNELS   1

/**
 * @brief Averaging Buffer Depth
 */
#define ADC_GRP1_BUF_DEPTH      10

/**
 * @brief ADC initialization
 */
void ecu_ADC_Init(void);

#endif

/**  @} */


