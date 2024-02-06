/**
 * @file ecu_engine.c
 * @brief Engine Routine code
 *
 * @addtogroup ENGINE
 * @{
 */

#include "ecu_includes.h"

adcsample_t adc_tps;

icucnt_t last_period, prev_last_period;
icucnt_t rpm, frequency, misstooth;

uint8_t toothcount;
uint8_t id_rpm, id_tps;

#if ENGINE_DATA_MEMORY
uint16_t inj_data_ms_perc[ENGINE_CDATA][ENGINE_CDATA];
uint16_t ign_data_off_deg[ENGINE_CDATA][ENGINE_CDATA];
uint16_t inj_ms_base, inj_open_time;
adcsample_t adc_tps_close,adc_tps_full;
#else
uint16_t inj_data_ms_perc[ENGINE_CDATA][ENGINE_CDATA]={
  // 500,	750, 1000, 1250, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000
  {	44,	26,	13,	 4,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0}, // 0
  {	26,	29,	33,	35,	37,	40,	42,	44,	51,	55,	57,	59}, // 10
  {	28,	30,	34,	37,	39,	41,	43,	45,	52,	56,	59,	61}, // 15
  {	29,	32,	36,	38,	40,	43,	45,	47,	54,	58,	60,	62}, // 20
  {	36,	38,	43,	45,	48,	50,	52,	54,	61,	65,	68,	70}, // 30
  {	38,	40,	44,	46,	48,	51,	54,	56,	63,	67,	70,	74}, // 40
  {	40,	42,	47,	48,	50,	52,	57,	57,	62,	70,	72,	74}, // 50
  {	42,	45,	50,	52,	55,	57,	62,	62,	69,	75,	77,	80}, // 60
  {	44,	47,	51,	53,	56,	59,	62,	62,	74,	79,	82,	84}, // 70
  {	45,	48,	52,	55,	57,	59,	64,	64,	74,	81,	82,	84}, // 80
  {	47,	49,	54,	97,	97,	97,	97,	97,	88,	88,	88,	88}, // 90
  {	48,	50,	57,	97,	97,	97,	97,	97,	88,	88,	88,	88}  // 100
};

uint16_t ign_data_off_deg[ENGINE_CDATA][ENGINE_CDATA]={
  // 500,	750, 1000, 1250, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 0
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 10
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 15
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 20
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 30
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 40
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 50
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 60
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 70
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 80
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}, // 90
  {	10,	15,	15,	18,	20,	22,	25,	25,	27,	27,	30,	30}  // 100
};

adcsample_t adc_tps_close=195,adc_tps_full=1395;
uint16_t inj_ms_base=5,inj_open_time=200;
#endif

uint16_t data_tps[ENGINE_CDATA]={0,10,15,20,30,40,50,60,70,80,90,100};
uint16_t data_rpm[ENGINE_CDATA]={500,750,1000,1250,1500,2000,2500,3000,4000,5000,6000,7000};

uint16_t inj_ms_perc,inj_ms_tick;
uint16_t ign_off_deg,ign_off_deg_out,ign_off_tick;
uint16_t one_deg_tick;

uint8_t rpm_index,tps_index;

void ecu_ENG_ToothCalc(void){
    // get period comparisson in percent
    if(last_period > 0){
        misstooth = (prev_last_period*100) / last_period;
        prev_last_period = last_period;
    }

    // if period percent approximately 50% (half than previous)
    // reset the toothcount
    // or else increment the toothcount
    if((misstooth>40) && (misstooth<60)){
        toothcount = 0;
    }
    else{
        frequency = F_ICU / last_period;
        rpm = frequency*60 / (ENGINE_ALL_TOOTH + 1);

        one_deg_tick = last_period / ENGINE_DEGREE_TOOTH;

        toothcount++;
    }

    // some guarding in case reset tooth failed
    if(toothcount==ENGINE_ALL_TOOTH+1) toothcount=0;
    if(toothcount==ENGINE_ALL_TOOTH+2) toothcount=1;
}

void ecu_ENG_InjIgnCalc(void){
    uint8_t i;

    ///////////////////////////////////////////////////
    // selecting rpm index in rpm array

    for(i=0;i<ENGINE_CDATA-2;i++){
        if((rpm>=data_rpm[i]) && (rpm<data_rpm[i+1])){
            rpm_index = i;
        }
    }

    if(rpm<data_rpm[0]) rpm_index = 0;
    if(rpm>=data_rpm[ENGINE_CDATA-1]) rpm_index = ENGINE_CDATA-1;

    //////////////////////////////////////////////////
    // selecting tps index in tps array

    for(i=0;i<ENGINE_CDATA-2;i++){
        if((adc_tps>=data_tps[i]) && (adc_tps<data_tps[i+1])){
            tps_index = i;
        }
    }

    if(adc_tps<data_tps[0]) tps_index = 0;
    if(adc_tps>=data_tps[ENGINE_CDATA-1]) tps_index = ENGINE_CDATA-1;

    //////////////////////////////////////////////////
    // Allocate actual matrix value

    id_tps = tps_index;
    id_rpm = rpm_index;

    inj_ms_perc = inj_data_ms_perc[tps_index][rpm_index];
    ign_off_deg = ign_data_off_deg[tps_index][rpm_index];

    // Injection Timing
    inj_ms_tick = (inj_ms_perc * inj_ms_base) + inj_open_time;

    // Ignition Timing
    // 31 came from two teeth range span (30 degree)
    ign_off_deg_out = 31 - ign_off_deg;
    ign_off_tick = ign_off_deg_out * one_deg_tick;
}

void ecu_ENG_InjIgnControl(void){

    ////////////////////////////////////////////////
    // Injection Control

    if(toothcount==ENGINE_TOOTH_INTAKE_OPEN){
        ecu_ENG_Inj_ON();

#if ENGINE_INJ_USETIMER
        chSysLockFromISR();
        gptStartOneShotI(&GPTD1,inj_ms_tick);
        chSysUnlockFromISR();
#endif
    }

    if(toothcount==ENGINE_TOOTH_INTAKE_CLOSE){
        ecu_ENG_Inj_OFF();
    }

    ////////////////////////////////////////////////
    // Ignition Control

    if(toothcount==ENGINE_TOOTH_COIL_ON){
        ecu_ENG_Ign_ON();
    }

    if(toothcount==ENGINE_TOOTH_COIL_OFF){
#if ENGINE_IGN_USETIMER
        chSysLockFromISR();

  #ifdef F103RBNUCLEO
        gptStartOneShotI(&GPTD4, ign_off_tick);
  #endif

  #ifdef F051R8NUCLEO
        gptStartOneShotI(&GPTD14, ign_off_tick);
  #endif

        chSysUnlockFromISR();
#else
        ecu_ENG_Ign_OFF();
#endif
    }
}

void ecu_ENG_Overflow(void){
    NO_CKP();

#if ECU_SIMULATE
    // control using virtual cranktooth
#else
    frequency = 0;
    rpm = 0;
    misstooth = 0;

    ecu_ENG_Inj_OFF();
    ecu_ENG_Ign_OFF();
#endif
}

void ecu_ENG_DataSend(void){
    chprintf(
        (BaseSequentialStream *)&SD1,
        "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,0\r\n",
        rpm,
        adc_tps,
        inj_ms_perc,
        inj_ms_tick,
        ign_off_deg,
        ign_off_tick,
        one_deg_tick,
        id_rpm,
        id_tps,
        inj_open_time,
        inj_ms_base
    );
}

/**  @} */


