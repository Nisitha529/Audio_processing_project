#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f4xx.h"
#include <stdint.h>

void start_conversion (void);
uint32_t adc_read (void);
void pa1_adc_init (void);

#endif
