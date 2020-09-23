
/***********************************************************************
*@Author: sola
*@Date: 2019-11-16 19:58:35
*@FilePath: \RT1052\User\main.c
*@Drscription: 
***********************************************************************/
 
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "led.h"
#include "key.h"
#include "systick.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "main.h"
#include "bsp_touch_gtxx.h"
#include "bsp_i2c_touch.h"
#include "dht11.h"
#include "uart.h"
void Print_Log(void);
void Board_Config(void);

global_flag_t global_flag;
global_lcd_string_t global_lcd_string;
/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 20:15:06
*@Drscription: 
***********************************************************************/
int main(void)
{
    Board_Config();
    Print_Log();
    
    //SysTick_Config(CLOCK_GetFreq(kCLOCK_CpuClk) / 1000000);    
    systick_delay_init();    
    led_init();
    key_init();
    I2C_Init();
//    adc_bsp_init(ADC_Channel);
//    Pit_init(kPIT_Chnl_0,100000);  //100ms
//    Pit_init(kPIT_Chnl_1,800000);  //100ms
//    Pit_init(kPIT_Chnl_2,500000);  //100ms
//    I2C_Init();
//    dht11_init();
//	GTP_Init_Panel();
//    MPU6050_Init();
//    MPU6050_ReadID();
    BS_LCD_Init(LCD_INTERRUPT_DISABLE);
    LCD_Clear(CL_BLUE);
    LCD_SetFont(&Font8x16);
    //LCD_SetColors(CL_WHITE,CL_RED);
    LCD_SetBackColor(CL_BLUE);
    LCD_SetTextColor(CL_WHITE);
    PutPixel(70,200);
    lcd_key_creat();

    while(1)  
    {   
        LCD_Clear(CL_BLUE);
        delay_ms(500);
        LCD_Clear(CL_WHITE);
        delay_ms(500);
        LCD_Clear(CL_GREEN);
        delay_ms(500);
        LCD_Clear(CL_YELLOW);
        delay_ms(500);
        LCD_Clear(CL_MAGENTA);
        delay_ms(500);
        
    }			
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 23:31:46
*@Drscription: 
***********************************************************************/
void Print_Log(void)
{
    DEBUG_PRINT("\r\n");
    DEBUG_PRINT("CPU:             %d Hz", CLOCK_GetFreq(kCLOCK_CpuClk));
    DEBUG_PRINT("AHB:             %d Hz", CLOCK_GetFreq(kCLOCK_AhbClk));
    DEBUG_PRINT("SEMC:            %d Hz", CLOCK_GetFreq(kCLOCK_SemcClk));
    DEBUG_PRINT("SYSPLL:          %d Hz", CLOCK_GetFreq(kCLOCK_SysPllClk));
    DEBUG_PRINT("SYSPLLPFD0:      %d Hz", CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
    DEBUG_PRINT("SYSPLLPFD1:      %d Hz", CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
    DEBUG_PRINT("SYSPLLPFD2:      %d Hz", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
    DEBUG_PRINT("SYSPLLPFD3:      %d Hz", CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));	
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 23:31:50
*@Drscription: 
***********************************************************************/
void Board_Config(void) 
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
}

/****************************END OF FILE**********************/
