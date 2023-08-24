/**
 * @file ecu_adc.c
 * @brief ADC code
 *
 * @addtogroup ADC
 * @{
 */

#include "ecu_includes.h"

extern adcsample_t adc_tps;
extern adcsample_t adc_tps_close, adc_tps_full;

adcsample_t adc_tps_val;

static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
static uint32_t sum_adc_tps;

void adc_cb(ADCDriver *adcp, adcsample_t *buffer, size_t n){
    (void)adcp;
    (void) buffer;
    (void) n;
    uint8_t i;

    if(adcp->state == ADC_COMPLETE){
        sum_adc_tps = 0;

        for(i=0;i<ADC_GRP1_BUF_DEPTH;i++){
            sum_adc_tps = sum_adc_tps + samples[0 + (i*ADC_GRP1_NUM_CHANNELS)];
        }

        adc_tps_val = sum_adc_tps/10;

        if(adc_tps_full!=0){
            if(adc_tps_val>=adc_tps_close){
                // ADC TPC calculated as percent from full-close range value
                adc_tps = 100 * (adc_tps_val - adc_tps_close) / (adc_tps_full - adc_tps_close);
            }
        }
    }
}

static const ADCConversionGroup adcgrpcfg = {
#ifdef F103RBNUCLEO
    FALSE,
    ADC_GRP1_NUM_CHANNELS,
    adc_cb,
    NULL,
    /* HW Dependent Part */
    0,
    0,
    ADC_SMPR2_SMP_AN0(ADC_SAMPLE_239P5),
    0,
    ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
    0,
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0)
#endif

#ifdef F051R8NUCLEO
    FALSE,
    ADC_GRP1_NUM_CHANNELS,
    adc_cb,
    NULL,
    /* HW Dependent Part */
    ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,             /* CFGR1 */
    ADC_TR(0, 0),                                     /* TR */
    ADC_SMPR_SMP_1P5,                                 /* SMPR */
    ADC_CHSELR_CHSEL1                                 /* CHSELR */
#endif
};

static THD_WORKING_AREA(wa_adcThread, 128);
static THD_FUNCTION(adcThread, arg) {
  (void)arg;
  while (TRUE) {
    chThdSleepMilliseconds(500);
    adcStartConversion(&ADCD1, &adcgrpcfg, samples, ADC_GRP1_BUF_DEPTH);
  }
}

void ecu_ADC_Init(void){
#ifdef F103RBNUCLEO
    palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_ANALOG);
#endif

#ifdef F051R8NUCLEO
    palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_ANALOG);
#endif

    adcStart(&ADCD1, NULL);
    chThdCreateStatic(wa_adcThread, sizeof(wa_adcThread), NORMALPRIO, adcThread, NULL);
}

/**  @} */


