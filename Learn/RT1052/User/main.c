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

void Print_Log(void);
void Board_Config(void);
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

    SysTick_Config(528000000/1000000);
    PRINTF("Systick init succeed\n");
    led_init();
    PRINTF("LED init succeed\n");
    key_init();
    PRINTF("KEY init succeed\n");
    I2C_Init();
    PRINTF("I2C init succeed\n");

    LCD_Init(LCD_INTERRUPT_DISABLE);
    LCD_Clear(CL_RED);
    LCD_SetFont(&Font8x16);
    LCD_SetColors(CL_WHITE,CL_RED);
    
    LCD_DisplayStringLine(LINE(0),(uint8_t *)"Systick init succeed");delay_ms(500);
    LCD_DisplayStringLine(LINE(1),(uint8_t *)"LED init succeed");delay_ms(500);
    LCD_DisplayStringLine(LINE(2),(uint8_t *)"KEY init succeed");delay_ms(500);
    LCD_DisplayStringLine(LINE(3),(uint8_t *)"I2C init succeed");delay_ms(500);
    LCD_DisplayStringLine(LINE(4),(uint8_t *)"ADC init succeed");delay_ms(500);


    uint16_t x_point = 100;
    while(1)
    {   
        LCD_DispString(0, 500, (uint8_t *)adc_dis);
        LCD_DrawRect(x_point,200,100,100);
        LCD_DispString(x_point+50-16, 200+50-8, "KEY1" );

        LCD_DrawRect(x_point+200,200,100,100);
        LCD_DispString(x_point+200+50-16, 200+50-8, "KEY2" );
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
    PRINTF("\r\n");
    PRINTF("CPU:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_CpuClk));
    PRINTF("AHB:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_AhbClk));
    PRINTF("SEMC:            %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SemcClk));
    PRINTF("SYSPLL:          %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllClk));
    PRINTF("SYSPLLPFD0:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
    PRINTF("SYSPLLPFD1:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
    PRINTF("SYSPLLPFD2:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
    PRINTF("SYSPLLPFD3:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));	
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
