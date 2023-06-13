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
extern icucnt_t rpm;

uint8_t cnt_ovf;

static THD_WORKING_AREA(wa_ovfThread, 128);
static THD_FUNCTION(ovfThread, arg) {
    (void)arg;
    while (TRUE) {
        cnt_ovf++;

        if(cnt_ovf==5){
            ecu_ENG_Overflow();
            cnt_ovf=0;
        }

        chThdSleepMilliseconds(100);
    }
}

static void icuperiod_cb(ICUDriver *icup){
    last_period = icuGetPeriodX(icup);
    cnt_ovf = 0;
    ecu_ENG_ToothCalc();
    ecu_ENG_InjIgnCalc();
    ecu_ENG_InjIgnControl();
}

static ICUConfig icucfg = {
    ICU_INPUT_ACTIVE_HIGH,
    F_ICU,
    NULL,
    icuperiod_cb,
    NULL,
    ICU_CHANNEL_2,
    0
};

void ecu_ICU_Init(void){
    palSetPadMode(GPIOA,CKP_PIN,PAL_MODE_INPUT_PULLDOWN);
    icuStart(&ICUD3, &icucfg);
    icuStartCapture(&ICUD3);
    icuEnableNotifications(&ICUD3);
    chThdCreateStatic(wa_ovfThread, sizeof(wa_ovfThread), NORMALPRIO, ovfThread, NULL);
}
/**  @} */
