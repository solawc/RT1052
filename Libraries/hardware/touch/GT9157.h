/***********************************************************************
*@Date: 2020-06-05 15:34:49
*@LastEditors: SOLA
*@LastEditTime: 2020-06-09 16:09:57
*@FilePath: \RT1052\Libraries\hardware\touch\GT9157.h
***********************************************************************/
#ifndef __GT9157_H
#define __GT9157_H

#include "main.h"
#include "i2c.h"

#define touch_RST_PORT          GPIO1  
#define touch_RST_PIN           (2U)
#define touch_RST_MUX           IOMUXC_GPIO_AD_B0_02_GPIO1_IO02

#define touch_INT_PORT          GPIO1
#define touch_INT_PIN           (11U)
#define touch_INT_MUX           IOMUXC_GPIO_AD_B0_11_GPIO1_IO11

#define touch_INT_IRQ           GPIO1_Combined_0_15_IRQn
#define touch_INT_IRQHANDER     GPIO1_Combined_0_15_IRQHandler



#endif
