
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
    adc_bsp_init(ADC_Channel);
    Pit_init(kPIT_Chnl_0,100000);  //100ms
    Pit_init(kPIT_Chnl_1,80000);  //100ms

    //I2C_Init();
	GTP_Init_Panel();
    MPU6050_Init();
    MPU6050_ReadID();
    BS_LCD_Init(LCD_INTERRUPT_DISABLE);
    LCD_Clear(CL_RED);
    LCD_SetFont(&Font8x16);
    LCD_SetColors(CL_WHITE,CL_RED);
    
    LCD_DisplayStringLine(LINE(0),(uint8_t *)"Systick init succeed");delay_ms(500);
    LCD_DisplayStringLine(LINE(1),(uint8_t *)"LED init succeed");delay_ms(500);
    LCD_DisplayStringLine(LINE(2),(uint8_t *)"KEY init succeed");delay_ms(500);
    LCD_DisplayStringLine(LINE(3),(uint8_t *)"I2C init succeed");delay_ms(500);
    LCD_DisplayStringLine(LINE(4),(uint8_t *)"ADC init succeed");delay_ms(500);

    while(1)  
    {   
        delay_ms(100);
        // GPIO_PortToggle(LED_R_PORT, 1U << LED_R_PIN);
        led_toggle(LED_R_PIN);
        //GTP_TouchProcess();    

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
    DEBUG_PRINT("CPU:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_CpuClk));
    DEBUG_PRINT("AHB:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_AhbClk));
    DEBUG_PRINT("SEMC:            %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SemcClk));
    DEBUG_PRINT("SYSPLL:          %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllClk));
    DEBUG_PRINT("SYSPLLPFD0:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
    DEBUG_PRINT("SYSPLLPFD1:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
    DEBUG_PRINT("SYSPLLPFD2:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
    DEBUG_PRINT("SYSPLLPFD3:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));	
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
