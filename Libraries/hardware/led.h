/***********************************************************************
*@Date: 2020-05-22 02:12:37
*@LastEditors: SOLA
*@LastEditTime: 2020-05-24 17:47:03
*@FilePath: \RT1052\Libraries\hardware\led.h
***********************************************************************/
/*
*@Date: 2020-03-15 02:33:54
*@LastEditors: SOLA
*@LastEditTime: 2020-03-20 01:33:19
*@FilePath: \RT1052\Libraries\hardware\led.h
*/
#ifndef __led_h
#define __led_h

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"

#define LED_ON      1
#define LED_OFF     0

#define LED_R_PORT      GPIO1
#define LED_G_PORT      GPIO1
#define LED_B_PORT      GPIO1

#define LED_R_PIN       24U         //GPIO_AD_B1_08
#define LED_G_PIN       25U         //GPIO_AD_B1_09
#define LED_B_PIN       10U         //GPIO_AD_B0_10

#define LED_R_MUX       IOMUXC_GPIO_AD_B1_08_GPIO1_IO24
#define LED_G_MUX       IOMUXC_GPIO_AD_B1_09_GPIO1_IO25
#define LED_B_MUX       IOMUXC_GPIO_AD_B0_10_GPIO1_IO10


void led_init(void);
void led_on(uint32_t LED_X_PIN);
void led_off(uint32_t LED_X_PIN);
void led_toggle(uint32_t LED_X_PIN);
#endif
