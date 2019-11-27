/***********************************************************************
*@Author: sola
*@Date: 2019-11-20 20:57:54
*@FilePath: \RT1052\Libraries\hardware\spi.h
*@Drscription: 
***********************************************************************/
#ifndef __spi_h
#define __spi_h

#include "fsl_common.h"
#include "fsl_flexspi.h"



/* IO MUX DEFINE */
#define QSPI_IO0_MUX    IOMUXC_GPIO_SD_B1_08_FLEXSPIA_DATA00
#define QSPI_IO1_MUX    IOMUXC_GPIO_SD_B1_09_FLEXSPIA_DATA01
#define QSPI_IO2_MUX    IOMUXC_GPIO_SD_B1_10_FLEXSPIA_DATA02
#define QSPI_IO3_MUX    IOMUXC_GPIO_SD_B1_11_FLEXSPIA_DATA03
#define QSPI_SCK_MUX    IOMUXC_GPIO_SD_B1_07_FLEXSPIA_SCLK
#define QSPI_CE_MUX     IOMUXC_GPIO_SD_B1_06_FLEXSPIA_SS0_B



/* FLASH常用命令 */
#define W25Q_WriteEnable                0x06
#define W25Q_WriteDisable               0x04
#define W25Q_ReadStatusReg              0x05
#define W25Q_WriteStatusReg             0x01
#define W25Q_ReadData                   0x03
#define W25Q_ReadData_4Addr             0x13
#define W25Q_FastReadData               0x0B
#define W25Q_FastReadData_4Addr         0x0C
#define W25Q_FastReadDual               0x3B
#define W25Q_FastReadDual_4Addr         0x3C
#define W25Q_FastReadQuad               0x6B
#define W25Q_FastReadQuad_4Addr         0xEC
#define W25Q_PageProgram                0x02
#define W25Q_PageProgram_4Addr          0x12
#define W25Q_PageProgramQuad            0x32
#define W25Q_PageProgramQuad_4Addr      0x34
#define W25Q_BlockErase                 0xD8
#define W25Q_BlockErase_4Addr           0xDC
#define W25Q_SectorErase                0x20
#define W25Q_SectorErase_4Addr          0x21
#define W25Q_ChipErase                  0xC7
#define W25Q_PowerDown                  0xB9
#define W25Q_ReleasePowerDown           0xAB
#define W25Q_DeviceID                   0xAB
#define W25Q_ManufactDeviceID           0x90
#define W25Q_JedecDeviceID              0x9F
/*其它*/
#define FLASH_ID                        0X18  
#define FLASH_WINBOND_JEDECDEVICE_ID    0XEF4019   
#define FLASH_ISSI_JEDECDEVICE_ID       0X9D6019  

/* FLASH的状态寄存器BUSY位的极性，为1时表示忙碌 */
#define FLASH_BUSY_STATUS_POL       1
/* FLASH的状态寄存器BUSY位的偏移，第0位 */
#define FLASH_BUSY_STATUS_OFFSET    0







#endif /* __spi_h */
