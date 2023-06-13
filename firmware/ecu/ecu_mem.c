/**
 * @file ecu_mem.c
 * @brief Non Volatile Memory code
 *
 * @addtogroup MEMORY
 * @{
 */

#include "ecu_includes.h"

volatile uint16_t VirtAddVarTab[NUMBER_OF_VAR];

extern uint16_t inj_data_ms_perc[ENGINE_CDATA][ENGINE_CDATA];
extern uint16_t ign_data_off_deg[ENGINE_CDATA][ENGINE_CDATA];
extern uint16_t inj_ms_base, inj_open_time;
extern adcsample_t adc_tps_close,adc_tps_full;

void ecu_MEM_Init(void){
    FLASH_Unlock();
    EE_Init();
    ecu_MEM_LoadAll();
}

uint16_t ecu_MEM_Read(uint16_t addr){
    uint16_t data;
    EE_ReadVariable(addr, &data);
    return data;
}

void ecu_MEM_Save(uint16_t addr, uint16_t data){
    EE_WriteVariable(addr, data);
}

void ecu_MEM_Adc(uint8_t rw){
    if(rw==MEM_SAVE){
        ecu_MEM_Save(MEM_ADC_TPS_CLOSE,adc_tps_close);
        ecu_MEM_Save(MEM_ADC_TPS_FULL,adc_tps_full);
    }
    else if(rw==MEM_READ){
        adc_tps_close=ecu_MEM_Read(MEM_ADC_TPS_CLOSE);
        adc_tps_full=ecu_MEM_Read(MEM_ADC_TPS_FULL);
    }
}

void ecu_MEM_InjTiming(uint8_t rw){
    if(rw==MEM_SAVE){
        ecu_MEM_Save(MEM_INJ_MS_BASE,inj_ms_base);
        ecu_MEM_Save(MEM_INJ_OPEN_TIME,inj_open_time);
    }
    else if(rw==MEM_READ){
        inj_ms_base=ecu_MEM_Read(MEM_INJ_MS_BASE);
        inj_open_time=ecu_MEM_Read(MEM_INJ_OPEN_TIME);
    }
}

void ecu_MEM_InjData(uint8_t idx_tps, uint8_t idx_rpm, uint8_t rw){
    int i,j;

    i = idx_tps;
    j = idx_rpm;

    if(rw==MEM_SAVE){
        ecu_MEM_Save(MEM_INJ_DATA+(i*ENGINE_CDATA)+j,inj_data_ms_perc[i][j]);
    }
    else if(rw==MEM_READ){
        inj_data_ms_perc[i][j]=ecu_MEM_Read(MEM_INJ_DATA+(i*ENGINE_CDATA)+j);
    }
}

void ecu_MEM_IgnData(uint8_t idx_tps, uint8_t idx_rpm, uint8_t rw){
    int i,j;

    i = idx_tps;
    j = idx_rpm;

    if(rw==MEM_SAVE){
        ecu_MEM_Save(MEM_IGN_DATA+(i*ENGINE_CDATA)+j,ign_data_off_deg[i][j]);
    }
    else if(rw==MEM_READ){
        ign_data_off_deg[i][j]=ecu_MEM_Read(MEM_IGN_DATA+(i*ENGINE_CDATA)+j);
    }
}

void ecu_MEM_LoadAll(void){
    uint8_t i,j;

    ecu_MEM_Adc(MEM_READ);
    ecu_MEM_InjTiming(MEM_READ);

    for(i=0;i<ENGINE_CDATA;i++){
        for(j=0;j<ENGINE_CDATA;j++){
            ecu_MEM_InjData(i,j,MEM_READ);
            ecu_MEM_IgnData(i,j,MEM_READ);
        }
    }
}


/**  @} */


