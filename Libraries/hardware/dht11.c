#include "dht11.h"

//GPIO_InitTypeDef DHT11_GPIO_Init;

DHT11_Data_TypeDef DHT11_Data;


#define DHT11_PAD_CONFIG_DATA          (IOMUXC_SW_PAD_CTL_PAD_SRE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(6) | \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | \
                                        IOMUXC_SW_PAD_CTL_PAD_ODE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PKE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUS(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_HYS(0))

/****************************************************************
*@function: dht11_gpio_init
*@input   : none
*@output  : none
*@describe: DHT11��GPIO�ڳ�ʼ��
*@author  : sola
****************************************************************/
void dht11_gpio_init(void)
{ 
	gpio_pin_config_t dht11_Config;

	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_GPIO1_IO25,0);
	
	dht11_Config.direction = kGPIO_DigitalOutput;
	dht11_Config.interruptMode = kGPIO_NoIntmode;
	dht11_Config.outputLogic = 0U;
	GPIO_PinInit(DHT11_PORT, DHT11_PIN, &dht11_Config);
}

/****************************************************************
*@function: DHT11_MODE
*@input   : mode    ��0/1��
*@output  : none
*@describe: DHT11 GPIO�������ģʽѡ��
*@author  : sola
****************************************************************/
void DHT11_MODE(uint8_t mode)
{
	gpio_pin_config_t dht11_Config;
	if(mode == 0)
	{
		dht11_Config.direction = kGPIO_DigitalInput;
		dht11_Config.interruptMode = kGPIO_NoIntmode;
		dht11_Config.outputLogic = 0;
		GPIO_PinInit(DHT11_PORT, DHT11_PIN, &dht11_Config);
	}
	else if(mode == 1)
	{
		dht11_Config.direction = kGPIO_DigitalOutput;
		dht11_Config.interruptMode = kGPIO_NoIntmode;
		dht11_Config.outputLogic = 0;
		GPIO_PinInit(DHT11_PORT, DHT11_PIN, &dht11_Config);
	}
}


/*---------------------------Ӧ�ò�----------------------------*/

/****************************************************************
*@function: dht11_delay
*@input   : n (MHz)  
*@output  : none
*@describe: ��ʱ
*@author  : sola
****************************************************************/
void wait(unsigned long n)
{   
	do{
	n--;
	}while(n);
}

/****************************************************************
*@function: dht11_init
*@input   : none
*@output  : none
*@describe: DHT11 ��ʼ�ź�
*@author  : sola
****************************************************************/
void dht11_init(void)
{
    __DHT11_GPIO_INIT();
}

/****************************************************************
*@function: ReadByte
*@input   : none
*@output  : temp
*@describe: ��һ���ֽ�
*@author  : sola
****************************************************************/
uint8_t ReadByte(void) {

	uint8_t i, temp = 0;

	for(i=0;i<8;i++) {

		while(__DHT11_READ() == 0);
		
		__DHT11_DELAY_US(40);               //40us
	
		if(__DHT11_READ() == 1) {

			while(__DHT11_READ() == 1);

			temp |= (uint8_t)(0x01<<(7-i));
		}
		else {
			
			temp &= (uint8_t)~(0x01<<(7-i));
		}
	}	
	return temp;
} 

/****************************************************************
*@function: Read_DHT11
*@input   : *DHT11_Data
*@output  : temp
*@describe: DHT11 ������
*@author  : sola
****************************************************************/
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data) {
    
    
	__DHT11_MODE(1);            //����Ϊ���
	
	__DHT11_OUT_L();            //����
	
	__DHT11_DELAY_MS(20);       //18ms

	__DHT11_OUT_H();            //����
    
    __DHT11_DELAY_US(13);       //13us

	__DHT11_MODE(0);            //����Ϊ����

	if(__DHT11_READ() == 0) {

		while(__DHT11_READ() == 0); 

		while(__DHT11_READ() == 1);

		DHT11_Data->humi_int= ReadByte();   //��ȡʪ������

		DHT11_Data->humi_deci= ReadByte();  //��ȡʪ��С��

		DHT11_Data->temp_int= ReadByte();   //��ȡ�¶�����

		DHT11_Data->temp_deci= ReadByte();  //��ȡ�¶�����

		DHT11_Data->check_sum= ReadByte();  //Ӧ���ȡ

		__DHT11_MODE(1);                    //����Ϊ���

		__DHT11_OUT_H();

		if(DHT11_Data->check_sum == 
                                    DHT11_Data->humi_int + 
                                        DHT11_Data->humi_deci + 
                                            DHT11_Data->temp_int+ 
                                                DHT11_Data->temp_deci) {
			return SUCCESS;
		}
		else {		
			return ERROR;	
		}
	}
    return 0;
}


/****************************************************************
*@function: DHT11_PRINTF
*@input   : none
*@output  : none
*@describe: DHT11 ��ӡ����
*@author  : sola
****************************************************************/
#if 1
void DHT11_PRINTF(void) {

    if(Read_DHT11(&DHT11_Data) == SUCCESS) {
              
            printf("\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n",
                                                                DHT11_Data.humi_int,
                                                                DHT11_Data.humi_deci,
                                                                DHT11_Data.temp_int,
                                                                DHT11_Data.temp_deci);
  } 
  else 
  {
		printf("\nDHT11 READ ERROR\r\n");
  }
}
#endif
