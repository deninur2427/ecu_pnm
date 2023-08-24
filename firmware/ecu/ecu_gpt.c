/**
 * @file ecu_gpt.h
 * @brief General Purpose Timer code
 *
 * @addtogroup TIMER
 * @{
 */

#include "ecu_includes.h"

static void gptInjCb(GPTDriver *gptp){
    (void) gptp;
    ecu_ENG_Inj_OFF();
}

static void gptIgnCb(GPTDriver *gptp){
    (void) gptp;
    ecu_ENG_Ign_OFF();
}

static const GPTConfig gptInjCfg = {
    F_GPT,    /* 10kHz timer clock.*/
    gptInjCb, /* Timer callback.*/
    0,
    0
};

static const GPTConfig gptIgnCfg = {
    F_GPT,    /* 10kHz timer clock.*/
    gptIgnCb, /* Timer callback.*/
    0,
    0
};

void ecu_GPT_Init(void){
    gptStart(&GPTD1, &gptInjCfg);

#ifdef F103RBNUCLEO
    gptStart(&GPTD4, &gptIgnCfg);
#endif

#ifdef F051R8NUCLEO
    gptStart(&GPTD14, &gptIgnCfg);
#endif
}

/**  @} */
