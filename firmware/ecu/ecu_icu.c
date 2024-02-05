/**
 * @file ecu_icu.c
 * @brief Input Capture Unit code
 *
 * @addtogroup ICU
 * @{
 */

#include "ecu_includes.h"

extern icucnt_t last_period;
extern adcsample_t adc_tps;
extern uint8_t toothcount;
extern icucnt_t rpm;

uint8_t cnt_ovf;

#if ECU_SIMULATE
static THD_WORKING_AREA(wa_simThread, 128);
static THD_FUNCTION(simThread, arg){
    (void) arg;


    while (TRUE) {
        last_period = 100;
        cnt_ovf = 0;

        ecu_ENG_ToothCalc();
        ecu_ENG_InjIgnCalc();
        ecu_ENG_InjIgnControl();

        palSetPad(GPIOA,CKP_LED);

        ECU_SIM_DELAY;
    }
}
#endif

static THD_WORKING_AREA(wa_ovfThread, 128);
static THD_FUNCTION(ovfThread, arg) {
    (void)arg;
    while (TRUE) {
        cnt_ovf++;

        if(cnt_ovf==5){
            ecu_ENG_Overflow();
            cnt_ovf=0;
        }

        chThdSleepMilliseconds(ECU_OVF_DELAY);
    }
}

static void icuperiod_cb(ICUDriver *icup){
    last_period = icuGetPeriodX(icup);
    cnt_ovf = 0;

    ecu_ENG_ToothCalc();
    ecu_ENG_InjIgnCalc();
    ecu_ENG_InjIgnControl();

    palSetPad(GPIOA,CKP_LED);
}

static ICUConfig icucfg = {
    ICU_INPUT_ACTIVE_HIGH,
    F_ICU,
    NULL,
#if ECU_SIMULATE
    NULL,
#else
    icuperiod_cb,
#endif
    NULL,
    ICU_CHANNEL_2,
    0
};

void ecu_ICU_Init(void){

#ifdef F103RBNUCLEO
    palSetPadMode(GPIOA,CKP_PIN,PAL_MODE_INPUT_PULLDOWN);
#endif

#ifdef F051R8NUCLEO
    palSetPadMode(GPIOA,CKP_PIN, PAL_MODE_ALTERNATE(1));
#endif

    icuStart(&ICUD3, &icucfg);
    icuStartCapture(&ICUD3);
    icuEnableNotifications(&ICUD3);
    chThdCreateStatic(wa_ovfThread, sizeof(wa_ovfThread), NORMALPRIO, ovfThread, NULL);

#if ECU_SIMULATE
    chThdCreateStatic(wa_simThread, sizeof(wa_simThread), NORMALPRIO, simThread, NULL);
#endif

}
/**  @} */
