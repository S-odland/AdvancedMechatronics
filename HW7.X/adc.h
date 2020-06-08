  
#ifndef ADC_H__
#define ADC_H__

#include <xc.h>
#include "i2c_master_noint.h"
#include "ssd1306.h"
#include "imu.h"

void adc_setup();
unsigned int adc_sample_convert(int pin);

void ctmu_setup();
int ctmu_read(int pin, int delay);

#endif