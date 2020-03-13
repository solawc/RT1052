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
  NVIC_SetPriorityGrouping((uint32_t)PriorityGroup); //�����ж����ȼ�����
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
    uint32_t PriorityGroup = 0;   //�����ж����ȼ�����
    uint32_t Priority_Encode = 0; //�����ж����ȼ�����
    PriorityGroup = NVIC_GetPriorityGrouping();//��õ�ǰ�ж����ȼ�����
    Priority_Encode = NVIC_EncodePriority (PriorityGroup,(uint32_t)PreemptPriority,(uint32_t)SubPriorit);//�õ��ж����ȼ�����
  
    NVIC_SetPriority(IRQn, Priority_Encode);//�����жϱ�ŵ��ж����ȼ�
}





