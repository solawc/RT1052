/***********************************************************************
*@Author: sola
*@Date: 2019-11-16 19:58:33
*@FilePath: \RT1052\Libraries\hardware\key.h
*@Drscription: 
***********************************************************************/
#ifndef __key_h
#define __key_h

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"


#define KEY_ON
#define KEY_OFF

#define K1_PORT         GPIO5   
#define K1_PIN          0u    
#define K1_MUX          IOMUXC_SNVS_WAKEUP_GPIO5_IO00
#define K1_READ         GPIO_PinRead(K1_PORT,K1_PIN)

typedef enum
{
    Key_On,
    Key_Off,
}KEY_StatusDef;

typedef enum
{
    Key_Mode_Point,
    Key_Mode_Series,
}KEY_ModeDef;


typedef struct 
{
    KEY_StatusDef  KEY_Status;      //������״̬------�ж��Ƿ���
    uint32_t KEY_Num;               //����������------2^32��
    KEY_ModeDef  KEY_Mode;          //������ģʽ------�㰴��������
}KEY_StrInit;





void key_init(void);
uint8_t key_scanf(void);
#endif



