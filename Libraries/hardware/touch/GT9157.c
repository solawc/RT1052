/***********************************************************************
*@Date: 2020-06-05 15:34:41
*@LastEditors: SOLA
*@LastEditTime: 2020-06-09 16:30:58
*@FilePath: \RT1052\Libraries\hardware\touch\GT9157.c
***********************************************************************/
#include "GT9157.h"

#define ONLY_ONE_I2C_DEV            0

void gt9157_touch_init(void)
{   
    gpio_pin_config_t Config;

#if ONLY_ONE_I2C_DEV
    I2C_Init();
#endif 

    IOMUXC_SetPinMux(touch_RST_MUX, 0U);
    IOMUXC_SetPinMux(touch_INT_MUX, 0U);

    Config.direction = kGPIO_DigitalOutput;
    Config.interruptMode = kGPIO_NoIntmode;
    Config.outputLogic = 0;
    GPIO_PinInit(touch_RST_PORT, touch_RST_PIN, &Config);
    GPIO_PinInit(touch_INT_PORT, touch_INT_PIN, &Config);

    GPIO_PinWrite(touch_RST_PORT, touch_RST_PIN,0U);
    GPIO_PinWrite(touch_INT_PORT, touch_INT_PIN,0U);

    delay_us(200);

    GPIO_PinWrite(touch_RST_PORT, touch_RST_PIN,1U);
    delay_ms(20);

    Config.direction = kGPIO_DigitalInput;
    Config.interruptMode = kGPIO_IntRisingEdge;
    Config.outputLogic = 0;
    GPIO_PinInit(touch_INT_PORT, touch_INT_PIN, &Config);

    GPIO_PortEnableInterrupts(touch_INT_PORT,1U<<touch_INT_PIN);
}
