/***********************************************************************
*@Date: 2020-05-22 02:22:45
*@LastEditors: SOLA
*@LastEditTime: 2020-06-03 10:06:27
*@FilePath: \RT1052\User\main.h
***********************************************************************/
#ifndef __main_h
#define __main_h

#include "board.h"
#include "dht11.h"
#include "stdint.h"
#include "mpu6050.h"

typedef struct
{
    short gyro_data[3];
    short arce_data[3];
    uint8_t flag:1;
    float adc_v_get;
    
}global_flag_t;

typedef struct
{
    char lcd_adc_str[20];
    char lcd_mpu_g_str[20];
    
}global_lcd_string_t;

extern global_flag_t global_flag;
extern global_lcd_string_t global_lcd_string;

#define SUCCESS							    1
#define ERROR					    	    0

#define DEBUG_SWITCH                        1
#if DEBUG_SWITCH
#define DEBUG_ERROR(fmt,arg...)             do{printf("<<-ERROR->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)
#define DEBUG_PRINT(fmt,arg...)             do{printf("<<-DEBUG->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)                       
#else
#define DEBUG_ERROR(fmt,arg...)
#define DEBUG_PRINT(fmt,arg...)
#endif 

#endif
