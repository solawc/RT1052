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
#define ADC_PIN     27U
#define ADC_MUX     IOMUXC_GPIO_AD_B1_11_GPIO1_IO27

#define ADCx        ADC1
#define ADC_Channel 0U
#define ADC_GROUP   0U



bool Adc_Init(void);
uint32_t ADC_Get(void);

#endif /* !__adc_h */
