/***********************************************************************
*@Author: sola
*@Date: 2019-11-16 19:58:33
*@FilePath: \RT1052\Libraries\hardware\led.c
*@Drscription: 
***********************************************************************/


/***********************************************************************
*                                Inc
***********************************************************************/
#include "led.h"



#define LED_PAD_CONFIG_DATA            (IOMUXC_SW_PAD_CTL_PAD_SRE(0) | \
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
static void led_gpio_mux_config(void)     //…Ë÷√GPIO∏¥”√
{
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09,0U);  //CORE LED
    
    IOMUXC_SetPinMux(LED_R_MUX,0U);         
    IOMUXC_SetPinMux(LED_G_MUX,0U);
    IOMUXC_SetPinMux(LED_B_MUX,0U);
}
    
/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:53:21
*@Drscription: 
***********************************************************************/    
static void led_gpio_pad_config(void)   //…Ë÷√GPIO PAD
{
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09,
                        LED_PAD_CONFIG_DATA);
    
    IOMUXC_SetPinConfig(LED_R_MUX,LED_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(LED_G_MUX,LED_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(LED_B_MUX,LED_PAD_CONFIG_DATA);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:53:25
*@Drscription: 
***********************************************************************/
static void led_gpio_mode_config()
{
    gpio_pin_config_t led_config;
    
    led_config.direction =  kGPIO_DigitalOutput;
    led_config.interruptMode = kGPIO_NoIntmode;
    led_config.outputLogic = 1U;
    
    GPIO_PinInit(GPIO1, 9u,&led_config);
    
    GPIO_PinInit(LED_R_PORT, LED_R_PIN,&led_config);
    GPIO_PinInit(LED_G_PORT, LED_G_PIN,&led_config);
    GPIO_PinInit(LED_B_PORT, LED_B_PIN,&led_config);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:53:27
*@Drscription: 
***********************************************************************/
void led_init(void)
{
    led_gpio_mux_config();
    led_gpio_pad_config();
    led_gpio_mode_config();
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:53:30
*@Drscription: 
***********************************************************************/
void led_on(uint32_t LED_X_PIN)
{
    GPIO_PinWrite(LED_R_PORT,LED_X_PIN,0U);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:53:35
*@Drscription: 
***********************************************************************/
void led_off(uint32_t LED_X_PIN)
{
    GPIO_PinWrite(LED_R_PORT,LED_X_PIN,1U);
}

/***********************************************************************
*@Date: 2020-05-22 14:03:29
*@Function: 
*@Input: 
*@Return: 
*@Drscription: 
***********************************************************************/
void led_toggle(uint32_t LED_X_PIN)
{
    GPIO_PinWrite(LED_R_PORT,LED_X_PIN,
                 (1 - GPIO_PinRead(LED_R_PORT, 
                                   LED_X_PIN)));
}


