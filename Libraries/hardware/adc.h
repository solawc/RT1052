/***********************************************************************
*@Author: sola
*@Date: 2019-11-22 00:40:36
*@FilePath: \RT1052\Libraries\hardware\adc.h
*@Drscription: 
***********************************************************************/
#ifndef __adc_h
#define __adc_h

#include "fsl_common.h"

#define ADC_GPIO    GPIO1
#define ADC_PIN     22U
#define ADC_MUX     IOMUXC_GPIO_AD_B1_06_GPIO1_IO22

#define ADCx        ADC1
#define ADC_Channel 11U
#define ADC_GROUP   0U

bool adc_bsp_init(uint16_t adc_channel_x);
uint32_t adc_get(uint16_t adc_channel_x);

#endif /* !__adc_h */
