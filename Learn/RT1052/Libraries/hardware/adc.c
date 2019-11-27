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



/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:53:18
*@Drscription: 
***********************************************************************/

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-22 00:43:50
*@Drscription: 
***********************************************************************/
bool Adc_Init(void)
{
    gpio_pin_config_t Config;
    adc_config_t config;
    adc_channel_config_t ADC_CH_config;

    Config.direction = kGPIO_DigitalInput;
    Config.interruptMode = kGPIO_NoIntmode;
    Config.outputLogic = 0u;
    GPIO_PinInit(ADC_GPIO, ADC_PIN, &Config);


    ADC_GetDefaultConfig(&config);
    ADC_Init(ADCx, &config);

    ADC_SetHardwareAverageConfig(ADCx,kADC_HardwareAverageCount32);

    ADC_CH_config.channelNumber = ADC_Channel;
    ADC_CH_config.enableInterruptOnConversionCompleted = true;
    ADC_SetChannelConfig(ADCx,ADC_GROUP,&ADC_CH_config);

    if(ADC_DoAutoCalibration(ADCx)==kStatus_Success)
    {
        PRINTF("校正完成\n");
    }
    else
    {
        PRINTF("校正失败\n");
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
    return ADC_GetChannelConversionValue(ADCx,ADC_Channel);
}
