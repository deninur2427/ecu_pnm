/**
 * @file ecu_mem.c
 * @brief Non Volatile Memory code
 *
 * @addtogroup MEMORY
 * @{
 */

#include "ecu_includes.h"

volatile uint16_t VirtAddVarTab[NUMBER_OF_VAR];

extern adcsample_t adc_tps_close,adc_tps_full;

void ecu_MEM_Init(void){
    FLASH_Unlock();
    EE_Init();
}

uint16_t ecu_MEM_Read(uint16_t addr){
    uint16_t data;
    EE_ReadVariable(addr, &data);
    return data;
}

void ecu_MEM_Save(uint16_t addr, uint16_t data){
    EE_WriteVariable(addr, data);
}

/**  @} */


