/***********************************************************************
*@Author: sola
*@Date: 2019-11-16 19:58:33
*@FilePath: \RT1052\Libraries\hardware\systick.c
*@Drscription: 
***********************************************************************/

/***********************************************************************
*                                Inc
***********************************************************************/
#include "systick.h"
#include "fsl_debug_console.h"

void systick_delay_init(void)
{
    SysTick->LOAD = 1000;

    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);

    SysTick->VAL = 0UL;
    
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk   |
                    SysTick_CTRL_ENABLE_Msk;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:54:57
*@Drscription: 
***********************************************************************/
void delay_us(uint32_t tick)
{
    uint32_t ticks;
    uint32_t told,tnow,tcnt=0;
    uint32_t reload=SysTick->LOAD;   
                                                     
    ticks=tick * (CLOCK_GetFreq(kCLOCK_CpuClk) / 1000000); 
    told=SysTick->VAL;                                       
    while(1)
    {
        tnow=SysTick->VAL;        
        if(tnow!=told)
        {            
            if(tnow<told)tcnt+=told-tnow;       
            else tcnt+=reload-tnow+told;            
            told=tnow;
            if(tcnt>=ticks)break;                        
        }  
    }
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:55:06
*@Drscription: 
***********************************************************************/
void delay_ms(uint32_t tick)
{
    for(int i = tick;i>0;i--)
    {
        delay_us(1000);
    }
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:55:10
*@Drscription: 
***********************************************************************/
void SysTick_Handler(void)
{
    
}

