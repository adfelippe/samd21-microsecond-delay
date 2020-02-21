/******************************************************************************/
/**
 *  @file        timer_counter_util.c
 *  @author      Anderson Felippe <anderson.felippe@br.bosch.com>
 *  @date        21 Feb 2020
 *
 * ****************************************************************************/

#include <stdint.h>
#include "timer_counter_util.h"

// TCC module instance
static struct tc_module tc_instance;


int8_t timerCounterInit(void)
{
    struct tc_config tc_config;
    /*config TCC0 for generating the needed timebase to measure CPU load*/
    tc_get_config_defaults(&tc_config);
    tc_config.counter_size = TC_COUNTER_SIZE_32BIT;
    tc_config.clock_source = CLOCK_SOURCE;
    // GCLK4 sources clock from main clock at 8 MHz
    // DIV8 will give an 1 us counter
    tc_config.clock_prescaler = TC_CLOCK_PRESCALER_DIV8;
    int8_t res = tc_init(&tc_instance, TC4, &tc_config);
    tc_enable(&tc_instance);
    return res;
}

uint32_t tcGetCountValue(void)
{
    return tc_get_count_value(&tc_instance);
}

void tcMicrosecondDelay(uint32_t delay)
{
    // Check if TC won't reach top during delay
    // If so, reset it to avoid longer loops than expected
    if ((TC_32BIT_TOP_VALUE - tc_get_count_value(&tc_instance)) < delay)
        tc_set_count_value(&tc_instance, 0);

    uint32_t currentTime = tc_get_count_value(&tc_instance);
    while (tc_get_count_value(&tc_instance) < (currentTime + delay));
}

void tcMicrosecondDelayUntil(uint32_t *lastWakeTime, uint32_t delay)
{
    uint32_t timePassed = tc_get_count_value(&tc_instance) - (*lastWakeTime);
    // Check if there's still time to delay
    if (timePassed < delay)
        tcMicrosecondDelay(delay - timePassed);
    // Update lastWakeTime
    *lastWakeTime = tc_get_count_value(&tc_instance);
}
