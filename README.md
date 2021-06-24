# samd21-microsecond-delay

This library implements a microsecond-precision delay feature to be used with Atmel's SAMD21 and similar MCUs in that family.
It uses TC3/TC4 to act as a 32-bit counter.
It uses the ASF Atmel API. (http://asf.atmel.com/docs/latest/api.html)


Please note that the clock source configured in `timer_counter_util.h` is the Generic Clock 4:
```
#define     CLOCK_SOURCE                GCLK_GENERATOR_4
```

In order to get this API running properly, you must edit your `conf_clocks.h` file to make the GCLK4 section look like this:
```
/* Configure GCLK generator 4 */
/* Used in TC3/TC4 32-bit counter */
#  define CONF_CLOCK_GCLK_4_ENABLE                true
#  define CONF_CLOCK_GCLK_4_RUN_IN_STANDBY        false
#  define CONF_CLOCK_GCLK_4_CLOCK_SOURCE          SYSTEM_CLOCK_SOURCE_OSC8M
#  define CONF_CLOCK_GCLK_4_PRESCALER             1
#  define CONF_CLOCK_GCLK_4_OUTPUT_ENABLE         false
```

If you need to use other clock source, please use the same template and change it in the API header file as well.

Pay attention to the clock source.
