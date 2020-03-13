/***********************************************************************
*@Author: sola
*@Date: 2019-11-17 17:05:11
*@FilePath: \RT1052\Libraries\hardware\i2c.c
*@Drscription: 
***********************************************************************/

/***********************************************************************
*                                Inc
***********************************************************************/
#include "i2c.h"
#include "fsl_iomuxc.h"
#include "fsl_lpi2c.h"




#if !defined(USE_I2C_SF)

#define I2C_PAD_CONFIG_DATA            (IOMUXC_SW_PAD_CTL_PAD_SRE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(6) | \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | \
                                        IOMUXC_SW_PAD_CTL_PAD_ODE(1) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PKE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUS(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_HYS(0))

/*    PAD ����˵��
*1��SER���ʹر�
*2��DSEǿ�����ر�
*3��SPEED�ٶ�ѡ�� ��100MHz
*4��ODE��©ʹ��
*6��PKE������ʧ��
*7��PUE������ѡ��ѡ������
*8��PUS����������ѡ��ѡ��22K
*9���ͻػ�����ʹ��
*/

/***********************************************************************
*@Function: I2C_Init
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-17 17:49:06
*@Drscription: 
***********************************************************************/
void I2C_Init(void)
{
    lpi2c_master_config_t masterConfig;
    
    /* 
     * @ʱ������
     * LPI2C1��ʱ����Դ��,ѡ��0������PLL3��ѡ��1������osc_clk
     * ��������ѡ��0---����PLL3��480MHz��,���Է�Ƶϵ��ѡ��5������6-1��
     */   
    CLOCK_SetMux(kCLOCK_Lpi2cMux, 0);              
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv,(6-1));
    /* IO�������� */
    IOMUXC_SetPinMux(I2C_SCL_MUX,1U);
    IOMUXC_SetPinMux(I2C_SDA_MUX,1U);
    
    /* IO PAD���� */
    IOMUXC_SetPinConfig(I2C_SCL_MUX,I2C_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(I2C_SDA_MUX,I2C_PAD_CONFIG_DATA);

    /* ��ȡĬ������ */
    LPI2C_MasterGetDefaultConfig(&masterConfig);

    /* ����LPI2C�ٶ�400k */
    masterConfig.baudRate_Hz = 400000; 

    LPI2C_MasterInit(I2Cx, &masterConfig, I2C_CLOCK);
}

/***********************************************************************
*@Function: 
*@Input:    SalveAddr,
            RegAddr,
            *DateByte
*@Return: true / false
*@Author: sola
*@Date: 2019-11-17 23:54:36
*@Drscription: 
***********************************************************************/
bool I2C_WriteByte(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte)
{
    lpi2c_master_transfer_t transfer;
    status_t err_flag;

    /*
    * @data         :Ҫ���͵�����
    * @datasize     :���͵����ݸ���
    * @direction    :��дģʽѡ��
    * @flags        :����ʧ�ܵı�־λ
    * @slaveAaddress:�ӻ���ַ
    * @subaddress   :�Ĵ���/�ڴ��ַ
    * @subaddressSize:��ַ�Ĵ�����С
    */
    transfer.data = DateByte;
    transfer.dataSize = 1;   
    transfer.direction = kLPI2C_Write;
    transfer.flags = kLPI2C_TransferDefaultFlag;
    transfer.slaveAddress =(SalveAddr>>1);
    transfer.subaddress = RegAddr;
    transfer.subaddressSize = 0x01;
    err_flag = LPI2C_MasterTransferBlocking(LPI2C1,&transfer);

    if(err_flag != kStatus_Success)  return false;
       
    return true;
}

/***********************************************************************
*@Function: 
*@Input:    SalveAddr,
            RegAddr,
            *DateByte
*@Return: true / false
*@Author: sola
*@Date: 2019-11-17 23:55:00
*@Drscription: 
***********************************************************************/
bool I2C_ReadByte(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte)
{

    lpi2c_master_transfer_t transfer;
    status_t err_flag;

    /*
    * @data         :���͡����ܵ�����
    * @datasize     :���͵����ݸ���
    * @direction    :��дģʽѡ��
    * @flags        :����ʧ�ܵı�־λ
    * @slaveAaddress:�ӻ���ַ
    * @subaddress   :�Ĵ���/�ڴ��ַ
    * @subaddressSize:��ַ�Ĵ�����С
    */
    transfer.data = DateByte;
    transfer.dataSize = 1;   
    transfer.direction = kLPI2C_Read;
    transfer.flags = kLPI2C_TransferDefaultFlag;
    transfer.slaveAddress =(SalveAddr>>1);
    transfer.subaddress = RegAddr;
    transfer.subaddressSize = 0x01;
    err_flag = LPI2C_MasterTransferBlocking(LPI2C1,&transfer);

    if(err_flag != kStatus_Success)  return false;

    return true;
}

