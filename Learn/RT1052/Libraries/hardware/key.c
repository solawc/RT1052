/***********************************************************************
*@Author: sola
*@Date: 2019-11-16 19:58:33
*@FilePath: \RT1052\Libraries\hardware\key.c
*@Drscription: 
***********************************************************************/

/***********************************************************************
*                                Inc
***********************************************************************/
#include "key.h"



#define KEY_PAD_CONFIG_DATA            (IOMUXC_SW_PAD_CTL_PAD_SRE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | \
                                        IOMUXC_SW_PAD_CTL_PAD_ODE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PKE(1) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE(1) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUS(3) | \
                                        IOMUXC_SW_PAD_CTL_PAD_HYS(1))
/*    PAD 配置说明
*1、SER摆率关闭
*2、DSE强驱动关闭
*3、SPEED速度选择 ：100MHz
*4、ODE开漏不使能
*6、PKE上下拉使能
*7、PUE上下拉选择，选择上拉
*8、PUS上下拉电阻选择，选择22K
*9、滞回缓冲器使能
*/                                        

/*-------------------------------------------------------------------------------*/

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:52:38
*@Drscription: 
***********************************************************************/
void key_it_config(void)
{
    
    CLOCK_EnableClock(kCLOCK_IomuxcSnvs);     //打开时钟
    
    EnableIRQ(GPIO5_Combined_0_15_IRQn);      //选择中断源并使能
    
    GPIO_PortEnableInterrupts(K1_PORT,1U << K1_PIN);    //使能端口中断
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:52:42
*@Drscription: 
***********************************************************************/
void key_init(void) 
{
    gpio_pin_config_t KEY_Config;
    
    /*设置IO复用*/
    IOMUXC_SetPinMux(K1_MUX,0u);
    
    /*配置GOIO PAD*/
    IOMUXC_SetPinConfig(K1_MUX,KEY_PAD_CONFIG_DATA);
    
    /*配置GPIO 模式*/
    KEY_Config.direction = kGPIO_DigitalInput;      //配置为输入模式
    KEY_Config.outputLogic = 1u;                    //此配置在输入时无效 
    KEY_Config.interruptMode = kGPIO_NoIntmode;     //不使用中断 
    //KEY_Config.interruptMode = kGPIO_IntLowLevel;   //低电平触发中断
    GPIO_PinInit(K1_PORT,K1_PIN,&KEY_Config);
    
    //key_it_config();                                //中断配置
} 

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:52:47
*@Drscription: 
***********************************************************************/
uint8_t key_scanf(void)
{
    static uint8_t key_status=1;

    if(key_status && (K1_READ==0) )
    {
        key_status = 0;
        if(K1_READ==0) return 1;
    }
    else if(K1_READ==1)
    {
        key_status = 1;
    }
    return 0;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:52:52
*@Drscription: 
***********************************************************************/
/*
void GPIO5_Combined_0_15_IRQHandler(void)
{
    GPIO_PortClearInterruptFlags(K1_PORT,1U << K1_PIN); //清除中断标志位
    
    led_toggle(LED_B_PIN);

}
*/


