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

#define K2_PORT         GPIO1   
#define K2_PIN          5u    
#define K2_MUX          IOMUXC_GPIO_AD_B0_05_GPIO1_IO05
#define K2_READ         GPIO_PinRead(K2_PORT,K2_PIN)

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
    KEY_StatusDef  KEY_Status;      //按键的状态------判断是否按下
    uint32_t KEY_Num;               //按键的数量------2^32个
    KEY_ModeDef  KEY_Mode;          //按键的模式------点按还是连按
}KEY_StrInit;


typedef struct 
{
    uint32_t key_start_x_point;
    uint32_t key_start_y_point;
    uint32_t key_weigth;
    uint32_t key_high;

}lcd_key_t;




bool lcd_key_creat(void);
bool lcd_key_scanf(void);
void key_init(void);
uint8_t key_scanf(void);
#endif