/***********************************************************************
*@Function: 
*@Input:    SalveAddr,
            RegAddr,
            *DateByte
            DataNum
*@Return: true / false
*@Author: sola
*@Date: 2019-11-17 23:55:22
*@Drscription: 
***********************************************************************/
bool I2C_WriteBuffer(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte,uint32_t DataNum)
{
    lpi2c_master_transfer_t transfer;
    status_t err_flag;

    /*
    * @data         :Ҫ���͵�����
    * @datasize     :���͵����ݸ���
    * @direction    :��дģʽѡ��
    * @flags        :����ʧ�ܵı�־λ
    * @slaveAaddress:�ӻ���ַ
    * @subaddress   :�Ĵ���/�ڴ��ַ
    * @subaddressSize:��ַ�Ĵ�����С
    */
    transfer.data = DateByte;
    transfer.dataSize = DataNum;   
    transfer.direction = kLPI2C_Write;
    transfer.flags = kLPI2C_TransferDefaultFlag;
    transfer.slaveAddress =(SalveAddr>>1);
    transfer.subaddress = RegAddr;
    transfer.subaddressSize = 0x01;
    err_flag = LPI2C_MasterTransferBlocking(LPI2C1,&transfer);

    if(err_flag != kStatus_Success)  return false;
       
    return true;
}

/***********************************************************************
*@Function: 
*@Input:    SalveAddr,
            RegAddr,
            *DateByte
            DataNum
*@Return: true / false
*@Author: sola
*@Date: 2019-11-17 23:55:42
*@Drscription: 
***********************************************************************/
bool I2C_ReadBuffer(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte,uint32_t DataNum)
{

    lpi2c_master_transfer_t transfer;
    status_t err_flag;

    /*
    * @data         :���͡����ܵ�����
    * @datasize     :���͵����ݸ���
    * @direction    :��дģʽѡ��
    * @flags        :����ʧ�ܵı�־λ
    * @slaveAaddress:�ӻ���ַ
    * @subaddress   :�Ĵ���/�ڴ��ַ
    * @subaddressSize:��ַ�Ĵ�����С
    */
    transfer.data = DateByte;
    transfer.dataSize = DataNum;   
    transfer.direction = kLPI2C_Read;
    transfer.flags = kLPI2C_TransferDefaultFlag;
    transfer.slaveAddress =(SalveAddr>>1);
    transfer.subaddress = RegAddr;
    transfer.subaddressSize = 0x01;
    err_flag = LPI2C_MasterTransferBlocking(LPI2C1,&transfer);

    if(err_flag != kStatus_Success)  return false;

    return true;
}

#else 


#define I2C_PAD_CONFIG_DATA            (IOMUXC_SW_PAD_CTL_PAD_SRE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(6) | \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(3) | \
                                        IOMUXC_SW_PAD_CTL_PAD_ODE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PKE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUS(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_HYS(0))

/*    PAD ����˵��
*1��SER���ʹر�
*2��DSEǿ�����ر�
*3��SPEED�ٶ�ѡ�� ��100MHz
*4��ODE��©ʹ��
*6��PKE������ʧ��
*7��PUE������ѡ��ѡ������
*8��PUS����������ѡ��ѡ��22K
*9���ͻػ�����ʹ��
*/

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:03
*@Drscription: 
***********************************************************************/
void I2C_Init(void)
{
    gpio_pin_config_t Config;

    IOMUXC_SetPinMux(I2C_SCL_MUX,0U);
    IOMUXC_SetPinMux(I2C_SDA_MUX,0U); 

    IOMUXC_SetPinConfig(I2C_SCL_MUX,I2C_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(I2C_SCL_MUX,I2C_PAD_CONFIG_DATA);

    /*                      
    *                       ��ʼ������
    * ����Ϊ���ģʽ
    * �����ж�
    * ��ʼ����ߵ�ƽ
    */
    Config.direction = kGPIO_DigitalOutput;
    Config.interruptMode = 0U;
    Config.outputLogic = 1;       //set logic 1
    GPIO_PinInit(I2C_PORT, I2C_SCL_PIN, &Config);
    GPIO_PinInit(I2C_PORT, I2C_SDA_PIN, &Config);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:57:56
*@Drscription: 
***********************************************************************/
bool I2C_IOMode(uint8_t MODE)
{
    gpio_pin_config_t Config;

    if(MODE==0)    //Setting mode Input
    {
        Config.direction = kGPIO_DigitalInput;   
        Config.interruptMode = 0U;
        //Config.outputLogic = 1;      
        GPIO_PinInit(I2C_PORT, I2C_SDA_PIN, &Config);
    }
    else 
    {
        Config.direction = kGPIO_DigitalOutput;
        Config.interruptMode = 0U;
        Config.outputLogic = 1;       //
        GPIO_PinInit(I2C_PORT, I2C_SDA_PIN, &Config);
    }
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:06
*@Drscription: 
***********************************************************************/
bool I2C_Start(void)
{

    return true;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:08
*@Drscription: 
***********************************************************************/
bool I2C_Stop(void)
{


    return true;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:16
*@Drscription: 
***********************************************************************/
bool I2C_Ack()
{

    return true;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:19
*@Drscription: 
***********************************************************************/
bool I2C_NoAck()
{


    return true;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:21
*@Drscription: 
***********************************************************************/
bool I2C_WriteByte(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte)
{


}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:25
*@Drscription: 
***********************************************************************/
bool I2C_ReadByte(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte)
{


}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:29
*@Drscription: 
***********************************************************************/
bool I2C_WriteBuffer(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte,uint32_t DataNum)
{


}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-19 19:44:32
*@Drscription: 
***********************************************************************/
bool I2C_ReadBuffer(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte,uint32_t DataNum)
{



}
#endif 
