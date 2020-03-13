/***********************************************************************
*@Author: sola
*@Date: 2019-11-16 21:13:29
*@FilePath: \RT1052\Libraries\hardware\nvic.c
*@Drscription: 
***********************************************************************/

/***********************************************************************
*                                Inc
***********************************************************************/
#include "nvic.h"

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:53:45
*@Drscription: 
***********************************************************************/
void Set_NVIC_PriorityGroup(PriorityGroup_Type PriorityGroup) 
{
  NVIC_SetPriorityGrouping((uint32_t)PriorityGroup); //设置中断优先级分组
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:53:47
*@Drscription: 
***********************************************************************/
void Set_IRQn_Priority(IRQn_Type IRQn,PreemptPriority_Type PreemptPriority, SubPriority_Type SubPriorit)
{
    uint32_t PriorityGroup = 0;   //保存中断优先级分组
    uint32_t Priority_Encode = 0; //保存中断优先级编码
    PriorityGroup = NVIC_GetPriorityGrouping();//获得当前中断优先级分组
    Priority_Encode = NVIC_EncodePriority (PriorityGroup,(uint32_t)PreemptPriority,(uint32_t)SubPriorit);//得到中断优先级编码
  
    NVIC_SetPriority(IRQn, Priority_Encode);//设置中断编号的中断优先级
}





