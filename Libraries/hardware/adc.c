/***********************************************************************
*@Author: sola
*@Date: 2019-11-22 00:40:29
*@FilePath: \RT1052\Libraries\hardware\adc.c
*@Drscription: 
***********************************************************************/

#include "adc.h"
#include "fsl_adc.h"
#include "fsl_io.h"
#include "fsl_debug_console.h"

#define ADC_PAD_CONFIG_DATA            (IOMUXC_SW_PAD_CTL_PAD_SRE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(6) | \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | \
                                        IOMUXC_SW_PAD_CTL_PAD_ODE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PKE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUS(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_HYS(0))

/*
*@Date: 2020-03-18 03:01:35
*@Function: 
*@Input: 
*@Return: 
*@Drscription: 
*/
bool Adc_Init(void)
{
    gpio_pin_config_t Config;
    adc_config_t config;
    adc_channel_config_t ADC_CH_config;

    Config.direction = kGPIO_DigitalInput;
    Config.interruptMode = kGPIO_NoIntmode;
    Config.outputLogic = 0u;
    GPIO_PinInit(ADC_GPIO, ADC_PIN, &Config);

    IOMUXC_SetPinMux(ADC_MUX,0);
    IOMUXC_SetPinConfig(ADC_MUX,ADC_PAD_CONFIG_DATA);

    ADC_GetDefaultConfig(&config);
    ADC_Init(ADCx, &config);
    ADC_SetHardwareAverageConfig(ADCx,kADC_HardwareAverageCount32);

    ADC_CH_config.channelNumber = ADC_Channel;
    ADC_CH_config.enableInterruptOnConversionCompleted = true;
    ADC_SetChannelConfig(ADCx,ADC_GROUP,&ADC_CH_config);

    if(ADC_DoAutoCalibration(ADCx)==kStatus_Success)
    {
      
    }
    else
    {
       
    }

    return  true;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-22 20:46:10
*@Drscription: 
***********************************************************************/
uint32_t ADC_Get(void)
{   
    adc_channel_config_t adcChannelConfigStruct;
    adcChannelConfigStruct.channelNumber = ADC_Channel;
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = true;
    ADC_SetChannelConfig(ADCx, ADC_GROUP, &adcChannelConfigStruct);
    
    return ADC_GetChannelConversionValue(ADCx,ADC_GROUP);
}
