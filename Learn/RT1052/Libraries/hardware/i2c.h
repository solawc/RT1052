/***********************************************************************
*@Author: sola
*@Date: 2019-11-17 17:05:16
*@FilePath: \RT1052\Libraries\hardware\i2c.h
*@Drscription: 
***********************************************************************/

#ifndef __i2c_h
#define __i2c_h


#include "fsl_common.h" 
#include "fsl_iomuxc.h"



/***********************************************************************
* if you want use software i2c,please defien USE_I2C_SF
***********************************************************************/
//#define USE_I2C_SF

#if !defined(USE_I2C_SF)

/* I2C PORT define */
#define I2Cx                        LPI2C1
#define I2C_PORT                    GPIO1               
#define I2C_SDA_PIN                 17U
#define I2C_SCL_PIN                 16U
#define I2C_CLOCK                   (CLOCK_GetFreq(kCLOCK_Usb1PllClk)/8)/(5 + 1U)
#define I2C_SCL_MUX                 IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL
#define I2C_SDA_MUX                 IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA

#define EEPROM_ADDR                 0XA0
#else

#define I2Cx                        LPI2C1
#define I2C_PORT                    GPIO1               
#define I2C_SDA_PIN                 17U
#define I2C_SCL_PIN                 16U
#define I2C_CLOCK                   (CLOCK_GetFreq(kCLOCK_Usb1PllClk)/8)/(5 + 1U)
#define I2C_SCL_MUX                 IOMUXC_GPIO_AD_B1_00_GPIO1_IO16
#define I2C_SDA_MUX                 IOMUXC_GPIO_AD_B1_01_GPIO1_IO17

#endif


void I2C_Init(void);
bool I2C_WriteByte(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte);
bool I2C_ReadByte(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte);
bool I2C_WriteBuffer(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte,uint32_t DataNum);
bool I2C_ReadBuffer(uint8_t SalveAddr,uint8_t RegAddr,uint8_t *DateByte,uint32_t DataNum);

#endif // !__i2c_h

