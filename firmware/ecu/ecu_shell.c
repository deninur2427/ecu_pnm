/**
 * @file ecu_shell.c
 * @brief Shell Interface code
 *
 * @addtogroup INTERFACE
 * @{
 */

#include "ecu_includes.h"

extern adcsample_t adc_tps_val;

thread_t *shelltp = NULL;

static void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]){
    (void) argv;

    if(argc==0) chprintf(chp, "Serial Interface Working \r\n");
    return;
}

static void cmd_tps_val(BaseSequentialStream *chp, int argc, char *argv[]){
    (void) argv;

    if(argc==0) chprintf(chp,"%i\n",adc_tps_val);
    return;
}

static const ShellCommand commands[] = {
    {"test",cmd_test},
    {"tps",cmd_tps_val},
    {NULL,NULL}
};

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD1,
    commands
};

void ecu_SHELL_Init(void){
    palSetPadMode(GPIOA, 9, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetPadMode(GPIOA, 10, PAL_MODE_INPUT);

    sdStart(&SD1, NULL);
    shellInit();

    chprintf((BaseSequentialStream*)&SD1,"Serial Shell Running\r\n");
}

void ecu_SHELL_Loop(void){
    if(!shelltp){
        shelltp = shellCreate(&shell_cfg, SHELL_WA_SIZE, NORMALPRIO);
    }
    else if(chThdTerminatedX(shelltp)){
        chThdRelease(shelltp);
        shelltp = NULL;
    }
}

/**  @} */


