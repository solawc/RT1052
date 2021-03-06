/***********************************************************************
*@Date: 2020-05-22 04:47:09
*@LastEditors: SOLA
*@LastEditTime: 2020-05-24 18:05:57
*@FilePath: \RT1052\Libraries\hardware\dht11.h
***********************************************************************/
#ifndef __dht11_h
#define __dht11_h

#include "main.h"

/*底层接口*/
#define __DHT11_GPIO_INIT()     dht11_gpio_init()
#define __DHT11_MODE(MODE)      DHT11_MODE(MODE)
#define __DHT11_OUT_H()         GPIO_PinWrite(DHT11_PORT,DHT11_PIN,1U)
#define __DHT11_OUT_L()         GPIO_PinWrite(DHT11_PORT,DHT11_PIN,0U)
#define __DHT11_READ()          GPIO_PinRead(DHT11_PORT,DHT11_PIN)    
#define __DHT11_DELAY_MS(nms)   delay_ms(nms)
#define __DHT11_DELAY_US(nms)   delay_us(nms)

/*硬件接口*/
#define __DHT11_PIN_CLK()       
#define DHT11_PIN              	27U 
#define DHT11_PORT              GPIO1

/*延时函数*/
#define  SYSCLK                             600000000/1000000                   //指明CPU工作频率为(SystemCoreClock/1000000)MHz
#define  A                                  12                                   //一次循环所花的周期数
#define  B                                  2                                   //调用、初始化、返回总共所用的周期数
#define  delay_us(nus)                      wait(((nus)*(SYSCLK)-(B))/(A))
// #define  delay_ms(nms)                      delay_us((nms)*1000)
// #define  delay_s(ns)                        delay_ms((ns)*1000)

/*结构体成员定义*/
typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
}DHT11_Data_TypeDef;


/*函数声明*/
void  wait(unsigned long n);
void dht11_init(void);
uint8_t ReadByte(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
void DHT11_PRINTF(void);
#endif
