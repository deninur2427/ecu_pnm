/**
 * @file ecu_mem.h
 * @brief Non-Volatile Memory header
 *
 * @addtogroup MEMORY
 * @{
 */

#ifndef _ECU_MEMORY_H_
#define _ECU_MEMORY_H_

#include <stdint.h>

// Memory sequence declarations
#define MEM_ADC_TPS_FULL    0
#define MEM_ADC_TPS_CLOSE   1
#define MEM_INJ_MS_BASE     2
#define MEM_INJ_OPEN_TIME   3
#define MEM_INJ_DATA        4
#define MEM_IGN_DATA        149

// Number of variables in memories
#define NUMBER_OF_VAR       ((uint16_t)0x300)

// Memory mode declarations
#define MEM_SAVE    0
#define MEM_READ    1

/**
 * @brief Non Volatile Memory Initialization
 */
void ecu_MEM_Init(void);

/**
 * @brief Non Volatile Memory Reading
 *
 * @param addr Address of data storage
 *
 * @return Data Value
 */
uint16_t ecu_MEM_Read(uint16_t addr);

/**
 * @brief Non Volatile Memory Saving
 *
 * @param addr Adress of data storage
 * @param data value for data storage
 */
void ecu_MEM_Save(uint16_t addr, uint16_t data);

#endif

/**  @} */

