/**
 * @file ecu_gpt.h
 * @brief General Purpose Timer code
 *
 * @addtogroup TIMER
 * @{
 */

#include "ecu_includes.h"

static void gpt1cb(GPTDriver *gptp){
    (void) gptp;
    ecu_ENG_Inj_OFF();
}

static void gpt4cb(GPTDriver *gptp){
    (void) gptp;
    ecu_ENG_Ign_OFF();
}

static const GPTConfig gpt1cfg = {
    F_GPT,    /* 10kHz timer clock.*/
    gpt1cb,   /* Timer callback.*/
    0,
    0
};

static const GPTConfig gpt4cfg = {
    F_GPT,    /* 10kHz timer clock.*/
    gpt4cb,   /* Timer callback.*/
    0,
    0
};

void ecu_GPT_Init(void){
    gptStart(&GPTD1, &gpt1cfg);
    gptStart(&GPTD4, &gpt4cfg);
}

/**  @} */
