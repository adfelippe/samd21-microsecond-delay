/******************************************************************************/
/**
 *  @file        timer_counter_util.h
 *  @author      Anderson Felippe <anderson.felippe@br.bosch.com>
 *  @date        21 Feb 2020
 *
 * ****************************************************************************/

#ifndef _TIMER_COUNTER_UNTIL_H_
#define _TIMER_COUNTER_UNTIL_H_

#include "samd21g18a.h"
#include "tc.h"

#define     TC_32BIT_TOP_VALUE          4294967295UL
#define     CLOCK_SOURCE                GCLK_GENERATOR_4

/****************************************************************************/
/**
 * @brief   Configures and inits TC registers.
 *
 * @detail  This API configures TC3/TC4 to act as 32-bit counter, expecting the
 *          internal 8 MHz clock source from the clock generator since prescaler
 *          is set to DIV8, resulting in 1 us period to the TC clock.
 *          If you have different clock settings, you'll have to adjust
 *          conf_clocks.h properly and maybe change prescaler settings in this
 *          function. The clock source is set to general clock generator 4, but
 *          you can change it to any clock you have configured in your conf_clocks
 *          file.
 *
 * @param   None.
 *
 * @retval  int8_t  Result from the ASF TC init API function.
 *
 ****************************************************************************/
int8_t timerCounterInit(void);

/****************************************************************************/
/**
 * @brief   Get current TC value
 *
 * @detail  This API is a just a wrapper to get current counter value from the
 *          inintialized TC instance.
 *
 * @param   None.
 *
 * @retval  uint32_t:   Current TC value.
 *
 ****************************************************************************/
uint32_t tcGetCountValue(void);

/****************************************************************************/
/**
 * @brief   Delay for a specified time in microseconds.
 *
 * @detail  This API will delay for a given amount of microseconds based on
 *          the microseconds precision of the consigured TC instance.
 *
 * @param   delay:  Time in microseconds to delay.
 *
 * @retval  None.
 *
 ****************************************************************************/
void tcMicrosecondDelay(uint32_t delay);

/****************************************************************************/
/**
 * @brief   Delay until a specified time in microseconds.
 *
 * @detail  This API mimics the behaviour of the FreeRTOS vTaskDelayUntil.
            Please see: https://www.freertos.org/vtaskdelayuntil.html
            Before calling it in your code or entering a loop, you must get
            current timer count value with tcGetCountValue and save it to the
            lastWakeTime variable. You need to to it only once for both scenarios
            since the variable is then updated inside the function.
 *
 * @param   *lastWakeTime:  Pointer to the last wake time.
            delay:          Time in microseconds to delay in total.
 *
 * @retval  None.
 *
 ****************************************************************************/
void tcMicrosecondDelayUntil(uint32_t *lastWakeTime, uint32_t delay);

#endif /*_TIMER_COUNTER_UNTIL_H_*/
