/***********************************************************************
*@Author: sola
*@Date: 2019-11-16 20:29:40
*@FilePath: \RT1052\Libraries\hardware\pit.c
*@Drscription: 
***********************************************************************/

/***********************************************************************
*                                Inc
***********************************************************************/
#include "pit.h"
#include "fsl_pit.h"
#include "fsl_debug_console.h"
#include "main.h"

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:49:54
*@Drscription: 
***********************************************************************/
static void PIT_NVIC_Config(void)
{
    uint32_t Priority_Encode = 0;
    NVIC_SetPriorityGrouping(0x04);
    Priority_Encode = NVIC_EncodePriority (0x04, 0x06, 0x00);//得到中断优先级编码
    NVIC_SetPriority(PIT_IRQn,Priority_Encode);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: 
*@Author: sola
*@Date: 2019-11-17 17:32:42
*@Drscription: 
***********************************************************************/
void Pit_init(pit_chnl_t PIT_CHn,uint32_t reload)
{
    pit_config_t config;
    pit_chnl_t channel;
    
    if(PIT_CHn==0)      channel = kPIT_Chnl_0;
    else if(PIT_CHn==1) channel = kPIT_Chnl_1;
    else if(PIT_CHn==2) channel = kPIT_Chnl_2;
    else if(PIT_CHn==3) channel = kPIT_Chnl_3;

    /* PIT时钟配置 */
    CLOCK_SetMux(kCLOCK_PerclkMux,1U);
    CLOCK_SetDiv(kCLOCK_PerclkDiv,0U);
    
    PIT_GetDefaultConfig(&config);
    
    config.enableRunInDebug = true;
    
    PIT_Init(PIT, &config);
    
    /* 设置PIT定时器通道自动重装载值 */
    PIT_SetTimerPeriod(PIT,channel,USEC_TO_COUNT(reload, PIT_SOURCE_CLOCK));
    
    /* 清除通道的中断标志位 */
    PIT_ClearStatusFlags(PIT,channel,kPIT_TimerFlag);
    
    /* 使能通道的计时完成中断 */
    PIT_EnableInterrupts(PIT, channel, kPIT_TimerInterruptEnable);
    
    //Set_NVIC_PriorityGroup(Group_4);
    //Set_IRQn_Priority(PIT_IRQn,Group4_PreemptPriority_6, Group4_SubPriority_0);
	PIT_NVIC_Config();
    /* 使能中断 */
    EnableIRQ(PIT_IRQn);

    if(PIT_CHn==0)      PIT_StartTimer(PIT,kPIT_Chnl_0);
    else if(PIT_CHn==1) PIT_StartTimer(PIT,kPIT_Chnl_1);
    else if(PIT_CHn==2) PIT_StartTimer(PIT,kPIT_Chnl_2);
    else if(PIT_CHn==3) PIT_StartTimer(PIT,kPIT_Chnl_3);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:50:05
*@Drscription: 
***********************************************************************/
void PIT_IRQHandler(void)
{
    if(PIT_GetStatusFlags(PIT, kPIT_Chnl_0))
    {
        /* 清除中断标志位 */
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag); 
        global_flag.adc_v_get = adc_get(ADC_Channel);
        global_flag.adc_v_get = (global_flag.adc_v_get/(float)4096)*(float)3.3;
        sprintf((char *)global_lcd_string.lcd_adc_str,
                "PIT ADC Value :%.2fV",global_flag.adc_v_get);
        LCD_DisplayStringLine(LINE(6),(uint8_t *)global_lcd_string.lcd_adc_str);
    }
    else if(PIT_GetStatusFlags(PIT, kPIT_Chnl_1))
    {
        /* 清除中断标志位 */
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag); 

        MPU6050_Gyro_Read(global_flag.gyro_data);
        sprintf((char *)global_lcd_string.lcd_mpu_g_str,
                "MPU Gyro:%d    %d   %d",
                global_flag.gyro_data[0],
                global_flag.gyro_data[1],
                global_flag.gyro_data[2]);
        
        LCD_ClearLine(LINE(7));
        LCD_DisplayStringLine(LINE(7),(uint8_t *)global_lcd_string.lcd_mpu_g_str);
    }
}



