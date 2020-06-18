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
#include "./touch/bsp_touch_gtxx.h"

#include "main.h"

#define KEY_PAD_CONFIG_DATA            (IOMUXC_SW_PAD_CTL_PAD_SRE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | \
                                        IOMUXC_SW_PAD_CTL_PAD_ODE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PKE(1) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE(1) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUS(3) | \
                                        IOMUXC_SW_PAD_CTL_PAD_HYS(1))
/*    PAD ����˵��
*1��SER���ʹر�
*2��DSEǿ�����ر�
*3��SPEED�ٶ�ѡ�� ��100MHz
*4��ODE��©��ʹ��
*6��PKE������ʹ��
*7��PUE������ѡ��ѡ������
*8��PUS����������ѡ��ѡ��22K
*9���ͻػ�����ʹ��
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
    
    CLOCK_EnableClock(kCLOCK_IomuxcSnvs);     //��ʱ��
    
    EnableIRQ(GPIO5_Combined_0_15_IRQn);      //ѡ���ж�Դ��ʹ��
    
    GPIO_PortEnableInterrupts(K1_PORT,1U << K1_PIN);    //ʹ�ܶ˿��ж�
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
    
    /*����IO����*/
    IOMUXC_SetPinMux(K1_MUX,0u);
    IOMUXC_SetPinMux(K2_MUX,0u);
    /*����GOIO PAD*/
    IOMUXC_SetPinConfig(K1_MUX,KEY_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(K2_MUX,KEY_PAD_CONFIG_DATA);
    /*����GPIO ģʽ*/
    KEY_Config.direction = kGPIO_DigitalInput;      //����Ϊ����ģʽ
    KEY_Config.outputLogic = 1u;                    //������������ʱ��Ч 
    KEY_Config.interruptMode = kGPIO_NoIntmode;     //��ʹ���ж� 
    //KEY_Config.interruptMode = kGPIO_IntLowLevel;   //�͵�ƽ�����ж�
    GPIO_PinInit(K1_PORT,K1_PIN,&KEY_Config);
    GPIO_PinInit(K2_PORT,K2_PIN,&KEY_Config);
    //key_it_config();                                //�ж�����
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

    if(key_status && ((K1_READ==0) ||(K2_READ==0)))
    {
        key_status = 0;
        if(K1_READ==0) return 1;
        else if (K2_READ==0) return 2;
    }
    else if ((K1_READ==1) && (K2_READ==1))
    {
        key_status = 1;
    }
    return 0;
}

lcd_key_t lcd_key1;

bool lcd_key_creat(void)
{
    lcd_key1.key_high = 50;
    lcd_key1.key_start_x_point = 100; 
    lcd_key1.key_start_y_point = 200;
    lcd_key1.key_weigth = 80;
    
    LCD_DrawRect(lcd_key1.key_start_x_point, 
                 lcd_key1.key_start_y_point,
                 lcd_key1.key_weigth,
                 lcd_key1.key_high);
    
    return true;
}

bool lcd_key_scanf(void)
{
    if(x_point>100 && x_point <150)
    {
        return true;
    }
    else
    {
        return false;
    }
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
    GPIO_PortClearInterruptFlags(K1_PORT,1U << K1_PIN); //����жϱ�־�?
    
    led_toggle(LED_B_PIN);

}
*/


